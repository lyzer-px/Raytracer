/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Cone.hpp
*/

#pragma once

#include <optional>

#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {

class Cone: public IShape {
public:
    explicit Cone(const nlohmann::json &config);

    explicit Cone(double radius, double zMin, double zMax,
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
    double _k;
    bool _reverseOrientation = false;

    enum class HitPart { LATERAL, BASE_CAP };

    struct Hit {
        double t;
        HitPart part;
    };

    [[nodiscard]] std::optional<Hit> findLateralHit(
        const maths::Ray &ray) const;

    [[nodiscard]] std::optional<Hit> findBaseCap(
        const maths::Ray &ray) const;

    [[nodiscard]] SurfaceInteraction buildInteraction(
        const maths::Ray &ray, const Hit &hit) const;
};

} // namespace raytracer::shape
