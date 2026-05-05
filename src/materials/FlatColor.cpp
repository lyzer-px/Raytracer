/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#include "include/FlatColor.hpp"

namespace raytracer::material {
FlatColor::FlatColor(const nlohmann::json &config) : _color{config["color"]} {}
FlatColor::FlatColor(const maths::Color &color): _color{color}
{}

maths::Color FlatColor::getColor(const shape::SurfaceInteraction &) const // NOLINT
{
    return _color;
}
} // raytracer::material