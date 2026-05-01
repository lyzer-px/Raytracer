/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.hpp
*/

#pragma once

#include <limits>

#include "Vector.hpp"
#include "Point.hpp"

class Ray {
public:
    Ray();
    Ray(const Point3d& origin, const Vector3d& direction,
        double tMax = std::numeric_limits<double>::infinity());

    Point3d operator()(double time) const;  // P(t) = o + t*d -- replaces at(t)
    bool    hasNaN() const;

    Point3d       origin;
    Vector3d      direction;  // direction (caller responsible for normalization)
    mutable double tMax;   // reduced by each intersection hit -- enables BVH early exit
};

#include "Ray.tpp"
