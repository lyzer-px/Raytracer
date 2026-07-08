# Raytracer

![Raytraced scene](docs/images/hero-render.png)

A modern physically based ray tracer written in C++20. This project renders scenes defined in JSON and outputs high-quality PPM images using a modular architecture with materials, lights, camera controls, and BVH acceleration.

## Overview

Raytracer is a compact rendering engine designed to explore the fundamentals of ray tracing and physically inspired shading. It supports a clean scene description format, recursive light transport, and several core primitives and materials for building believable test scenes.

## Features

- **C++20 implementation** with a clean, extensible codebase
- **JSON scene descriptions** for easy scene authoring
- **Physically inspired materials**:
  - Lambertian / diffuse
  - Metal with conductor parameters
  - Dielectric / glass
- **Core primitives**:
  - Sphere
  - Plane
- **Lighting models**:
  - Ambient
  - Directional
- **Camera system** with perspective projection and look-at transform
- **BVH acceleration** for improved rendering performance
- **Multiple integrators**:
  - Simple direct integrator
  - Recursive multi-bounce integrator

## Demo

The repository includes rendered scenes like the one below:

![Demo render](docs/images/hero-render.png)

## Requirements

- CMake 3.28 or newer
- A C++20-compatible compiler
- `clang++` is recommended based on the current build setup

## Build

```bash
mkdir build
cd build
cmake ..
make
```

This will generate the `raytracer` executable inside the build directory.

## Usage

Render a scene by passing a JSON file as input:

```bash
./raytracer <scene.json>
```

The output is written to `output.ppm`.

## Scene Format

Scenes are described in JSON. Example:

```json
{
  "background_color": [24, 184, 224],
  "camera": {
    "resolution": [1920, 1080],
    "position": [0.0, -100.0, 60.0],
    "target": [0.0, 0.0, 0.0],
    "up": [0.0, 0.0, 1.0],
    "fov": 60.0
  },
  "materials": [
    {
      "id": "red",
      "type": "lambertian",
      "config": {
        "albedo": [255, 0, 0]
      }
    }
  ],
  "primitives": [
    {
      "type": "geometric_primitive",
      "material_id": "red",
      "shape": {
        "type": "sphere",
        "config": {
          "center": [0, 0, 0],
          "radius": 10
        }
      }
    }
  ]
}
```

### Supported Material Types

| Type | Config fields |
|------|---------------|
| `lambertian` | `albedo` (RGB 0–255) |
| `metal` | `eta`, `k` (conductor IOR), `fuzz` |
| `dielectric` | `ior` |

### Supported Shape Types

| Type | Config fields |
|------|---------------|
| `sphere` | `center`, `radius` |
| `plane` | `point`, `normal` |

## Tests

Run the test suite from the build directory:

```bash
cd build
ctest
```

## Project Structure

- `config/` — sample scene files
- `src/` — renderer implementation
- `tests/` — automated tests

## License

This project is licensed under the MIT License. See [LICENCE](LICENCE).
