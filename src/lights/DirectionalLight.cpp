/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#include "DirectionalLight.hpp"
#include <memory>

namespace raytracer::light {
DirectionalLight::DirectionalLight(const nlohmann::json &config) :
_direction{config["direction"]}, _radiance{config["radiance"]} {}
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

std::unique_ptr<DirectionalLight> DirectionalLight::create(const nlohmann::json &config)
{
    return std::make_unique<DirectionalLight>(nlohmann::json(config));
}
} // raytracer::light
