/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Cylinder.hpp
*/

#pragma once

#include <optional>

#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {

class Cylinder: public IShape {
public:
    explicit Cylinder(const nlohmann::json &config);

    explicit Cylinder(double radius, double zMin, double zMax,
        bool reverseOrientation = false);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3<> objectBound() const override;

    static std::unique_ptr<IShape> create(const nlohmann::json &config);

private:
    double _radius;
    double _zMin;
    double _zMax;
    bool _reverseOrientation = false;

    enum class HitPart { LATERAL, BOTTOM_CAP, TOP_CAP };

    struct Hit {
        double t;
        HitPart part;
    };

    [[nodiscard]] std::optional<Hit> findLateralHit(
        const maths::Ray &ray) const;

    [[nodiscard]] std::optional<Hit> findCapHit(
        const maths::Ray &ray, double zTarget, HitPart part) const;

    [[nodiscard]] SurfaceInteraction buildInteraction(
        const maths::Ray &ray, const Hit &hit) const;
};

} // namespace raytracer::shape
