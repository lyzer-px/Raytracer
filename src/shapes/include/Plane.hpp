/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#pragma once
#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {

class Plane: public IShape {
public:
    explicit Plane(bool reverseOrientation = false);

    explicit Plane(const nlohmann::json &config);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3<> objectBound() const override;

    static std::unique_ptr<IShape> create(const nlohmann::json &config);

private:
    bool _reverseOrientation = false;
};

} // namespace raytracer::shape
