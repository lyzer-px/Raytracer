/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Emissive.hpp
*/

#pragma once

#include "IMaterial.hpp"
#include "Serializer.hpp"

namespace raytracer::material {

class Emissive: public IMaterial {
public:
    explicit Emissive(const maths::Color &radiance);

    [[nodiscard]] std::optional<ScatterRecord> scatter(const maths::Ray &ray,
        const shape::SurfaceInteraction &si) const override;

    [[nodiscard]] maths::Color emitted(
        const shape::SurfaceInteraction &si) const override;

    [[nodiscard]] static std::unique_ptr<IMaterial> create(
        const nlohmann::json &config);

private:
    maths::Color _radiance;
};

} // namespace raytracer::material
