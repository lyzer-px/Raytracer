/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IShape
*/

#pragma once

#include <optional>

#include "Normal.hpp"
#include "Point.hpp"
#include "Ray.hpp"

namespace raytracer::shape {
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

} // namespace raytracer::shape
