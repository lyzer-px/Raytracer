/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** math_types.hpp
*/

#pragma once

#include "Vector.hpp"
#include "Point.hpp"
#include "Normal.hpp"

namespace raytracer::maths {

// Vectors
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

// Points
using Point2f = Point2<float>;
using Point2i = Point2<int>;
using Point3f = Point3<float>;
using Point3i = Point3<int>;

// Normals
using Normal3f = Normal3<float>;

} // namespace raytracer::maths

