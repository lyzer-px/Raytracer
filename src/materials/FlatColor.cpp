/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#include "include/FlatColor.hpp"

namespace raytracer {
namespace material {
FlatColor::FlatColor(const Color &color): _color{color}
{}

Color FlatColor::getColor(const shape::SurfaceInteraction &) const // NOLINT
{
    return _color;
}
} // material
} // raytracer