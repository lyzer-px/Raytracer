/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#pragma once
#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {
class Sphere: public IShape {
public:
    explicit Sphere(const nlohmann::json &config);

    explicit Sphere(double radius, bool reverseOrientation = false);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3<> objectBound() const override;

    static std::unique_ptr<IShape> create(const nlohmann::json &config);

private:
    double _radius;
    bool _reverseOrientation = false;

    [[nodiscard]] std::optional<double> solveQuadratic(
        const maths::Ray &ray) const;
};

} // namespace raytracer::shape
