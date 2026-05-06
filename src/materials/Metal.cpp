/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Metal
*/

#include "Metal.hpp"

namespace raytracer {
namespace material {
Metal::Metal(const maths::Color &albedo, const double &roughness): _eta{albedo},
    _roughness{roughness}, _physical{false}
{}

Metal::Metal(const maths::Color &eta, const maths::Vector3d &k,
    const double &roughness): _eta{eta}, _k{k}, _roughness{roughness},
    _physical{true}
{}

std::optional<ScatterRecord> Metal::scatter(const maths::Ray &ray,
    const shape::SurfaceInteraction &si) const
{
    const maths::Vector3d reflected = -ray.direction.normalize().reflect(
        maths::Vector3d{si.normal});
    const maths::Vector3d scatterDir = reflected +
        maths::Vector3d::randomUnitVector() * _roughness;

    if (scatterDir.dot(maths::Vector3d{si.normal}) <= 0.0)
        return std::nullopt;

    const maths::Point3d origin = si.hitPoint + maths::Vector3d{
        si.normal * 0.0001};

    return ScatterRecord{
        .scattered   = maths::Ray{origin, scatterDir},
        .attenuation = _physical
        ? fresnelConductor(std::abs(
            ray.direction.normalize().dot(
                maths::Vector3d{si.normal.normalize()})))
        : _eta,
        .isSpecular = true
    };
}

maths::Color Metal::fresnelConductor(const double &cosTheta) const
{
    static auto fresnel = [](const double n, const double &k,
        const double &cosT) -> double {
        const double cosSquare = cosT * cosT;
        const double nSquareKSquared = n * n + k * k;
        const double rsNum = nSquareKSquared - 2.0 * n * cosT + cosSquare;
        const double rsDen = nSquareKSquared + 2.0 * n * cosT + cosSquare;
        const double rpNum = nSquareKSquared * cosSquare - 2.0 * n * cosT + 1.0;
        const double rpDen = nSquareKSquared * cosSquare + 2.0 * n * cosT + 1.0;
        return 0.5 * (rsNum / rsDen + rpNum / rpDen);
    };

    return maths::Color{
        fresnel(_eta.r, _k.x(), cosTheta),
        fresnel(_eta.g, _k.y(), cosTheta),
        fresnel(_eta.b, _k.z(), cosTheta)
    };
}
} // material
} // raytracer
