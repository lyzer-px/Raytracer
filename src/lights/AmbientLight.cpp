/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#include <memory>
#include "ILight.hpp"
#include "Serializer.hpp"
#include "AmbientLight.hpp"

namespace raytracer::light {

AmbientLight::AmbientLight(const nlohmann::json &config) :
_radiance{config["radiance"].get<raytracer::maths::Color>()} {}

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

std::unique_ptr<ILight> AmbientLight::create(const nlohmann::json &config)
{
    return std::make_unique<AmbientLight>(nlohmann::json(config));
}

} // raytracer::light
