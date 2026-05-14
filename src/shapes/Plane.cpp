/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"

#include <cmath>
#include <limits>

namespace raytracer {
namespace shape {
Plane::Plane(bool reverseOrientation): _reverseOrientation{reverseOrientation}
{}

Plane::Plane(const nlohmann::json &config)
{
    if (config.contains("reverse_orientation"))
        _reverseOrientation = config.at("reverse_orientation").get<bool>();
}

std::optional<SurfaceInteraction> Plane::intersect(const maths::Ray &ray) const
{
    if (std::abs(ray.direction.z()) < 1e-8)
        return std::nullopt;

    const double t = -ray.origin.z() / ray.direction.z();
    if (t <= 0 || t >= ray.tMax)
        return std::nullopt;

    const maths::Point3d hitPoint = ray(t);
    const bool hitsTopFace = ray.direction.z() < 0;
    const double normalZ = (hitsTopFace != _reverseOrientation) ? 1.0 : -1.0;

    ray.tMax = t;

    return SurfaceInteraction{
        .hitPoint = hitPoint,
        .normal   = maths::Normal3d{0.0, 0.0, normalZ},
        .wo       = -ray.direction.normalize(),
        .uv       = maths::Point2d{hitPoint.x(), hitPoint.y()}
    };
}

bool Plane::intersectP(const maths::Ray &ray) const
{
    if (std::abs(ray.direction.z()) < 1e-8)
        return false;

    const double t = -ray.origin.z() / ray.direction.z();
    return t > 0 && t < ray.tMax;
}

maths::Bounds3<> Plane::objectBound() const
{
    // Infinity produces NaN when multiplied by zero matrix elements during
    // Transform application (0 * inf = NaN in IEEE 754). Use a large finite
    // extent that covers any practical scene.
    constexpr double large = 1e6;
    constexpr auto eps     = 1e-4;

    return maths::Bounds3d{maths::Point3d{-large, -large, -eps},
                           maths::Point3d{large, large, eps}};
}

std::unique_ptr<IShape> Plane::create(const nlohmann::json &config)
{
    return std::make_unique<Plane>(config);
}
} // shape
} // raytracer
