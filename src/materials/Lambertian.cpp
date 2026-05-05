/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#include "Lambertian.hpp"

namespace raytracer {
namespace material {
Lambertian::Lambertian(const maths::Color &color): _albedo{color}
{}

maths::Color Lambertian::getColor(const shape::SurfaceInteraction &) const // NOLINT
{
    return _albedo;
}

std::optional<ScatterRecord> Lambertian::scatter(const maths::Ray &,
    const shape::SurfaceInteraction &si) const
{
    maths::Vector3d scatterDirection = maths::Vector3d{si.normal} +
        maths::Vector3d::randomUnitVector();

    if (scatterDirection.isNearZero())
        scatterDirection = maths::Vector3d{si.normal};

    const maths::Point3d origin = si.hitPoint + maths::Vector3d{
        si.normal * 0.0001};

    return ScatterRecord{
        .scattered   = maths::Ray{origin, scatterDirection},
        .attenuation = _albedo,
        .isSpecular  = false
    };
}
} // material
} // raytracer
