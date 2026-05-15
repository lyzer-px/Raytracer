/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** AreaLight.hpp
*/

#pragma once

#include "ILight.hpp"
#include "jsonParser.hpp"

namespace raytracer::light {

class AreaLight: public ILight {
public:
    explicit AreaLight(const nlohmann::json &config);
    AreaLight(const maths::Point3d &position, const maths::Vector3d &normal,
        double radius, const maths::Color &radiance);

    [[nodiscard]] LightSample sample(const maths::Point3d &p) const override;

    [[nodiscard]] bool isDelta() const override;

    static std::unique_ptr<ILight> create(const nlohmann::json &config);

private:
    maths::Point3d  _position;
    maths::Vector3d _normal;
    double          _radius;
    maths::Color    _radiance;
    maths::Vector3d _tangent;
    maths::Vector3d _bitangent;
};

} // namespace raytracer::light
