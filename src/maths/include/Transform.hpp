/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class declaration
*/

#pragma once

#include <cmath>
#include <ctime>
#include "Matrix.hpp"
#include "Point.hpp"
#include "Vector.hpp"


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

Vector<3> operator*(const Matrix<3, 3> &matrix, Vector<3> &vector);
Vector<2> operator*(const Matrix<2, 2> &matrix, Vector<2> &vector);

Point<3> operator*(const Matrix3x3 &matrix, Point<3> &point);
Point<2> operator*(const Matrix2x2 &matrix, Point<2> &point);


}