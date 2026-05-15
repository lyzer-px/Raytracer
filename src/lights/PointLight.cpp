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
    _intensity{config.at("intensity").get<maths::Vector3d>()}
{}

PointLight::PointLight(
    const maths::Point3d &position, const maths::Vector3d &intensity):
    _position{position}, _intensity{intensity}
{}

LightSample PointLight::sample(const maths::Point3d &p) const
{
    const maths::Vector3d toLight = _position - p;
    const double dist             = toLight.length();
    const maths::Vector3d wi      = -toLight.normalize();
    const double dist2            = dist * dist;

    return LightSample{
        .wi       = wi,
        .radiance = maths::Color{_intensity.x() / dist2,
                                 _intensity.y() / dist2,
                                 _intensity.z() / dist2},
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
