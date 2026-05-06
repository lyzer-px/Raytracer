/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** GeometricPrimitive
*/

#ifndef RAYTRACER_GEOMETRICPRIMITIVE_HPP
#define RAYTRACER_GEOMETRICPRIMITIVE_HPP
#include <memory>

#include "IPrimitive.hpp"

namespace raytracer {
namespace shape {
class GeometricPrimitive: public IPrimitive {
public:
    explicit GeometricPrimitive(std::unique_ptr<IShape> &shape,
        std::unique_ptr<material::IMaterial> &material);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] const material::IMaterial *material() const override;

private:
    std::unique_ptr<IShape> _shape;
    std::unique_ptr<material::IMaterial> _material;
};
} // shape
} // raytracer

#endif //RAYTRACER_GEOMETRICPRIMITIVE_HPP
