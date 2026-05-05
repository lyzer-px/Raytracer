/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#ifndef RAYTRACER_IMATERIAL_HPP
#define RAYTRACER_IMATERIAL_HPP

#include "Color.hpp"
#include "IShape.hpp"

namespace raytracer {
namespace material {
struct ScatterRecord {
    maths::Ray scattered;
    maths::Color attenuation;
    bool isSpecular = false;
};

class IMaterial {
public:
    virtual ~IMaterial() = default;

    [[nodiscard]] virtual maths::Color getColor(
        const shape::SurfaceInteraction &si) const = 0; //NOLINT

    [[nodiscard]] virtual std::optional<ScatterRecord> scatter(
        const maths::Ray &ray, const shape::SurfaceInteraction &si) const = 0;

    [[nodiscard]] virtual maths::Color emitted(
        const shape::SurfaceInteraction &si) const;
};

} // material
} // raytracer

#endif //RAYTRACER_IMATERIAL_HPP
