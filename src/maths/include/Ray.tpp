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

Ray::Ray() : tMax(std::numeric_limits<double>::infinity()) {}

Ray::Ray(const Point3d &origin, const Vector3d &direction, double tMax)
    : o(origin), d(direction), tMax(tMax) {}

Point3d Ray::operator()(double time) const
{
    Point3d result;

    result.x = o.x() + (d.x() * time);
    result.y = o.y() + (d.y() * time);
    result.z = o.z() + (d.z() * time);
    return result;
}

bool Ray::hasNaN() const
{
    return
    std::isnan(o.x()) || std::isnan(o.y()) || std::isnan(o.z()) ||
    std::isnan(d.x()) || std::isnan(d.y()) || std::isnan(d.z()) ||
    std::isnan(tMax);
}