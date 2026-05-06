/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Dielectric
*/

#include "include/Dielectric.hpp"

namespace raytracer {
namespace material {
Dielectric::Dielectric(const double &ior): _ior{ior}
{}

std::optional<ScatterRecord> Dielectric::scatter(const maths::Ray &ray,
    const shape::SurfaceInteraction &si) const
{
    const maths::Color attenuation{1.0, 1.0, 1.0};
    const auto normalVec = maths::Vector3d{si.normal};
    const bool frontFace = normalVec.dot(
        -ray.direction.normalize()) > 0.0;
    const double ratio      = frontFace ? (1.0 / _ior) : _ior;
    maths::Vector3d unitDir = ray.direction.normalize();
    const double cosTheta   = std::min((-unitDir).dot(normalVec),
        1.0);
    const double sinTheta     = std::sqrt(1.0 - (cosTheta * cosTheta));
    const bool cannotRefract  = ratio * sinTheta > 1.0;
    const bool schlickReflect = schlick(cosTheta, ratio) >
        maths::randomNumber<double>();
    const bool isReflect             = cannotRefract || schlickReflect;
    const maths::Vector3d scatterDir = isReflect
        ? unitDir.reflect(normalVec)
        : unitDir.refract(maths::Vector3d{si.normal}, ratio);
    const auto normalDir        = maths::Vector3d{si.normal};
    const maths::Point3d origin = si.hitPoint + normalDir * (isReflect
        ? 0.0001
        : -0.0001);

    return ScatterRecord{
        .scattered   = maths::Ray{origin, scatterDir.normalize()},
        .attenuation = attenuation,
        .isSpecular  = true
    };
}

double Dielectric::schlick(const double &cosTheta, const double &ratio)
{
    double r0 = (1.0 - ratio) / (1.0 + ratio);
    r0        = r0 * r0;

    return r0 + ((1.0 - r0) * std::pow(1.0 - cosTheta, 5.0));
}
} // material
} // raytracer
