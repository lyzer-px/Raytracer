/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#pragma once
#include "IShape.hpp"

namespace raytracer::shape {

class Sphere: public IShape {
public:
    Sphere(const nlohmann::json &config);
    Sphere(const maths::Point3d &center, const float &radius);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    static std::unique_ptr<Sphere> create(const nlohmann::json &config);

private:
    [[nodiscard]] std::optional<double> solveQuadratic(const maths::Ray &ray) const;

    maths::Point3d _center;
    float _radius;
};

} // shape
} // raytracer

#endif //RAYTRACER_SPHERE_HPP
