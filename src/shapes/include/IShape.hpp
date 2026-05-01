/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IShape
*/

#ifndef RAYTRACER_ISHAPE_HPP
#define RAYTRACER_ISHAPE_HPP

#include <optional>

#include "Normal.hpp"
#include "Point.hpp"
#include "Ray.hpp"

class Ray;

namespace raytracer {
namespace shape {
class IShape;

struct SurfaceInteraction {
    Point3d p;
    Normal3d n;
    Vector3d wo;
    Point2d uv;
    const IShape *shape = nullptr;
    // const IPrimitive *primitive;
};

class IShape {
public:
    virtual ~IShape() = default;

    [[nodiscard]] virtual std::optional<SurfaceInteraction> intersect(
        const Ray &ray) const = 0;

    [[nodiscard]] virtual bool intersectP(const Ray &ray) const = 0;
};

} // shape
} // raytracer

#endif //RAYTRACER_ISHAPE_HPP
