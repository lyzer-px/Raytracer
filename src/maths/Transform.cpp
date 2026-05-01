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

    return {
        (matrix[0][0] * vector.x()) + (matrix[0][1] * vector.y()),
        (matrix[1][0] * vector.x()) + (matrix[1][1] * vector.y())
    };

}

Vector3d operator*(const Matrix3x3 &matrix, const Vector3d &vector)
{

    return {
    (matrix[0][0] * vector.x()) + (matrix[0][1] * vector.y()) + (matrix[0][2] * vector.z()),
    (matrix[1][0] * vector.x()) + (matrix[1][1] * vector.y()) + (matrix[1][2] * vector.z()),
    (matrix[2][0] * vector.x()) + (matrix[2][1] * vector.y()) + (matrix[2][2] * vector.z())
    };
}

Point2d operator*(const Matrix2x2 &matrix, const Point2d &point)
{

    return {
        (matrix[0][0] * point.x()) + (matrix[0][1] * point.y()),
        (matrix[1][0] * point.x()) + (matrix[1][1] * point.y())
    };
}

Point3d operator*(const Matrix3x3 &matrix, const Point3d &point)
{
    return {
        (matrix[0][0] * point.x()) + (matrix[0][1] * point.y()) + (matrix[0][2] * point.z()),
        (matrix[1][0] * point.x()) + (matrix[1][1] * point.y()) + (matrix[1][2] * point.z()),
        (matrix[2][0] * point.x()) + (matrix[2][1] * point.y()) + (matrix[2][2] * point.z())
    };
}
