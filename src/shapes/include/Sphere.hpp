/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP
#include "IShape.hpp"

namespace raytracer { // NOLINT
namespace shape {

class Sphere: public IShape {
public:
    Sphere(const Point3d &center, const float &radius);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const Ray &ray) const override;

    [[nodiscard]] bool intersectP(const Ray &ray) const override;

private:
    [[nodiscard]] std::optional<double> solveQuadratic(const Ray &ray) const;

    Point3d _center;
    float _radius;
};

} // shape
} // raytracer

#endif //RAYTRACER_SPHERE_HPP
