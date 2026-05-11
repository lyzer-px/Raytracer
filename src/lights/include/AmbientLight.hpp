/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** AmbientLight
*/

#pragma once

#include "ILight.hpp"
#include "jsonParser.hpp"

namespace raytracer::light {

class AmbientLight: public ILight {
public:
    explicit AmbientLight(const nlohmann::json &config);
    explicit AmbientLight(const maths::Color &radiance);

    [[nodiscard]] LightSample sample(const maths::Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

    static std::unique_ptr<ILight> create(const nlohmann::json &config);

private:
    maths::Color _radiance;
};

} // light
