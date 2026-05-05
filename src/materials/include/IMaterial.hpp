/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#pragma once

#include "Color.hpp"
#include "IShape.hpp"

namespace raytracer::material {

class IMaterial {
public:
    virtual ~IMaterial() = default;

    [[nodiscard]] virtual maths::Color getColor(
        const shape::SurfaceInteraction &si) const = 0; //NOLINT
};

} // namespace raytracer::material
