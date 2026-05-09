/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Transform.cpp
*/

#include "Transform.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

namespace raytracer::maths::TransformationMatrices {

template <typename T>
const Matrix2x2<T> &scalingMatrix2D(double scaleX, double scaleY) noexcept
{
    static Matrix2x2<T> matrix({{scaleX, 0}, {0, scaleY}});
    return matrix;
}

template <typename T>
const Matrix3x3<T> &scalingMatrix3D(double scaleX, double scaleY) noexcept
{
    static Matrix3x3<T> matrix({{scaleX, 0, 0}, {0, scaleY, 0}, {0, 0, 1}});
    return matrix;
}

template <typename T>
const Matrix2x2<T> &rotationMatrix2D(double angle) noexcept
{
    double cosA = std::cos(angle);
    double sinA = std::sin(angle);

    static Matrix2x2<T> matrix({{cosA, -sinA}, {sinA, cosA}});
    return matrix;
}
template <typename T>
const Matrix3x3<T> &rotationMatrix3D(double angle) noexcept
{
    double cosA = std::cos(angle);
    double sinA = std::sin(angle);

    static Matrix3x3<T> matrix({{cosA, -sinA, 0}, {sinA, cosA, 0}, {0, 0, 1}});
    return matrix;
}

template <typename T>
const Matrix3x3<T> &translationMatrix3D(
    double translateX, double translateY) noexcept
{
    static Matrix3x3<T> matrix(
        {{1, 0, translateX}, {0, 1, translateY}, {0, 0, 1}});
    return matrix;
}

template <typename T>
const Matrix2x2<T> &shearingMatrix2D(double shearX, double shearY) noexcept
{
    static Matrix2x2<T> matrix({{1, shearX}, {shearY, 1}});
    return matrix;
}

template <typename T>
const Matrix3x3<T> &shearingMatrix3D(double shearX, double shearY) noexcept
{
    static Matrix3x3<T> matrix({{1, shearX, 0}, {shearY, 1, 0}, {0, 0, 1}});
    return matrix;
}

template <typename T>
const Matrix2x2<T> &reflectionMatrix2D(bool reflectX, bool reflectY) noexcept
{
    static Matrix2x2<T> matrix({{static_cast<double>(reflectX ? -1 : 1), 0},
        {0, static_cast<double>(reflectY ? -1 : 1)}});
    return matrix;
}

template <typename T>
const Matrix3x3<T> &reflectionMatrix3D(bool reflectX, bool reflectY) noexcept
{
    static Matrix3x3<T> matrix({{static_cast<double>(reflectX ? -1 : 1), 0, 0},
        {0, static_cast<double>(reflectY ? -1 : 1), 0}, {0, 0, 1}});
    return matrix;
}

} // namespace raytracer::maths::TransformationMatrices
