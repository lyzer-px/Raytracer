/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** GeometricPrimitive
*/

#include "GeometricPrimitive.hpp"
#include "FactoryTemplate.hpp"
#include "IShape.hpp"
#include <string>

namespace raytracer::shape {

GeometricPrimitive::GeometricPrimitive(std::unique_ptr<IShape> &shape,
    material::IMaterial *material): _shape{std::move(shape)},
    _material{material}
{}


GeometricPrimitive::GeometricPrimitive(std::unique_ptr<IShape> &&shape,
    material::IMaterial *material): _shape{std::move(shape)},
    _material{material}
{}

std::optional<SurfaceInteraction> GeometricPrimitive::intersect(
    const maths::Ray &ray) const
{
    auto surfaceInteraction = _shape->intersect(ray);
    if (!surfaceInteraction)
        return std::nullopt;

    surfaceInteraction->primitive = this;

    return surfaceInteraction;
}

bool GeometricPrimitive::intersectP(const maths::Ray &ray) const
{
    return _shape->intersectP(ray);
}

std::unique_ptr<IPrimitive> create(std::unique_ptr<IShape> &shape,
    material::IMaterial *material)
{
    return std::make_unique<GeometricPrimitive>(shape, material);
}

const material::IMaterial *GeometricPrimitive::material() const
{
    return _material;
}
} // raytracer::shape
