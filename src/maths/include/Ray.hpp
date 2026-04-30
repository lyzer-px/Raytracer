/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.hpp
*/

#pragma once

#include "Point.hpp"

class Ray {
public:
    explicit Ray(const Point3d &origin, const Vector3d &direction);

    [[nodiscard]] const Point3d &getOrigin() const;

    [[nodiscard]] const UnitVector3 &getDirection() const;

    [[nodiscard]] Vector3d at(double t) const;

private:
    Point3d _origin;
    Vector3d _direction;
};

#include "Ray.tpp"
