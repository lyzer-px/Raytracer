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

namespace raytracer {
namespace shape {
class IPrimitive;
class IShape;

struct SurfaceInteraction {
    maths::Point3d hitPoint;
    maths::Normal3d normal;
    maths::Vector3d wo;
    maths::Point2d uv;
    const IPrimitive *primitive = nullptr;
};

class IShape {
public:
    virtual ~IShape() = default;

    [[nodiscard]] virtual std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const = 0;

    [[nodiscard]] virtual bool intersectP(const maths::Ray &ray) const = 0;
};

} // shape
} // raytracer

#endif //RAYTRACER_ISHAPE_HPP
