/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Emissive.cpp
*/

#include "Emissive.hpp"

namespace raytracer::material {

Emissive::Emissive(const maths::Color &radiance): _radiance{radiance}
{}

std::optional<ScatterRecord> Emissive::scatter(
    const maths::Ray &, const shape::SurfaceInteraction &) const
{
    return std::nullopt;
}

maths::Color Emissive::emitted(const shape::SurfaceInteraction &) const
{
    return _radiance;
}

std::unique_ptr<IMaterial> Emissive::create(const nlohmann::json &config)
{
    return std::make_unique<Emissive>(
        config.at("radiance").get<maths::Color>());
}

} // namespace raytracer::material
