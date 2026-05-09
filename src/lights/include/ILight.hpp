/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ILight
*/

#pragma once

#include "Color.hpp"
#include "maths_types.hpp"
#include "Vector3.hpp"

namespace raytracer::light {
struct LightSample {
    maths::Vector3d wi;
    maths::Color radiance;
    double distance = 0.0;
};

class ILight {
public:
    virtual ~ILight() = default;

    [[nodiscard]] virtual LightSample sample(const maths::Point3d &p) const = 0;

    [[nodiscard]] virtual bool isDelta() const = 0;
};

} // namespace raytracer::light
