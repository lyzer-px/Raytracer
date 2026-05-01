/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.tpp
*/

#pragma once

#include <cmath>
#include <limits>
#include "Ray.hpp"
#include "Point.hpp"

Ray::Ray() : tMax(std::numeric_limits<double>::infinity()) {}

Ray::Ray(const Point3d &origin, const Vector3d &direction, double tMax)
    : origin(origin), direction(direction), tMax(tMax) {}

Point3d Ray::operator()(double time) const
{
    return origin + (direction * time);
}

bool Ray::hasNaN() const
{
    return
    std::isnan(origin.x()) || std::isnan(origin.y()) || std::isnan(origin.z()) ||
    std::isnan(direction.x()) || std::isnan(direction.y()) || std::isnan(direction.z()) ||
    std::isnan(tMax);
}