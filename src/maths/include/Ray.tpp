/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.tpp
*/

#pragma once

#include "Ray.hpp"

namespace raytracer::maths {

inline Ray::Ray(): tMax(std::numeric_limits<double>::infinity())
{}

inline Ray::Ray(const Point3d &origin, const Vector3d &direction, double tMax):
    origin(origin), direction(direction), tMax(tMax)
{
    if (direction.hasNaN())
        throw std::invalid_argument("Direction vector contains NaN");
}

inline Point3d Ray::operator()(double time) const
{
    return origin + (direction * time);
}

inline bool Ray::hasNaN() const
{
    return std::isnan(origin.x()) || std::isnan(origin.y()) ||
        std::isnan(origin.z()) || std::isnan(direction.x()) ||
        std::isnan(direction.y()) || std::isnan(direction.z()) ||
        std::isnan(tMax);
}

} // namespace raytracer::maths
