/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.hpp
*/

#pragma once

#include "Point.hpp"
#include "Vector.hpp"

class Ray {
public:
Ray(const Point3f& origin, const UnitVector3& direction);

    const Point3f& getOrigin() const;
    const UnitVector3& getDirection() const;

    Point3f at(double t) const;

private:
    Point3f _origin;
    UnitVector3 _direction; // must be normalized
};

#include "Ray.tpp"