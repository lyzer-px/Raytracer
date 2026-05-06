/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Matrix4x4.hpp
*/

#pragma once
#include "Matrix.hpp"

namespace raytracer::maths {

using Matrix4x4 = Matrix<4, 4>;

Matrix4x4 Transpose(const Matrix4x4 &other); // NOLINT

Matrix4x4 Inverse(const Matrix4x4 &other); // NOLINT
} // namespace raytracer::maths