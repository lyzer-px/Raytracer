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

Vector2d operator*(const Matrix2x2 &matrix, const Vector2d &vector)
{
    Vector2d out;

    out.x = (matrix[0][0] * vector.x) + (matrix[0][1] * vector.y);
    out.y = (matrix[1][0] * vector.x) + (matrix[1][1] * vector.y);
    return out;
}

Vector3d operator*(const Matrix3x3 &matrix, const Vector3d &vector)
{
    Vector3d out;

    out.x = (matrix[0][0] * vector.x) + (matrix[0][1] * vector.y) + (matrix[0][2] * vector.z);
    out.y = (matrix[1][0] * vector.x) + (matrix[1][1] * vector.y) + (matrix[1][2] * vector.z);
    out.z = (matrix[2][0] * vector.x) + (matrix[2][1] * vector.y) + (matrix[2][2] * vector.z);
    return out;
}

Point2d operator*(const Matrix2x2 &matrix, const Point2d &point)
{
    Point2d out;

    out.x = (matrix[0][0] * point.x) + (matrix[0][1] * point.y);
    out.y = (matrix[1][0] * point.x) + (matrix[1][1] * point.y);
    return out;
}

Point3d operator*(const Matrix3x3 &matrix, const Point3d &point)
{
    Point3d out;

    out.x = (matrix[0][0] * point.x) + (matrix[0][1] * point.y) + (matrix[0][2] * point.z);
    out.y = (matrix[1][0] * point.x) + (matrix[1][1] * point.y) + (matrix[1][2] * point.z);
    out.z = (matrix[2][0] * point.x) + (matrix[2][1] * point.y) + (matrix[2][2] * point.z);
    return out;
}
