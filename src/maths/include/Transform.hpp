/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class declaration
*/

#pragma once

#include "Matrix.hpp"

namespace raytracer::maths {

template <typename T>
class Vector2;

template <typename T>
class Vector3;

template <typename T>
class Point2;

template <typename T>
class Point3;

Vector2<double> operator*(const Matrix2x2 &matrix, const Vector2<double> &vector);
Vector3<double> operator*(const Matrix3x3 &matrix, const Vector3<double> &vector);

Point2<double> operator*(const Matrix2x2 &matrix, const Point2<double> &point);
Point3<double> operator*(const Matrix3x3 &matrix, const Point3<double> &point);

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

} // namespace raytracer::maths
