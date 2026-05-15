/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Cylinder.hpp
*/

#pragma once

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

    enum class HitPart {
        Lateral,
        BottomCap,
        TopCap
    };

    struct Hit {
        double t;
        HitPart part;
    };
};

} // namespace raytracer::shape
