/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Matrix4x4.hpp
*/

#pragma once
#include "Matrix.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

using Matrix4x4 = Matrix<4, 4>;

Matrix4x4 Transpose(const Matrix4x4 &other); // NOLINT

Matrix4x4 operator*(const Matrix4x4 &m, const Vector3d &v); // NOLINT

Matrix4x4 inverse(const Matrix4x4 &other); // NOLINT
} // namespace raytracer::maths
