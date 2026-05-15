# Qt6 Interactive Raytracer UI — Implementation Plan

## Goal

Add a second executable `raytracer-ui` alongside the existing CLI `raytracer`. The UI runs the renderer in a dedicated render thread while the Qt event loop lives in the main thread. Scene objects are shared data — primitives, lights, and the camera expose setter interfaces protected by fine-grained mutexes so the render thread can continue working while the UI updates non-structural state. For structural changes that invalidate the BVH (primitive transforms, shape geometry), the render thread pauses briefly while BVH rebuilds (shown as a modal progress dialog), then resumes. The integrator's render loop is designed around a `renderTile()` primitive to make a future multithreaded upgrade a drop-in.

---

## Concurrency Model

### Two tiers of change

**Structural (BVH-invalidating):** primitive transform, sphere radius — any change that alters `worldBound()`.
1. UI takes the scene-level `std::unique_lock` (render thread finishes its current scanline and yields its `std::shared_lock`)
2. Updates the primitive in-place
3. Rebuilds BVH (with indeterminate `QProgressDialog`)
4. Releases lock → render resumes with new BVH

**Non-structural:** camera movement, material albedo/roughness, light radiance/direction — no BVH impact.
- Each object owns a `std::mutex` (camera: `_viewMutex`, each light: `_lightMutex`, each material: `_matMutex`)
- Render reads: briefly lock → copy values → unlock → use copy for full ray computation
- UI writes: briefly lock → update → unlock
- Render never pauses; next ray picks up new values

### Shared data layout

```
Scene
  std::shared_mutex _sceneMutex        ← structural lock (BVH + primitive geometry)
  std::vector<IPrimitive>              ← geometry protected by _sceneMutex
  BvhAggregate                         ← rebuilt under unique_lock

PerspectiveCamera
  std::mutex _viewMutex                ← fine-grained, non-structural

ILight (per instance)
  std::mutex _lightMutex               ← fine-grained, non-structural

IMaterial (per instance)
  std::mutex _matMutex                 ← fine-grained, non-structural

Film (double-buffer)
  back  ← render writes here
  front ← UI reads here for display
  std::mutex _swapMutex ← swapped at frame boundary
```

---

## Files to Modify

### `CMakeLists.txt` (root)
```cmake
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
```

### `src/CMakeLists.txt`
```cmake
add_subdirectory(ui)
```

### `src/scene/include/Scene.hpp` + `Scene.cpp`
- Add `std::shared_mutex _sceneMutex` with public reference accessor
- Add `const std::vector<std::unique_ptr<shape::IPrimitive>> &primitives() const`
- `intersect()` / `intersectAny()` do **not** lock internally — caller (render thread) holds `shared_lock` for the whole scanline

### `src/shapes/include/IPrimitive.hpp`
```cpp
virtual void setObjectToWorld(const maths::Transform &t) = 0;
```

### `src/shapes/GeometricPrimitive.hpp/.cpp`
Implement `setObjectToWorld`: updates `_objectToWorld` + `_worldToObject`. Caller holds scene `unique_lock` and calls `scene.buildAccelerator()` afterwards.

### `src/shapes/include/IShape.hpp` + `Sphere.hpp/.cpp`
```cpp
void setRadius(double r);  // BVH-invalidating
```

### `src/lights/include/ILight.hpp` + concrete lights
```cpp
virtual void setRadiance(const maths::Color &radiance) = 0;
```
Each concrete light stores `std::mutex _lightMutex`. `sample()` locks briefly to copy state.

### `src/cameras/include/PerspectiveCamera.hpp` + `.cpp`
- Store `_position`, `_target`, `_up` as fields alongside `_cameraToWorld`
- Add `void updateView(const Point3d &pos, const Point3d &target, const Vector3d &up)` — locks `_viewMutex`, recomputes `_cameraToWorld`
- `generateRay()` locks `_viewMutex`, copies transform scalars, unlocks, generates ray from copies
- Add getters: `position()`, `target()`, `up()`, `fovDegrees()`

### `src/cameras/include/Film.hpp` + `Film.cpp`
Double-buffer:
```cpp
class Film {
    std::vector<maths::Color> _back;   // render writes
    std::vector<maths::Color> _front;  // UI reads
    std::mutex _swapMutex;
public:
    void addSample(int x, int y, const maths::Color &c);  // writes _back
    void swapBuffers();                                     // brief lock, swap
    const maths::Color &getFrontPixel(int x, int y) const; // UI reads _front
};
```

### `src/integrators/include/IIntegrator.hpp`
```cpp
virtual void renderTile(int x0, int y0, int w, int h,
    const scene::Scene &scene,
    const camera::ICamera &camera,
    camera::Film &film) const = 0;

// Default full-image render: loops scanlines, yields sceneMutex between rows
void render(const scene::Scene &scene,
    const camera::ICamera &camera,
    camera::Film &film,
    std::shared_mutex &sceneMutex) const;
```
`render()` releases + reacquires the shared_lock at each scanline boundary — this is the yield point where a structural edit can take the unique_lock.

### `src/integrators/RecursiveIntegrator.hpp/.cpp` + `SimpleIntegrator.hpp/.cpp`
Implement `renderTile()` — same loop logic as current `render()`, bounded to tile region.

---

## New Files (`src/ui/`)

### `src/ui/CMakeLists.txt`
Defines `raytracer-ui` executable, links Qt6::Widgets + all existing static libs, sets include paths.

### `src/ui/RenderThread.hpp/.cpp`
`QThread` subclass. Owns `SimpleIntegrator` + `Film(960, 540)`.

```cpp
class RenderThread : public QThread {
    Q_OBJECT
public:
    void setScene(scene::Scene *, camera::PerspectiveCamera *);
    void stopRender();
signals:
    void frameReady();
protected:
    void run() override;
    // while (!_stop):
    //   shared_lock on scene mutex
    //   integrator.render(*_scene, *_camera, _film, sceneMutex)
    //   _film.swapBuffers()
    //   emit frameReady()
};
```

### `src/ui/RenderWidget.hpp/.cpp`
Central `QWidget`:
- Holds `QImage(960, 540, QImage::Format_RGB888)`; updated from `Film::getFrontPixel()` on `frameReady`
- `paintEvent`: draws QImage scaled/letterboxed to widget size
- `keyPressEvent/keyReleaseEvent`: tracks WASD
- `mousePressEvent/mouseMoveEvent`: captures delta for yaw/pitch
- 16 ms `QTimer`: applies movement to `camera.updateView(pos, target, up)` — purely non-structural, render never pauses

**Camera navigation math:**
```
forward = normalize(target − position)
right   = normalize(forward × up)

W/S → position ±= forward * speed;  target ±= forward * speed
A/D → position ∓= right * speed;    target ∓= right * speed
mouse dx → yaw   (rotate forward around up)
mouse dy → pitch (rotate forward around right)
```

### `src/ui/SceneInspector.hpp/.cpp`
`QDockWidget` (docked right). `QTreeWidget` with four top-level nodes:

- **Camera** — fov, position, target, up → edits call `camera.updateView()` directly (non-structural)
- **Primitives** — transform + shape params. "Apply":
  1. `std::unique_lock` on `scene.sceneMutex()`
  2. `primitive->setObjectToWorld(t)` or `sphere->setRadius(r)`
  3. Show indeterminate `QProgressDialog` while `scene.buildAccelerator()` runs
  4. Release lock → render resumes
- **Lights** — radiance, direction → calls `light.setRadiance()` (fine-grained mutex, no rebuild)
- **Materials** — albedo/roughness/ior → calls material setters (fine-grained mutex, no rebuild)

### `src/ui/MainWindow.hpp/.cpp`
`QMainWindow`:
- `setCentralWidget(renderWidget)`
- `addDockWidget(Qt::RightDockWidgetArea, inspector)`
- Menu: **File → Open Scene**, **Render → High-Quality Export** (full-res RecursiveIntegrator on separate thread, saves PPM)
- Status bar: render progress / "Ready"
- Connects `renderThread.frameReady()` → `renderWidget.updateDisplay()`

### `src/ui/main_ui.cpp`
```cpp
int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow window;
    if (argc > 1) window.loadScene(argv[1]);
    window.show();
    return app.exec();
}
```

---

## Rendering Resolution Strategy

| Mode | Resolution | Integrator | spp | Trigger |
|------|-----------|------------|-----|---------|
| Live preview | 960×540 | SimpleIntegrator | 1 | Continuous in RenderThread |
| High-quality export | 1920×1080 | RecursiveIntegrator | 6 | Menu → Export |

---

## Verification Checklist

1. `cmake --build build` — both `raytracer` and `raytracer-ui` compile without errors
2. `./raytracer-ui config/example4.json` — window opens, scene renders at 960×540
3. WASD + mouse drag — camera moves, render updates continuously, no pause
4. Inspector: change a light's radiance — lighting updates on next frame, no dialog
5. Inspector: move a sphere — progress dialog appears briefly, render shows updated geometry
6. Inspector: change material albedo — color updates on next frame, no dialog
7. Export → high-quality → PPM written at 1920×1080
8. `./raytracer config/example4.json` — CLI batch render still works identically
