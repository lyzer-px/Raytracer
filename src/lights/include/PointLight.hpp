/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** PointLight.hpp
*/

#pragma once

#include "ILight.hpp"
#include "jsonParser.hpp"
#include "maths_types.hpp"

namespace raytracer::light {

class PointLight: public ILight {
public:
    explicit PointLight(const nlohmann::json &config);
    PointLight(const maths::Point3d &position, const maths::Color &intensity);

    [[nodiscard]] LightSample sample(const maths::Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

    static std::unique_ptr<ILight> create(const nlohmann::json &config);

private:
    maths::Point3d _position;
    maths::Color   _intensity;
};

} // namespace raytracer::light
