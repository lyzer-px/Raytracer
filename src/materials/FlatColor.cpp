/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#include <memory>
#include "include/FlatColor.hpp"
#include "IMaterial.hpp"

namespace raytracer::material {
FlatColor::FlatColor(const nlohmann::json &config) : _color{
    config["color"][0].get<double>(),
    config["color"][1].get<double>(),
    config["color"][2].get<double>()
} {}
FlatColor::FlatColor(const maths::Color &color): _color{color}
{}

maths::Color FlatColor::getColor(const shape::SurfaceInteraction &) const // NOLINT
{
    return _color;
}

std::unique_ptr<IMaterial> FlatColor::create(const nlohmann::json &config)
{
    if (!config.contains("albedo"))
        throw std::runtime_error("FlatColor material requires 'albedo' field in config");
    return std::make_unique<FlatColor>(raytracer::maths::Color(
        config["albedo"][0].get<double>(),
        config["albedo"][1].get<double>(),
        config["albedo"][2].get<double>()
    ));

}
} // raytracer::material