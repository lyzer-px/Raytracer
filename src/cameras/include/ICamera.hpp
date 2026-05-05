/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ICamera
*/

#pragma once
#include "Ray.hpp"
#include "jsonParser.hpp"

namespace raytracer::camera {
class ICamera {
public:
    virtual ~ICamera() = default;

    [[nodiscard]] virtual maths::Ray generateRay(const float &u, const float &v) const
    = 0;
};
} // namespace raytracer::camera
