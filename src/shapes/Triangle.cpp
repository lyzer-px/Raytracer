/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Triangle.cpp
*/

#include "Triangle.hpp"

#include <algorithm>
#include <cmath>

#include "Normal.hpp"
#include "Serializer.hpp"

namespace raytracer::shape {

Triangle::Triangle(maths::Point3d v0, maths::Point3d v1, maths::Point3d v2):
    _v0{v0}, _v1{v1}, _v2{v2}
{}

Triangle::Triangle(const nlohmann::json &config):
    _v0{config.at("v0").get<maths::Point3d>()},
    _v1{config.at("v1").get<maths::Point3d>()},
    _v2{config.at("v2").get<maths::Point3d>()}
{}

std::optional<SurfaceInteraction> Triangle::intersect(
    const maths::Ray &ray) const
{
    const maths::Vector3d e1  = _v1 - _v0;
    const maths::Vector3d e2  = _v2 - _v0;
    const maths::Vector3d h   = ray.direction.cross(e2);
    const double a            = e1.dot(h);

    if (std::abs(a) < 1e-8)
        return std::nullopt;

    const double f            = 1.0 / a;
    const maths::Vector3d s   = ray.origin - _v0;
    const double u            = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return std::nullopt;

    const maths::Vector3d q   = s.cross(e1);
    const double v            = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return std::nullopt;

    const double t = f * e2.dot(q);
    if (t <= 0.0 || t >= ray.tMax)
        return std::nullopt;

    ray.tMax = t;
    return SurfaceInteraction{
        .hitPoint = ray(t),
        .normal   = maths::Normal3d{e1.cross(e2).normalize()},
        .wo       = -ray.direction.normalize(),
        .uv       = maths::Point2d{u, v}};
}

bool Triangle::intersectP(const maths::Ray &ray) const
{
    const maths::Vector3d e1  = _v1 - _v0;
    const maths::Vector3d e2  = _v2 - _v0;
    const maths::Vector3d h   = ray.direction.cross(e2);
    const double a            = e1.dot(h);

    if (std::abs(a) < 1e-8)
        return false;

    const double f            = 1.0 / a;
    const maths::Vector3d s   = ray.origin - _v0;
    const double u            = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return false;

    const maths::Vector3d q   = s.cross(e1);
    const double v            = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return false;

    const double t = f * e2.dot(q);
    return t > 0.0 && t < ray.tMax;
}

maths::Bounds3<> Triangle::objectBound() const
{
    auto mn = maths::Point3d{
        std::min({_v0.x(), _v1.x(), _v2.x()}),
        std::min({_v0.y(), _v1.y(), _v2.y()}),
        std::min({_v0.z(), _v1.z(), _v2.z()})};
    auto mx = maths::Point3d{
        std::max({_v0.x(), _v1.x(), _v2.x()}),
        std::max({_v0.y(), _v1.y(), _v2.y()}),
        std::max({_v0.z(), _v1.z(), _v2.z()})};

    if (mx.x() - mn.x() < 1e-4)
        mx = maths::Point3d{mx.x() + 1e-4, mx.y(), mx.z()};
    if (mx.y() - mn.y() < 1e-4)
        mx = maths::Point3d{mx.x(), mx.y() + 1e-4, mx.z()};
    if (mx.z() - mn.z() < 1e-4)
        mx = maths::Point3d{mx.x(), mx.y(), mx.z() + 1e-4};

    return maths::Bounds3d{mn, mx};
}

std::unique_ptr<IShape> Triangle::create(const nlohmann::json &config)
{
    return std::make_unique<Triangle>(config);
}

} // namespace raytracer::shape
