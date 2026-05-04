/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#ifndef RAYTRACER_AMBIENTLIGHT_HPP
#define RAYTRACER_AMBIENTLIGHT_HPP

#include "ILight.hpp"

namespace raytracer {
namespace light {

class AmbientLight: public ILight {
public:
    explicit AmbientLight(const maths::Color &radiance);

    [[nodiscard]] LightSample sample(const maths::Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

private:
    maths::Color _radiance;
};

} // light
} // raytracer

#endif //RAYTRACER_AMBIENTLIGHT_HPP
