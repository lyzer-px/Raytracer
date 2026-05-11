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
    Sphere(const nlohmann::json &config);
    Sphere(const Point3d &center, const double &radius);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    static std::unique_ptr<IShape> create(const nlohmann::json &config);

private:
    [[nodiscard]] std::optional<double> solveQuadratic(
        const maths::Ray &ray) const;

    Point3d _center;
    double _radius;
};

} // namespace raytracer::shape
