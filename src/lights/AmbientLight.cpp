/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#include "AmbientLight.hpp"

namespace raytracer {
namespace light {
AmbientLight::AmbientLight(const Color &radiance): _radiance{radiance}
{}

LightSample AmbientLight::sample(const Point3d &) const
{
    return LightSample {
        .wi = Vector3d{},
        .radiance = _radiance,
        .distance = 0.0
    };
}

bool AmbientLight::isDelta() const
{
    return false;
}
} // light
} // raytracer
