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
    maths::Vector3d surfaceNormal;
    const maths::Vector3d reflected = ray.direction.reflect(si.normal);
    double ratio;
    double cosTheta;

    if (ray.direction.dot(si.normal) > 0) {
        surfaceNormal = maths::Vector3d{-si.normal};
        ratio = _ior;
        cosTheta = ray.direction.normalize().dot(si.normal);
    } else {
        surfaceNormal = maths::Vector3d{si.normal};
        ratio = 1.0 / _ior;
        cosTheta = -ray.direction.dot(si.normal);
    }

    const maths::Point3d reflectOrigin = si.hitPoint + surfaceNormal * 0.0001;
    const maths::Point3d refractOrigin = si.hitPoint - surfaceNormal * 0.0001;

    const std::optional<maths::Vector3d> refracted = ray.direction.refraction(
        surfaceNormal, ratio);
    double reflectionProbability;
    if (refracted)
        reflectionProbability = schlick(cosTheta, _ior);
    else
        reflectionProbability = 1.0;

    if (maths::randomNumber<double>() < reflectionProbability) {
        return ScatterRecord{
            .scattered = maths::Ray{reflectOrigin, reflected},
            .attenuation = maths::Color{1.0, 1.0, 1.0},
            .isSpecular = true
        };
    }
    return ScatterRecord{
        .scattered = maths::Ray{refractOrigin, *refracted},
        .attenuation = maths::Color{1.0, 1.0, 1.0},
        .isSpecular = true
    };
}

bool Dielectric::castsShadow() const
{
    return false;
}

std::unique_ptr<IMaterial> Dielectric::create(const nlohmann::json &config)
{
    return std::make_unique<Dielectric>(config.at("ior").get<double>());
}

double Dielectric::schlick(const double &cosTheta, const double &ratio)
{
    double r0 = (1.0 - ratio) / (1.0 + ratio);
    r0        = r0 * r0;

    return r0 + ((1.0 - r0) * std::pow(1.0 - cosTheta, 5.0));
}
} // material
} // raytracer
