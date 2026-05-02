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

class ILight {};

} // light
} // raytracer

#endif //RAYTRACER_ILIGHT_HPP
