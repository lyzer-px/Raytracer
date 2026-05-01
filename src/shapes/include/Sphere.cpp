/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace raytracer {
namespace shape {
Sphere::Sphere(const Point3d &origin, const double &radius): _origin{origin},
    _radius{radius}
{}

std::optional<SurfaceInteraction> Sphere::intersect(const Ray &ray, float tMin,
    float tMax) const
{
    return {};
}
} // shape
} // raytracer
