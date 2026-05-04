/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#include "AmbientLight.hpp"

namespace raytracer {
namespace light {
AmbientLight::AmbientLight(const maths::Color &radiance): _radiance{radiance}
{}

LightSample AmbientLight::sample(const maths::Point3d &) const
{
    return LightSample {
        .wi = maths::Vector3d{},
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
