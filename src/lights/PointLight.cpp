/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** PointLight.cpp
*/

#include "PointLight.hpp"

#include "Serializer.hpp"

namespace raytracer::light {

PointLight::PointLight(const nlohmann::json &config):
    _position{config.at("position").get<maths::Point3d>()},
    _intensity{config.at("intensity").get<maths::Color>()}
{}

PointLight::PointLight(
    const maths::Point3d &position, const maths::Color &intensity):
    _position{position}, _intensity{intensity}
{}

LightSample PointLight::sample(const maths::Point3d &p) const
{
    const maths::Vector3d toLight = _position - p;
    const double dist             = toLight.length();
    const maths::Vector3d wi      = toLight.normalize();

    return LightSample{
        .wi       = wi,
        .radiance = _intensity / (dist * dist),
        .distance = dist};
}

bool PointLight::isDelta() const
{
    return true;
}

std::unique_ptr<ILight> PointLight::create(const nlohmann::json &config)
{
    return std::make_unique<PointLight>(config);
}

} // namespace raytracer::light
