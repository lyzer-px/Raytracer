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

template <typename T> using Matrix4x4 = Matrix<4, 4, T>;

template <typename T>
Matrix4x4<T> Transpose(const Matrix4x4<T> &other); // NOLINT

template <typename T>
Matrix4x4<T> operator*(const Matrix4x4<T> &m, const Vector3<T> &v); // NOLINT

template <typename T> Matrix4x4<T> inverse(const Matrix4x4<T> &other); // NOLINT
} // namespace raytracer::maths
