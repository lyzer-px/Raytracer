/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Dielectric
*/

#ifndef RAYTRACER_DIELECTRIC_HPP
#define RAYTRACER_DIELECTRIC_HPP
#include "IMaterial.hpp"

namespace raytracer {
namespace material {

class Dielectric: public IMaterial {
public:
    explicit Dielectric(const double &ior);

    [[nodiscard]] std::optional<ScatterRecord> scatter(const maths::Ray &ray,
        const shape::SurfaceInteraction &si) const override;

private:
    double _ior;

    static double schlick(const double &cosTheta, const double &ratio);
};

} // material
} // raytracer

#endif //RAYTRACER_DIELECTRIC_HPP
