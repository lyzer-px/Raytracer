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

Ray::Ray()
    : tMax(std::numeric_limits<double>::infinity())
{
}

Ray::Ray(const Point3d &origin, const Vector3d &direction, double tMax)
    : o(origin), d(direction), tMax(tMax)
{
}

Point3d Ray::operator()(double time) const
{
    Point3d result;

    result.x = o.x + (d.x * time);
    result.y = o.y + (d.y * time);
    result.z = o.z + (d.z * time);
    return result;
}

bool Ray::hasNaN() const
{
    return std::isnan(o.x) || std::isnan(o.y) || std::isnan(o.z) ||
        std::isnan(d.x) || std::isnan(d.y) || std::isnan(d.z) ||
        std::isnan(tMax);
}

RayDifferential::RayDifferential()
        : hasDifferentials(false)
{
}

RayDifferential::RayDifferential(const Point3d &origin,
    const Vector3d &direction, double tMax)
        : Ray(origin, direction, tMax), hasDifferentials(false)
{
}

RayDifferential::RayDifferential(const Ray &ray)
        : Ray(ray), hasDifferentials(false)
{
}

void RayDifferential::scaleDifferentials(double scale)
{
    if (!hasDifferentials)
        return;

    Point3d newRxOrigin;
    Point3d newRyOrigin;
    Vector3d newRxDirection;
    Vector3d newRyDirection;

    newRxOrigin.x = o.x + ((rxOrigin.x - o.x) * scale);
    newRxOrigin.y = o.y + ((rxOrigin.y - o.y) * scale);
    newRxOrigin.z = o.z + ((rxOrigin.z - o.z) * scale);
    newRyOrigin.x = o.x + ((ryOrigin.x - o.x) * scale);
    newRyOrigin.y = o.y + ((ryOrigin.y - o.y) * scale);
    newRyOrigin.z = o.z + ((ryOrigin.z - o.z) * scale);
    newRxDirection.x = d.x + ((rxDirection.x - d.x) * scale);
    newRxDirection.y = d.y + ((rxDirection.y - d.y) * scale);
    newRxDirection.z = d.z + ((rxDirection.z - d.z) * scale);
    newRyDirection.x = d.x + ((ryDirection.x - d.x) * scale);
    newRyDirection.y = d.y + ((ryDirection.y - d.y) * scale);
    newRyDirection.z = d.z + ((ryDirection.z - d.z) * scale);

    rxOrigin = newRxOrigin;
    ryOrigin = newRyOrigin;
    rxDirection = newRxDirection;
    ryDirection = newRyDirection;
}

inline bool RayDifferential::hasNaN() const
{
    return Ray::hasNaN() || std::isnan(rxOrigin.x) || std::isnan(rxOrigin.y) ||
        std::isnan(rxOrigin.z) || std::isnan(ryOrigin.x) ||
        std::isnan(ryOrigin.y) || std::isnan(ryOrigin.z) ||
        std::isnan(rxDirection.x) || std::isnan(rxDirection.y) ||
        std::isnan(rxDirection.z) || std::isnan(ryDirection.x) ||
        std::isnan(ryDirection.y) || std::isnan(ryDirection.z);
}
