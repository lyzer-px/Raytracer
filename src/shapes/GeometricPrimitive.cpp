/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** GeometricPrimitive
*/

#include "GeometricPrimitive.hpp"

#include <string>

#include "FactoryTemplate.hpp"
#include "IShape.hpp"

namespace raytracer::shape {

GeometricPrimitive::GeometricPrimitive(maths::Transform worldToObject,
    maths::Transform objectToWorld, std::unique_ptr<IShape> &shape,
    material::IMaterial *material):
    _shape{std::move(shape)},
    _material{material},
    _worldToObject{std::move(worldToObject)},
    _objectToWorld{std::move(objectToWorld)}
{}

std::optional<SurfaceInteraction> GeometricPrimitive::intersect(
    const maths::Ray &ray) const
{
    const maths::Ray objectRay = _worldToObject(ray);
    auto si = _shape->intersect(objectRay);
    if (!si)
        return std::nullopt;

    ray.tMax = objectRay.tMax;
    si->primitive = this;
    si->hitPoint  = _objectToWorld(si->hitPoint);
    si->normal    = _objectToWorld(si->normal);
    si->wo        = _objectToWorld(si->wo);

    return si;
}

bool GeometricPrimitive::intersectP(const maths::Ray &ray) const
{
    const maths::Ray objectRay = _worldToObject(ray);
    return _shape->intersectP(objectRay);
}

maths::Bounds3d GeometricPrimitive::worldBound() const
{
    return _objectToWorld(_shape->objectBound());
}

const material::IMaterial *GeometricPrimitive::material() const
{
    return _material;
}

std::unique_ptr<IPrimitive> GeometricPrimitive::create(
    maths::Transform worldToObject, maths::Transform objectToWorld,
    std::unique_ptr<IShape> &shape, material::IMaterial *material)
{
    return std::make_unique<GeometricPrimitive>(
        std::move(worldToObject), std::move(objectToWorld), shape, material);
}
} // namespace raytracer::shape
