/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IPrimitive
*/

#pragma once
#include <optional>

#include "IMaterial.hpp"
#include "IShape.hpp"

namespace raytracer::shape {
class IPrimitive {
public:
    virtual ~IPrimitive() = default;

    [[nodiscard]] virtual std::optional<SurfaceInteraction> intersect(
        const maths::Ray& ray) const = 0;

    [[nodiscard]] virtual bool intersectP(const maths::Ray& ray) const = 0;

    [[nodiscard]] virtual const material::IMaterial* material() const = 0;
};
} // namespace raytracer::shape
