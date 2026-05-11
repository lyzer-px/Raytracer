/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** DirectionalLight
*/

#pragma once
#include "ILight.hpp"
#include "jsonParser.hpp"

namespace raytracer::light {
class DirectionalLight: public ILight {
public:
    DirectionalLight(const nlohmann::json &config);
    DirectionalLight(
        const maths::Vector3d &direction, const maths::Color &radiance);

    [[nodiscard]] LightSample sample(const maths::Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

    static std::unique_ptr<ILight> create(const nlohmann::json &config);

private:
    maths::Vector3d _direction;
    maths::Color _radiance;
};
} // namespace raytracer::light
