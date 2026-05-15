/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Triangle.hpp
*/

#pragma once

#include "IShape.hpp"
#include "jsonParser.hpp"

namespace raytracer::shape {

class Triangle: public IShape {
public:
    Triangle(maths::Point3d v0, maths::Point3d v1, maths::Point3d v2);
    explicit Triangle(const nlohmann::json &config);

    [[nodiscard]] std::optional<SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3<> objectBound() const override;

    static std::unique_ptr<IShape> create(const nlohmann::json &config);

private:
    maths::Point3d _v0;
    maths::Point3d _v1;
    maths::Point3d _v2;
};

} // namespace raytracer::shape
