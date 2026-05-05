/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** GeometricPrimitive
*/

#pragma once
#include <memory>

#include "IPrimitive.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {
class GeometricPrimitive: public IPrimitive {
public:
    explicit GeometricPrimitive(const nlohmann::json &config);
    explicit GeometricPrimitive(std::unique_ptr<IShape> &shape,
        std::unique_ptr<material::IMaterial> &material);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] const material::IMaterial *material() const override;

    static std::unique_ptr<GeometricPrimitive> create(const nlohmann::json &config);

private:
    std::unique_ptr<IShape> _shape;
    std::unique_ptr<material::IMaterial> _material;
};
} // raytracer::shape
