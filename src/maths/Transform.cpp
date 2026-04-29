/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Tranform.cpp
*/

#include "Transform.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Point.hpp"

Vector<2, double, false> operator*(const Matrix2x2 &matrix, const Vector<2, double, false> &vector)
{
    std::array<double, 2> out{0.0, 0.0};
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            out[i] += matrix[i][j] * vector[j];
    return Vector<2, double, false>(out);
}

Vector<3, double, false> operator*(const Matrix3x3 &matrix, const Vector<3, double, false> &vector)
{
    std::array<double, 3> out{0.0, 0.0, 0.0};
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            out[i] += matrix[i][j] * vector[j];
    return Vector<3, double, false>(out);
}

Point<2, double> operator*(const Matrix2x2 &matrix, const Point<2, double> &point)
{
    std::array<double, 2> out{0.0, 0.0};
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            out[i] += matrix[i][j] * point[j];
    return Point<2, double>(out);
}

Point<3, double> operator*(const Matrix3x3 &matrix, const Point<3, double> &point)
{
    std::array<double, 3> out{0.0, 0.0, 0.0};
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            out[i] += matrix[i][j] * point[j];
    return Point<3, double>(out);
}
