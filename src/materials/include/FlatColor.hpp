/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#pragma once

#include "Color.hpp"
#include "IMaterial.hpp"
#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::material {

class FlatColor: public IMaterial {
public:
    explicit FlatColor(const nlohmann::json &config);
    explicit FlatColor(const maths::Color &color);

    [[nodiscard]] maths::Color
        getColor(const shape::SurfaceInteraction &si) const override; // NOLINT

    static std::unique_ptr<IMaterial> create(const nlohmann::json &config);
private:
    maths::Color _color;
};

} // raytracer::material
