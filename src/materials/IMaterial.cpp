/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#include "include/IMaterial.hpp"

namespace raytracer {
namespace material {
maths::Color IMaterial::emitted(const shape::SurfaceInteraction &) const
{
    return maths::Color{0.0, 0.0, 0.0};
}
} // material
} // raytracer