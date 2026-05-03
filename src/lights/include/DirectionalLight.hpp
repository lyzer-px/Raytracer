/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#ifndef RAYTRACER_DIRECTIONALLIGHT_HPP
#define RAYTRACER_DIRECTIONALLIGHT_HPP
#include "ILight.hpp"

namespace raytracer {
namespace light {
class DirectionalLight: public ILight {
public:
    DirectionalLight(const Vector3d &direction, const Color &radiance);

    [[nodiscard]] LightSample sample(const Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

private:
    Vector3d _direction;
    Color _radiance;
};
} // light
} // raytracer

#endif //RAYTRACER_DIRECTIONALLIGHT_HPP
