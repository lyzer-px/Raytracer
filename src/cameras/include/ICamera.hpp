/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** ICamera
*/

#ifndef RAYTRACER_ICAMERA_HPP
#define RAYTRACER_ICAMERA_HPP
#include "Ray.hpp"

namespace raytracer {
namespace camera {
class ICamera {
public:
    virtual ~ICamera() = default;

    [[nodiscard]] virtual maths::Ray generateRay(const float &u, const float &v) const
    = 0;
};
} // camera
} // raytracer

#endif //RAYTRACER_ICAMERA_HPP
