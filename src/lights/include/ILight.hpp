/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ILight
*/

#ifndef RAYTRACER_ILIGHT_HPP
#define RAYTRACER_ILIGHT_HPP
#include "Color.hpp"
#include "maths_types.hpp"

namespace raytracer {
namespace light {
struct LightSample {
    Vector3f wi;
    Color radiance;
    double distance = 0.0;
};

class ILight {
public:
    virtual ~ILight() = default;

    [[nodiscard]] virtual LightSample sample(const Point3f &p) const = 0;

    [[nodiscard]] virtual bool isDelta() const = 0;
};

} // light
} // raytracer

#endif //RAYTRACER_ILIGHT_HPP
