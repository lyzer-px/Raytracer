/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** GeometricPrimitive
*/

#include "GeometricPrimitive.hpp"

namespace raytracer {
namespace shape {
GeometricPrimitive::GeometricPrimitive(std::unique_ptr<IShape> &shape,
    std::unique_ptr<material::IMaterial> &material): _shape{std::move(shape)},
    _material{std::move(material)}
{}

std::optional<SurfaceInteraction> GeometricPrimitive::intersect(
    const Ray &ray) const
{
    auto surfaceInteraction = _shape->intersect(ray);
    if (!surfaceInteraction)
        return std::nullopt;

    surfaceInteraction->primitive = this;

    return surfaceInteraction;
}

bool GeometricPrimitive::intersectP(const Ray &ray) const
{
    return _shape->intersectP(ray);
}

const material::IMaterial *GeometricPrimitive::material() const
{
    return _material.get();
}
} // shape
} // raytracer
