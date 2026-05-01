/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Sphere
*/

#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP
#include "IShape.hpp"

namespace raytracer {
namespace shape {

class Sphere: public IShape {
public:
    explicit Sphere(const Point3d &origin, const double &radius);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(const Ray &ray,
        float tMin, float tMax) const override;

private:
    Point3d _origin;
    double _radius;
};

} // shape
} // raytracer

#endif //RAYTRACER_SPHERE_HPP
