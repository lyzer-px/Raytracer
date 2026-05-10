/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Transform.cpp
*/

#include "Transform.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

namespace raytracer::maths::Transform {

const Matrix2x2 &scalingMatrix2D(double scaleX, double scaleY) noexcept
{
    static Matrix2x2 matrix({{scaleX, 0}, {0, scaleY}});
    return matrix;
}

const Matrix3x3 &scalingMatrix3D(double scaleX, double scaleY) noexcept
{
    static Matrix3x3 matrix({{scaleX, 0, 0}, {0, scaleY, 0}, {0, 0, 1}});
    return matrix;
}

const Matrix2x2 &rotationMatrix2D(double angle) noexcept
{
    double cosA = std::cos(angle);
    double sinA = std::sin(angle);

    static Matrix2x2 matrix({{cosA, -sinA}, {sinA, cosA}});
    return matrix;
}

const Matrix3x3 &rotationMatrix3D(double angle) noexcept
{
    double cosA = std::cos(angle);
    double sinA = std::sin(angle);

    static Matrix3x3 matrix({{cosA, -sinA, 0}, {sinA, cosA, 0}, {0, 0, 1}});
    return matrix;
}

const Matrix3x3 &translationMatrix3D(
    double translateX, double translateY) noexcept
{
    static Matrix3x3 matrix(
        {{1, 0, translateX}, {0, 1, translateY}, {0, 0, 1}});
    return matrix;
}

const Matrix2x2 &shearingMatrix2D(double shearX, double shearY) noexcept
{
    static Matrix2x2 matrix({{1, shearX}, {shearY, 1}});
    return matrix;
}

const Matrix3x3 &shearingMatrix3D(double shearX, double shearY) noexcept
{
    static Matrix3x3 matrix({{1, shearX, 0}, {shearY, 1, 0}, {0, 0, 1}});
    return matrix;
}

const Matrix2x2 &reflectionMatrix2D(bool reflectX, bool reflectY) noexcept
{
    static Matrix2x2 matrix({{static_cast<double>(reflectX ? -1 : 1), 0},
        {0, static_cast<double>(reflectY ? -1 : 1)}});
    return matrix;
}

const Matrix3x3 &reflectionMatrix3D(bool reflectX, bool reflectY) noexcept
{
    static Matrix3x3 matrix({{static_cast<double>(reflectX ? -1 : 1), 0, 0},
        {0, static_cast<double>(reflectY ? -1 : 1), 0}, {0, 0, 1}});
    return matrix;
}

} // namespace raytracer::maths::Transform
