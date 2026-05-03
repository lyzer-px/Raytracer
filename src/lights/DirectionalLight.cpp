/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

namespace raytracer {
namespace light {
DirectionalLight::DirectionalLight(const Vector3d &direction,
    const Color &radiance): _direction{direction}, _radiance{radiance}
{}

LightSample DirectionalLight::sample(const Point3d &) const
{
    return LightSample{
        .wi = -_direction,
        .radiance = _radiance,
        .distance = std::numeric_limits<double>::infinity()
    };
}

bool DirectionalLight::isDelta() const
{
    return true;
}
} // light
} // raytracer
