/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

#include "maths.hpp"
#include "Normal.hpp"

namespace raytracer { // NOLINT
namespace shape {
Sphere::Sphere(const Point3d &center, const float &radius): _center{center},
    _radius{radius}
{}

std::optional<SurfaceInteraction> Sphere::intersect(const Ray &ray) const
{
    const auto t = solveQuadratic(ray);
    if (!t)
        return std::nullopt;

    const Point3d hitPoint   = ray(*t);
    const Vector3d temp      = hitPoint - _center;
    const auto outwardNormal = Normal3d{temp.normalize()};
    const Vector3d wo        = -ray.direction.normalize();

    ray.tMax = *t;

    return SurfaceInteraction{
        .p  = hitPoint,
        .n  = outwardNormal,
        .wo = wo,
        .uv = Point2d{
            sphericalTheta(temp) / (2.0 * M_PI),
            sphericalPhi(temp) / M_PI
        }
    };
}

bool Sphere::intersectP(const Ray &ray) const
{
    return solveQuadratic(ray).has_value();
}

std::optional<double> Sphere::solveQuadratic(const Ray &ray) const
{
    const Vector3d oc         = ray.origin - _center;
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
} // shape
} // raytracer
