# Raytracer

A physically-based raytracer written in C++20. Scenes are defined in JSON and rendered to PPM images.

## Features

- **Shapes:** Sphere, Plane
- **Materials:** Lambertian (diffuse), Metal (with conductor IOR/k), Dielectric (glass)
- **Lights:** Ambient, Directional
- **Camera:** Perspective with look-at transform
- **Acceleration:** BVH aggregate
- **Integrators:** Simple (direct), Recursive (multi-bounce)

## Build

Requires CMake 3.28+ and clang++.

```bash
mkdir build && cd build
cmake ..
make
```

The binary is output as `raytracer` in the build directory.

## Usage

```bash
./raytracer <scene.json>
```

Output is written to `output.ppm`.

## Scene Format

Scenes are described in JSON. See `config/` for examples.

```json
{
  "background_color": [24, 184, 224],
  "camera": {
    "resolution": [1920, 1080],
    "position":   [0.0, -100.0, 60.0],
    "target":     [0.0,   0.0,   0.0],
    "up":         [0.0,   0.0,   1.0],
    "fov":        60.0
  },
  "materials": [
    { "id": "red", "type": "lambertian", "config": { "albedo": [255, 0, 0] } }
  ],
  "primitives": [
    {
      "type": "geometric_primitive",
      "material_id": "red",
      "shape": { "type": "sphere", "config": { "center": [0, 0, 0], "radius": 10 } }
    }
  ]
}
```

### Material types

| Type         | Config fields                  |
|--------------|-------------------------------|
| `lambertian` | `albedo` (RGB 0–255)          |
| `metal`      | `eta`, `k` (conductor IOR), `fuzz` |
| `dielectric` | `ior`                         |

### Shape types

| Type     | Config fields              |
|----------|---------------------------|
| `sphere` | `center` (xyz), `radius`  |
| `plane`  | `point`, `normal`         |

## Tests

```bash
cd build && ctest
```

## License

See [LICENCE](LICENCE).
