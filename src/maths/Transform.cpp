/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Tranform.cpp
*/

#include "Transform.hpp"
#include <algorithm>

#include "Matrix.hpp"
#include "Matrix4x4.hpp"
#include "Normal.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

Vector2d operator*(const Matrix2x2 &matrix, const Vector2d &vector)
{

    return {(matrix[0][0] * vector.x()) + (matrix[0][1] * vector.y()),
        (matrix[1][0] * vector.x()) + (matrix[1][1] * vector.y())};
}

Vector3d operator*(const Matrix3x3 &matrix, const Vector3d &vector)
{

    return {(matrix[0][0] * vector.x()) + (matrix[0][1] * vector.y()) +
            (matrix[0][2] * vector.z()),
        (matrix[1][0] * vector.x()) + (matrix[1][1] * vector.y()) +
            (matrix[1][2] * vector.z()),
        (matrix[2][0] * vector.x()) + (matrix[2][1] * vector.y()) +
            (matrix[2][2] * vector.z())};
}

Point2d operator*(const Matrix2x2 &matrix, const Point2d &point)
{

    return {(matrix[0][0] * point.x()) + (matrix[0][1] * point.y()),
        (matrix[1][0] * point.x()) + (matrix[1][1] * point.y())};
}

Point3d operator*(const Matrix3x3 &matrix, const Point3d &point)
{
    return {(matrix[0][0] * point.x()) + (matrix[0][1] * point.y()) +
            (matrix[0][2] * point.z()),
        (matrix[1][0] * point.x()) + (matrix[1][1] * point.y()) +
            (matrix[1][2] * point.z()),
        (matrix[2][0] * point.x()) + (matrix[2][1] * point.y()) +
            (matrix[2][2] * point.z())};
}

Transform::Transform(const Matrix4x4 &m): _m(m), _mInv(inverse(m))
{}

Transform::Transform(const Matrix4x4 &m, const Matrix4x4 &mInv): _m(m), _mInv(mInv)
{}

const Matrix4x4 &Transform::getMatrix() const
{
    return _m;

}

const Matrix4x4 &Transform::getInverseMatrix() const
{
    return _mInv;
}

bool Transform::isIdentity() const
{
    return _m.isIdentity();
}

bool Transform::hasScale() const
{
    double s2 = (_m[0][0] * _m[0][0]) + (_m[1][0] * _m[1][0]) + (_m[2][0] * _m[2][0]);
    return s2 != 1.0;
}

bool Transform::swapHandedness() const
{
    double det = _m.determinant();
    return det < 0;
}

Point3d Transform::operator()(const Point3d &p) const
{
    double x = (_m[0][0] * p.x()) + (_m[0][1] * p.y()) + (_m[0][2] * p.z()) + _m[0][3];
    double y = (_m[1][0] * p.x()) + (_m[1][1] * p.y()) + (_m[1][2] * p.z()) + _m[1][3];
    double z = (_m[2][0] * p.x()) + (_m[2][1] * p.y()) + (_m[2][2] * p.z()) + _m[2][3];
    double w = (_m[3][0] * p.x()) + (_m[3][1] * p.y()) + (_m[3][2] * p.z()) + _m[3][3];

    if (w == 1.0)
        return {x, y, z};
    return {x / w, y / w, z / w};
}

Vector3d Transform::operator()(const Vector3d &v) const
{
    return {(_m[0][0] * v.x()) + (_m[0][1] * v.y()) + (_m[0][2] * v.z()),
        (_m[1][0] * v.x()) + (_m[1][1] * v.y()) + (_m[1][2] * v.z()),
        (_m[2][0] * v.x()) + (_m[2][1] * v.y()) + (_m[2][2] * v.z())};
}

Matrix4x4 operator*(const Matrix4x4 &m, const Vector3d &v)
{
    Matrix4x4 result = m;
    std::fill(result[3].begin(), result[3].end(), 0.0);
    for (size_t i = 0; i != 4; i++)
        result[i][3] += (m[i][0] * v.x()) + (m[i][1] * v.y()) + (m[i][2] * v.z());
    return result;
}

Normal3d multiply(const Matrix4x4 &m, const Normal3d &v)
{
    return {(m[0][0] * v.x()) + (m[0][1] * v.y()) + (m[0][2] * v.z()),
        (m[1][0] * v.x()) + (m[1][1] * v.y()) + (m[1][2] * v.z()),
        (m[2][0] * v.x()) + (m[2][1] * v.y()) + (m[2][2] * v.z())};
}

Transform Transform::operator*(const Vector3d &other) const
{
    return {_m * other, _mInv * other};
}

Normal3d Transform::operator()(const Normal3d &n) const
{
    return multiply(Transpose(_mInv), n);
}
} // namespace raytracer::maths
