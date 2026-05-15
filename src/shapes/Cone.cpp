/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Cone.cpp
*/

#include "Cone.hpp"

#include "IShape.hpp"
#include "Normal.hpp"
#include "maths.hpp"

namespace raytracer::shape {

Cone::Cone(const nlohmann::json &config):
    _radius{config.at("radius").get<double>()},
    _zMin{config.at("z_min").get<double>()},
    _zMax{config.at("z_max").get<double>()},
    _k{_radius / (_zMax - _zMin)}
{
    if (config.contains("reverse_orientation"))
        _reverseOrientation = config.at("reverse_orientation").get<bool>();
}

Cone::Cone(double radius, double zMin, double zMax, bool reverseOrientation):
    _radius{radius},
    _zMin{zMin},
    _zMax{zMax},
    _k{radius / (zMax - zMin)},
    _reverseOrientation{reverseOrientation}
{}

std::optional<Cone::Hit> Cone::findLateralHit(const maths::Ray &ray) const
{
    const double dx = ray.direction.x();
    const double dy = ray.direction.y();
    const double dz = ray.direction.z();
    const double ox = ray.origin.x();
    const double oy = ray.origin.y();
    const double cz = _zMax - ray.origin.z();

    const double k2     = _k * _k;
    const double a      = dx * dx + dy * dy - k2 * dz * dz;
    const double halfB  = ox * dx + oy * dy + k2 * cz * dz;
    const double c      = ox * ox + oy * oy - k2 * cz * cz;
    const double disc   = halfB * halfB - a * c;

    if (disc < 0.0 || std::abs(a) < 1e-8)
        return std::nullopt;

    const double sqrtDisc = std::sqrt(disc);
    for (const double t : {(-halfB - sqrtDisc) / a, (-halfB + sqrtDisc) / a}) {
        if (t <= 0.0 || t >= ray.tMax)
            continue;
        const double z = ray.origin.z() + t * dz;
        if (z >= _zMin && z <= _zMax)
            return Hit{t, HitPart::LATERAL};
    }
    return std::nullopt;
}

std::optional<Cone::Hit> Cone::findBaseCap(const maths::Ray &ray) const
{
    const double dz = ray.direction.z();
    if (std::abs(dz) < 1e-8)
        return std::nullopt;

    const double t = (_zMin - ray.origin.z()) / dz;
    if (t <= 0.0 || t >= ray.tMax)
        return std::nullopt;

    const maths::Point3d p = ray(t);
    if (p.x() * p.x() + p.y() * p.y() > _radius * _radius)
        return std::nullopt;

    return Hit{t, HitPart::BASE_CAP};
}

SurfaceInteraction Cone::buildInteraction(
    const maths::Ray &ray, const Hit &hit) const
{
    const maths::Point3d hitPoint = ray(hit.t);
    ray.tMax                      = hit.t;

    double phi = std::atan2(hitPoint.y(), hitPoint.x());
    if (phi < 0.0)
        phi += 2.0 * M_PI;
    const double u = phi / (2.0 * M_PI);

    if (hit.part == HitPart::LATERAL) {
        const double rHit =
            std::sqrt(hitPoint.x() * hitPoint.x() + hitPoint.y() * hitPoint.y());
        const double invScale = 1.0 / (rHit * std::sqrt(1.0 + _k * _k));
        const double normalDir = _reverseOrientation ? -1.0 : 1.0;

        return SurfaceInteraction{
            .hitPoint = hitPoint,
            .normal   = maths::Normal3d{
                hitPoint.x() * invScale * normalDir,
                hitPoint.y() * invScale * normalDir,
                _k * invScale * normalDir},
            .wo = -ray.direction.normalize(),
            .uv = maths::Point2d{u,
                (hitPoint.z() - _zMin) / (_zMax - _zMin)}};
    }

    const double rHit =
        std::sqrt(hitPoint.x() * hitPoint.x() + hitPoint.y() * hitPoint.y());
    const double normalZ = _reverseOrientation ? 1.0 : -1.0;

    return SurfaceInteraction{
        .hitPoint = hitPoint,
        .normal   = maths::Normal3d{0.0, 0.0, normalZ},
        .wo       = -ray.direction.normalize(),
        .uv       = maths::Point2d{u, 1.0 - rHit / _radius}};
}

std::optional<SurfaceInteraction> Cone::intersect(const maths::Ray &ray) const
{
    const auto lateral = findLateralHit(ray);
    const auto cap     = findBaseCap(ray);

    const Hit *best = nullptr;
    if (lateral.has_value())
        best = &lateral.value();
    if (cap.has_value() && (best == nullptr || cap->t < best->t))
        best = &cap.value();

    if (best == nullptr)
        return std::nullopt;

    return buildInteraction(ray, *best);
}

bool Cone::intersectP(const maths::Ray &ray) const
{
    return findLateralHit(ray).has_value() || findBaseCap(ray).has_value();
}

maths::Bounds3<> Cone::objectBound() const
{
    return maths::Bounds3d{maths::Point3d{-_radius, -_radius, _zMin},
                           maths::Point3d{ _radius,  _radius, _zMax}};
}

std::unique_ptr<IShape> Cone::create(const nlohmann::json &config)
{
    return std::make_unique<Cone>(config);
}

} // namespace raytracer::shape
