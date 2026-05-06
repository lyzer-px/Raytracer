/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#include "include/FlatColor.hpp"

#include <memory>

#include "IMaterial.hpp"
#include "Serializer.hpp"

namespace raytracer::material {
FlatColor::FlatColor(const nlohmann::json &config):
    _color{config["color"].get<raytracer::maths::Color>()}
{}
FlatColor::FlatColor(const maths::Color &color): _color{color}
{}

maths::Color FlatColor::getColor(
    const shape::SurfaceInteraction &) const // NOLINT
{
    return _color;
}

std::unique_ptr<IMaterial> FlatColor::create(const nlohmann::json &config)
{
    if (!config.contains("albedo"))
        throw std::runtime_error(
            "FlatColor material requires 'albedo' field in config");
    return std::make_unique<FlatColor>(
        config["albedo"].get<raytracer::maths::Color>());
}
} // namespace raytracer::material
