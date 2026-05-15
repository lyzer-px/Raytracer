/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AreaLight.cpp
*/

#include "AreaLight.hpp"

#include <cmath>

#include "Serializer.hpp"
#include "maths.hpp"

namespace raytracer::light {

AreaLight::AreaLight(const nlohmann::json &config):
    _position{config.at("position").get<maths::Point3d>()},
    _normal{config.at("normal").get<maths::Vector3d>().normalize()},
    _radius{config.at("radius").get<double>()},
    _radiance{config.at("radiance").get<maths::Color>()}
{
    maths::coordinateSystem(_normal, _tangent, _bitangent);
}

AreaLight::AreaLight(const maths::Point3d &position,
    const maths::Vector3d &normal, double radius, const maths::Color &radiance):
    _position{position},
    _normal{normal.normalize()},
    _radius{radius},
    _radiance{radiance}
{
    maths::coordinateSystem(_normal, _tangent, _bitangent);
}

LightSample AreaLight::sample(const maths::Point3d &p) const
{
    const double r     = _radius * std::sqrt(maths::randomNumber<double>());
    const double theta = 2.0 * M_PI * maths::randomNumber<double>();
    const maths::Point3d lightPoint =
        _position + (_tangent * std::cos(theta) + _bitangent * std::sin(theta)) * r;

    const maths::Vector3d toLight = lightPoint - p;
    const double dist             = toLight.length();
    const maths::Vector3d wi      = -(toLight / dist);

    const double cosTheta = std::max(0.0, _normal.dot(wi));
    const double area     = M_PI * _radius * _radius;

    return LightSample{
        .wi       = wi,
        .radiance = _radiance * (cosTheta * area / (dist * dist)),
        .distance = dist};
}

bool AreaLight::isDelta() const
{
    return true;
}

std::unique_ptr<ILight> AreaLight::create(const nlohmann::json &config)
{
    return std::make_unique<AreaLight>(config);
}

} // namespace raytracer::light
