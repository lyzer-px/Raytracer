/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Disk.cpp
*/

#include "Disk.hpp"

#include "IShape.hpp"
#include "Normal.hpp"
#include "maths.hpp"

namespace raytracer::shape {

Disk::Disk(const nlohmann::json &config):
    _radius{config.at("radius").get<double>()}
{
    if (config.contains("inner_radius"))
        _innerRadius = config.at("inner_radius").get<double>();
    if (config.contains("reverse_orientation"))
        _reverseOrientation = config.at("reverse_orientation").get<bool>();
}

Disk::Disk(double radius, double innerRadius, bool reverseOrientation):
    _radius{radius},
    _innerRadius{innerRadius},
    _reverseOrientation{reverseOrientation}
{}

std::optional<SurfaceInteraction> Disk::intersect(const maths::Ray &ray) const
{
    if (std::abs(ray.direction.z()) < 1e-8)
        return std::nullopt;

    const double t = -ray.origin.z() / ray.direction.z();
    if (t <= 0 || t >= ray.tMax)
        return std::nullopt;

    const maths::Point3d hitPoint = ray(t);
    const double dist2 =
        hitPoint.x() * hitPoint.x() + hitPoint.y() * hitPoint.y();
    if (dist2 > _radius * _radius || dist2 < _innerRadius * _innerRadius)
        return std::nullopt;

    double phi = std::atan2(hitPoint.y(), hitPoint.x());
    if (phi < 0.0)
        phi += 2.0 * M_PI;

    const double rHit = std::sqrt(dist2);
    const double u    = phi / (2.0 * M_PI);
    const double v    = (_radius - rHit) / (_radius - _innerRadius);

    const bool hitsTopFace = ray.direction.z() < 0;
    const double normalZ   = (hitsTopFace != _reverseOrientation) ? 1.0 : -1.0;

    ray.tMax = t;

    return SurfaceInteraction{.hitPoint = hitPoint,
        .normal                         = maths::Normal3d{0.0, 0.0, normalZ},
        .wo                             = -ray.direction.normalize(),
        .uv                             = maths::Point2d{u, v}};
}

bool Disk::intersectP(const maths::Ray &ray) const
{
    if (std::abs(ray.direction.z()) < 1e-8)
        return false;

    const double t = -ray.origin.z() / ray.direction.z();
    if (t <= 0 || t >= ray.tMax)
        return false;

    const maths::Point3d hitPoint = ray(t);
    const double dist2 =
        hitPoint.x() * hitPoint.x() + hitPoint.y() * hitPoint.y();
    return dist2 <= _radius * _radius && dist2 >= _innerRadius * _innerRadius;
}

maths::Bounds3<> Disk::objectBound() const
{
    constexpr double eps = 1e-4;
    return maths::Bounds3d{maths::Point3d{-_radius, -_radius, -eps},
        maths::Point3d{_radius, _radius, eps}};
}

std::unique_ptr<IShape> Disk::create(const nlohmann::json &config)
{
    return std::make_unique<Disk>(config);
}

} // namespace raytracer::shape
