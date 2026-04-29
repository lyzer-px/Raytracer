/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class declaration
*/

#pragma once

#include "Matrix.hpp"

template<std::size_t N, typename T, bool PrecomputeNorm>
class Vector;

template<std::size_t N, typename T>
class Point;

Vector<3, double, false> operator*(const Matrix3x3 &matrix, const Vector<3, double, false> &vector);
Vector<2, double, false> operator*(const Matrix2x2 &matrix, const Vector<2, double, false> &vector);

Point<3, double> operator*(const Matrix3x3 &matrix, const Point<3, double> &point);
Point<2, double> operator*(const Matrix2x2 &matrix, const Point<2, double> &point);

namespace Transform {

// References for transformation matrices

const Matrix3x3 &scalingMatrix3D(double scaleX, double scaleY) noexcept;
const Matrix2x2 &scalingMatrix2D(double scaleX, double scaleY) noexcept;

const Matrix2x2 &rotationMatrix2D(double angle) noexcept;
const Matrix3x3 &rotationMatrix3D(double angle) noexcept;

const Matrix3x3 &translationMatrix3D(double translateX, double translateY) noexcept;

const Matrix3x3 &shearingMatrix3D(double shearX, double shearY) noexcept;
const Matrix2x2 &shearingMatrix2D(double shearX, double shearY) noexcept;

const Matrix3x3 &reflectionMatrix3D(bool reflectX, bool reflectY) noexcept;
const Matrix2x2 &reflectionMatrix2D(bool reflectX, bool reflectY) noexcept;

}