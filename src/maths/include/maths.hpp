/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** maths.hpp
*/

#pragma once

#include "maths_types.hpp"
#include "Matrix.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Normal.hpp"
#include "Color.hpp"
#include "Ray.hpp"
#include "Transform.hpp"

namespace raytracer::maths {

// Build an orthonormal basis (v2, v3) from a single unit vector v1.
// Used by PerspectiveCamera to derive right and up vectors from the forward direction.
void coordinateSystem(const Vector3d& v1, Vector3d &v2, Vector3d &v3);

// Spherical direction from polar angles theta and phi, in world space.
Vector3d sphericalDirection(double sinTheta, double cosTheta, double phi);

// Spherical direction in a given local basis (x, y, z).
Vector3d sphericalDirection(double sinTheta, double cosTheta, double phi,
    const Vector3d &x, const Vector3d &y, const Vector3d &z);

// Polar angle theta of a direction vector (angle from the z-axis).
double sphericalTheta(const Vector3d &v);

// Azimuthal angle phi of a direction vector (angle in the xy-plane).
double sphericalPhi(const Vector3d &v);

template <typename T>
double randomNumber()
{
    static std::uniform_real_distribution<T> distribution(0.0, 1.0);
    static std::mt19937 generator(std::random_device{}());

    return distribution(generator);
}

template <typename T>
T randomNumber(const T &low, const T &high)
{
    return low + (high - low) * randomNumber<T>();
}

} // namespace raytracer::maths
