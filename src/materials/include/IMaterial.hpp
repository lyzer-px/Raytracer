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

struct ScatterRecord {
    maths::Ray scattered;
    maths::Color attenuation;
    bool isSpecular = false;
};

class IMaterial {
public:
    virtual ~IMaterial() = default;

    [[nodiscard]] virtual maths::Color getColor(
        const shape::SurfaceInteraction &si) const = 0; // NOLINT

    [[nodiscard]] virtual std::optional<ScatterRecord> scatter(
        const maths::Ray &ray, const shape::SurfaceInteraction &si) const = 0;

    [[nodiscard]] virtual maths::Color emitted(
        const shape::SurfaceInteraction &si) const;
};

} // namespace raytracer::material
