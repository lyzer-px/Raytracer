/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"

namespace raytracer {
namespace light {
DirectionalLight::DirectionalLight(const maths::Vector3d &direction,
    const maths::Color &radiance): _direction{direction.normalize()}, _radiance{radiance}
{}

LightSample DirectionalLight::sample(const maths::Point3d &) const
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
