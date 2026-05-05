/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Metal
*/

#ifndef RAYTRACER_METAL_HPP
#define RAYTRACER_METAL_HPP

#include "IMaterial.hpp"

namespace raytracer {
namespace material {

class Metal: public IMaterial {
public:
    explicit Metal(const maths::Color &albedo, const double &roughness);

    explicit Metal(const maths::Color &eta, const maths::Vector3d &k,
        const double &roughness);

    [[nodiscard]] std::optional<ScatterRecord> scatter(const maths::Ray &ray,
        const shape::SurfaceInteraction &si) const override;

private:
    maths::Color _eta;
    maths::Vector3d _k; // extinction or attenuation coef per channel
    double _roughness;
    bool _physical;

    maths::Color fresnelConductor(const double &cosTheta) const;
};

} // material
} // raytracer

#endif //RAYTRACER_METAL_HPP
