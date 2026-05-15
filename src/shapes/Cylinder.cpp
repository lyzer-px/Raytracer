/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"

#include "IShape.hpp"
#include "Normal.hpp"
#include "maths.hpp"

namespace raytracer::shape {

Cylinder::Cylinder(const nlohmann::json &config):
    _radius{config.at("radius").get<double>()},
    _zMin{config.at("z_min").get<double>()},
    _zMax{config.at("z_max").get<double>()}
{
    if (config.contains("reverse_orientation"))
        _reverseOrientation = config.at("reverse_orientation").get<bool>();
}

Cylinder::Cylinder(double radius, double zMin, double zMax,
    bool reverseOrientation):
    _radius{radius},
    _zMin{zMin},
    _zMax{zMax},
    _reverseOrientation{reverseOrientation}
{}

std::optional<Cylinder::Hit> Cylinder::findLateralHit(
    const maths::Ray &ray) const
{
    const double dx = ray.direction.x();
    const double dy = ray.direction.y();
    const double ox = ray.origin.x();
    const double oy = ray.origin.y();

    const double a = dx * dx + dy * dy;
    if (a <= 1e-8)
        return std::nullopt;

    const double h    = ox * dx + oy * dy;
    const double c    = ox * ox + oy * oy - _radius * _radius;
    const double disc = h * h - a * c;
    if (disc < 0.0)
        return std::nullopt;

    const double sqrtDisc = std::sqrt(disc);
    const double oz       = ray.origin.z();
    const double dz       = ray.direction.z();

    for (const double t : {(-h - sqrtDisc) / a, (-h + sqrtDisc) / a}) {
        if (t <= 0.0 || t >= ray.tMax)
            continue;
        const double z = oz + t * dz;
        if (z >= _zMin && z <= _zMax)
            return Hit{t, HitPart::LATERAL};
    }
    return std::nullopt;
}

std::optional<Cylinder::Hit> Cylinder::findCapHit(
    const maths::Ray &ray, double zTarget, HitPart part) const
{
    const double dz = ray.direction.z();
    if (std::abs(dz) <= 1e-8)
        return std::nullopt;

    const double t = (zTarget - ray.origin.z()) / dz;
    if (t <= 0.0 || t >= ray.tMax)
        return std::nullopt;

    const maths::Point3d p = ray(t);
    if (p.x() * p.x() + p.y() * p.y() > _radius * _radius)
        return std::nullopt;

    return Hit{t, part};
}

SurfaceInteraction Cylinder::buildInteraction(
    const maths::Ray &ray, const Hit &hit) const
{
    const maths::Point3d hitPoint = ray(hit.t);
    ray.tMax                      = hit.t;

    double phi = std::atan2(hitPoint.y(), hitPoint.x());
    if (phi < 0.0)
        phi += 2.0 * M_PI;
    const double u = phi / (2.0 * M_PI);

    if (hit.part == HitPart::LATERAL) {
        const double normalDir = _reverseOrientation ? -1.0 : 1.0;
        return SurfaceInteraction{
            .hitPoint = hitPoint,
            .normal   = maths::Normal3d{
                hitPoint.x() / _radius * normalDir,
                hitPoint.y() / _radius * normalDir, 0.0},
            .wo = -ray.direction.normalize(),
            .uv = maths::Point2d{u, (hitPoint.z() - _zMin) / (_zMax - _zMin)}};
    }

    const bool isTop   = (hit.part == HitPart::TOP_CAP);
    double normalZ     = isTop ? 1.0 : -1.0;
    if (_reverseOrientation)
        normalZ = -normalZ;

    const double rHit =
        std::sqrt(hitPoint.x() * hitPoint.x() + hitPoint.y() * hitPoint.y());
    return SurfaceInteraction{
        .hitPoint = hitPoint,
        .normal   = maths::Normal3d{0.0, 0.0, normalZ},
        .wo       = -ray.direction.normalize(),
        .uv       = maths::Point2d{u, 1.0 - rHit / _radius}};
}

std::optional<SurfaceInteraction> Cylinder::intersect(
    const maths::Ray &ray) const
{
    const auto lateral   = findLateralHit(ray);
    const auto bottomCap = findCapHit(ray, _zMin, HitPart::BOTTOM_CAP);
    const auto topCap    = findCapHit(ray, _zMax, HitPart::TOP_CAP);

    const Hit *best = nullptr;
    for (const auto *c : {&lateral, &bottomCap, &topCap}) {
        if (c->has_value() && (best == nullptr || c->value().t < best->t))
            best = &c->value();
    }

    if (best == nullptr)
        return std::nullopt;

    return buildInteraction(ray, *best);
}

bool Cylinder::intersectP(const maths::Ray &ray) const
{
    return findLateralHit(ray).has_value()
        || findCapHit(ray, _zMin, HitPart::BOTTOM_CAP).has_value()
        || findCapHit(ray, _zMax, HitPart::TOP_CAP).has_value();
}

maths::Bounds3<> Cylinder::objectBound() const
{
    return maths::Bounds3d{maths::Point3d{-_radius, -_radius, _zMin},
                           maths::Point3d{ _radius,  _radius, _zMax}};
}

std::unique_ptr<IShape> Cylinder::create(const nlohmann::json &config)
{
    return std::make_unique<Cylinder>(config);
}

} // namespace raytracer::shape
