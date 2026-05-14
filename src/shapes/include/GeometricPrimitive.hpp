/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** GeometricPrimitive
*/

#pragma once
#include <memory>

#include "IPrimitive.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {
class GeometricPrimitive: public IPrimitive {
public:
    GeometricPrimitive(maths::Transform worldToObject,
        maths::Transform objectToWorld, std::unique_ptr<IShape> &shape,
        material::IMaterial *material);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3d worldBound() const override;

    [[nodiscard]] const material::IMaterial *material() const override;

    static std::unique_ptr<IPrimitive> create(maths::Transform worldToObject,
        maths::Transform objectToWorld, std::unique_ptr<IShape> &shape,
        material::IMaterial *material);

private:
    std::unique_ptr<IShape> _shape;
    material::IMaterial *_material;
    maths::Transform _worldToObject;
    maths::Transform _objectToWorld;
};
} // namespace raytracer::shape
