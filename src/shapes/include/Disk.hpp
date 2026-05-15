/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Disk.hpp
*/

#pragma once

#include <memory>
#include <optional>

#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {

class Disk: public IShape {
public:
    explicit Disk(const nlohmann::json &config);
    explicit Disk(double radius, double innerRadius = 0.0,
        bool reverseOrientation = false);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3<> objectBound() const override;

    static std::unique_ptr<IShape> create(const nlohmann::json &config);

private:
    double _radius;
    double _innerRadius      = 0.0;
    bool _reverseOrientation = false;
};

} // namespace raytracer::shape
