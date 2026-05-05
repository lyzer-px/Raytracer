/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#include "include/FlatColor.hpp"

namespace raytracer {
namespace material {
FlatColor::FlatColor(const maths::Color &color): _color{color}
{}

maths::Color FlatColor::getColor(const shape::SurfaceInteraction &) const // NOLINT
{
    return _color;
}

std::optional<ScatterRecord> FlatColor::scatter(const maths::Ray &,
    const shape::SurfaceInteraction &) const
{
    return std::nullopt;
}
} // material
} // raytracer