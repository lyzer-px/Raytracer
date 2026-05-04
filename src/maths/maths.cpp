/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** maths.cpp
*/

#include <cstdlib>
#include "maths.hpp"
#include "Vector.hpp"

namespace raytracer::maths {

void coordinateSystem(const Vector3d &v1, Vector3d &v2, Vector3d &v3)
{
    if (std::abs(v1.x()) > std::abs(v1.y()))
        v2 = Vector3d(-v1.z(), 0, v1.x()).normalize();
    else
        v2 = Vector3d(0, v1.z(), -v1.y()).normalize();
    v3 = v1.cross(v2);
}

Vector3d sphericalDirection(double sinTheta, double cosTheta, double phi)
{
    return {
        sinTheta * std::cos(phi),
        sinTheta * std::sin(phi),
        cosTheta
    };
}

Vector3d sphericalDirection(double sinTheta, double cosTheta, double phi,
                             const Vector3d &x, const Vector3d &y, const Vector3d &z)
{
    return {
        (x * (sinTheta * std::cos(phi))) + (y * (sinTheta * std::sin(phi))) + (z * cosTheta)
    };
}

double sphericalTheta(const Vector3d &v)
{
    return std::acos(std::ranges::clamp(v.z(), -1.0, 1.0));
}

double sphericalPhi(const Vector3d &v)
{
    const double phi = std::atan2(v.y(), v.x());
    return (phi < 0) ? (phi + (2.0 * M_PI)) : phi;
}

} // namespace raytracer::maths
