/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include "IShape.hpp"
#include "maths.hpp"
#include "Normal.hpp"
#include "Serializer.hpp"

namespace raytracer::shape {
Sphere::Sphere(const nlohmann::json &config):
    _radius{config.at("radius").get<double>()}
{
    if (config.contains("reverse_orientation"))
        _reverseOrientation = config.at("reverse_orientation").get<bool>();
}

Sphere::Sphere(double radius, bool reverseOrientation):
    _radius{radius}, _reverseOrientation{reverseOrientation}
{}

std::optional<SurfaceInteraction> Sphere::intersect(const maths::Ray &ray) const
{
    const auto t = solveQuadratic(ray);
    if (!t)
        return std::nullopt;

    const maths::Point3d hitPoint = ray(*t);
    const maths::Vector3d temp{hitPoint.x(), hitPoint.y(), hitPoint.z()};
    const auto outwardNormal      = maths::Normal3d{temp.normalize()};
    const maths::Vector3d wo      = -ray.direction.normalize();

    ray.tMax = *t;

    return SurfaceInteraction{.hitPoint = hitPoint,
        .normal                         = outwardNormal,
        .wo                             = wo,
        .uv                             = maths::Point2d{
            sphericalTheta(temp) / (2.0 * M_PI), sphericalPhi(temp) / M_PI}};
}

bool Sphere::intersectP(const maths::Ray &ray) const
{
    return solveQuadratic(ray).has_value();
}

std::optional<double> Sphere::solveQuadratic(const maths::Ray &ray) const
{
    const maths::Vector3d oc{ray.origin.x(), ray.origin.y(), ray.origin.z()};
    const double a            = ray.direction.dot(ray.direction);
    const double h            = oc.dot(ray.direction);
    const double c            = oc.dot(oc) - (_radius * _radius);
    const double discriminant = (h * h) - (a * c);

    if (discriminant < 0.0)
        return std::nullopt;

    const double sqrtDiscriminant = std::sqrt(discriminant);

    double t = (-h - sqrtDiscriminant) / a;
    if (t > 0 && t < ray.tMax)
        return std::optional{t};

    t = (-h + sqrtDiscriminant) / a;
    if (t > 0 && t < ray.tMax)
        return std::optional{t};

    return std::nullopt;
}

maths::Bounds3<> Sphere::objectBound() const
{
    return maths::Bounds3d{maths::Point3d{-_radius, -_radius, -_radius},
                           maths::Point3d{_radius, _radius, _radius}};
}

std::unique_ptr<IShape> Sphere::create(const nlohmann::json &config)
{
    return std::make_unique<Sphere>(nlohmann::json(config));
}
} // namespace raytracer::shape
