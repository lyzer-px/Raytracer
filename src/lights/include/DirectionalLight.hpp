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
    DirectionalLight(const nlohmann::json &config);
    DirectionalLight(const maths::Vector3d &direction, const maths::Color &radiance);

    [[nodiscard]] LightSample sample(const maths::Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

    static void create(const nlohmann::json &config);

private:
    maths::Vector3d _direction;
    maths::Color _radiance;
};
} // light
} // raytracer

#endif //RAYTRACER_DIRECTIONALLIGHT_HPP
