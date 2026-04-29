/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Tranform.cpp
*/

#include "Transform.hpp"

namespace Transform {

Vector<2> operator*(const Matrix<2, 2> &matrix, Vector<2> &vector)
{
    Vector<2> result;
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            result[i] += matrix[i][j] * vector[j];
    return result;
}

Vector<3> operator*(const Matrix<3, 3> &matrix, Vector<3> &vector)
{
    Vector<3> result;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            result[i] += matrix[i][j] * vector[j];
    return result;
}

Point<2> operator*(const Matrix2x2 &matrix, Point<2> &point)
{
    Point<2> result;
    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 2; j++)
            result[i] += matrix[i][j] * point[j];
    return result;
}

Point<3> operator*(const Matrix3x3 &matrix, Point<3> &point)
{
    Point<3> result;
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            result[i] += matrix[i][j] * point[j];
    return result;
}


}