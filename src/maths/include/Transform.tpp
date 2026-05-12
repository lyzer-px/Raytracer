/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Tranform.cpp
*/

#pragma once

#include "Transform.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

template <typename T>
Vector2<T> operator*(const Matrix2x2<T> &matrix, const Vector2<T> &vector)
{

    return {(matrix[0][0] * vector.x()) + (matrix[0][1] * vector.y()),
        (matrix[1][0] * vector.x()) + (matrix[1][1] * vector.y())};
}

template <typename T>
Vector3<T> operator*(const Matrix3x3<T> &matrix, const Vector3<T> &vector)
{

    return {(matrix[0][0] * vector.x()) + (matrix[0][1] * vector.y()) +
            (matrix[0][2] * vector.z()),
        (matrix[1][0] * vector.x()) + (matrix[1][1] * vector.y()) +
            (matrix[1][2] * vector.z()),
        (matrix[2][0] * vector.x()) + (matrix[2][1] * vector.y()) +
            (matrix[2][2] * vector.z())};
}

template <typename T>
Point2<T> operator*(const Matrix2x2<T> &matrix, const Point2<T> &point)
{

    return {(matrix[0][0] * point.x()) + (matrix[0][1] * point.y()),
        (matrix[1][0] * point.x()) + (matrix[1][1] * point.y())};
}

template <typename T>
Point3<T> operator*(const Matrix3x3<T> &matrix, const Point3<T> &point)
{
    return {(matrix[0][0] * point.x()) + (matrix[0][1] * point.y()) +
            (matrix[0][2] * point.z()),
        (matrix[1][0] * point.x()) + (matrix[1][1] * point.y()) +
            (matrix[1][2] * point.z()),
        (matrix[2][0] * point.x()) + (matrix[2][1] * point.y()) +
            (matrix[2][2] * point.z())};
}

// Transform class implementation

template <typename T>
Transform<T>::Transform(const Matrix4x4<T> &m): _m(m), _mInv(inverse(m))
{}

template <typename T>
Transform<T>::Transform(const Matrix4x4<T> &m, const Matrix4x4<T> &mInv):
    _m(m), _mInv(mInv)
{}

template <typename T> const Matrix4x4<T> &Transform<T>::getMatrix() const
{
    return _m;
}

template <typename T> const Matrix4x4<T> &Transform<T>::getInverseMatrix() const
{
    return _mInv;
}

template <typename T> bool Transform<T>::isIdentity() const
{
    return _m.isIdentity();
}

template <typename T> bool Transform<T>::hasScale() const
{
    T s2 =
        (_m[0][0] * _m[0][0]) + (_m[1][0] * _m[1][0]) + (_m[2][0] * _m[2][0]);
    return s2 != 1.0;
}

template <typename T> bool Transform<T>::swapHandedness() const
{
    T det = _m.determinant();
    return det < 0;
}

template <typename T>
Transform<T> Transform<T>::translate(const Vector3<T> &delta) const
{
    return Transform<T>(
        TransformationMatrices::translationMatrix3D<T>(delta.x(), delta.y()));
}

template <typename T>
Transform<T> Transform<T>::scale(const Vector3<T> &scale) const
{
    return Transform<T>({scale.x(), 0, 0, 0}, {0, scale.y(), 0, 0},
        {0, 0, scale.z(), 0}, {0, 0, 0, 1});
}

template <typename T> Transform<T> Transform<T>::rotateX(double angle) const
{
    return Transform<T>(
        Matrix4x4<T>({1, 0, 0, 0}, {0, std::cos(angle), -std::sin(angle), 0},
            {0, std::sin(angle), std::cos(angle), 0}, {0, 0, 0, 1}));
}

template <typename T> Transform<T> Transform<T>::rotateY(double angle) const
{
    return Transform<T>(Matrix4x4<T>({std::cos(angle), 0, std::sin(angle), 0},
        {0, 1, 0, 0}, {-std::sin(angle), 0, std::cos(angle), 0}, {0, 0, 0, 1}));
}

template <typename T> Transform<T> Transform<T>::rotateZ(double angle) const
{
    return Transform<T>(Matrix4x4<T>({std::cos(angle), -std::sin(angle), 0, 0},
        {std::sin(angle), std::cos(angle), 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}));
}

template <typename T>
Transform<T> Transform<T>::rotate(double angle, const Vector3<T> &axis) const
{
    Vector3<T> normalizedAxis = axis.normalize();
    T cosTheta                = std::cos(angle);
    T sinTheta                = std::sin(angle);
    Transform<T> t1           = rotateX(axis.x());
    Transform<T> t2           = rotateY(axis.y());
    Transform<T> t3           = rotateZ(axis.z());
    Transform<T> rotation     = t3 * t2 * t1;
    return {rotation.getMatrix(), transpose(rotation).getMatrix()};
}

template <typename T>
Point3<T> Transform<T>::operator()(const Point3<T> &p) const
{
    T x =
        (_m[0][0] * p.x()) + (_m[0][1] * p.y()) + (_m[0][2] * p.z()) + _m[0][3];
    T y =
        (_m[1][0] * p.x()) + (_m[1][1] * p.y()) + (_m[1][2] * p.z()) + _m[1][3];
    T z =
        (_m[2][0] * p.x()) + (_m[2][1] * p.y()) + (_m[2][2] * p.z()) + _m[2][3];
    T w =
        (_m[3][0] * p.x()) + (_m[3][1] * p.y()) + (_m[3][2] * p.z()) + _m[3][3];

    if (w == 1.0)
        return {x, y, z};
    return {x / w, y / w, z / w};
}

template <typename T>
Vector3<T> Transform<T>::operator()(const Vector3<T> &v) const
{
    return {(_m[0][0] * v.x()) + (_m[0][1] * v.y()) + (_m[0][2] * v.z()),
        (_m[1][0] * v.x()) + (_m[1][1] * v.y()) + (_m[1][2] * v.z()),
        (_m[2][0] * v.x()) + (_m[2][1] * v.y()) + (_m[2][2] * v.z())};
}

template <typename T>
Transform<T> Transform<T>::operator*(const Vector3<T> &other) const
{
    return {_m * other, _mInv * other};
}

template <typename T>
Normal3<T> Transform<T>::operator()(const Normal3<T> &n) const
{
    return {
        (_mInv[0][0] * n.x()) + (_mInv[1][0] * n.y()) + (_mInv[2][0] * n.z()),
        (_mInv[0][1] * n.x()) + (_mInv[1][1] * n.y()) + (_mInv[2][1] * n.z()),
        (_mInv[0][2] * n.x()) + (_mInv[1][2] * n.y()) + (_mInv[2][2] * n.z())};
}

template <typename T> Ray Transform<T>::operator()(const Ray &r) const
{
    Point3d newOrigin     = (*this)(r.origin);
    Vector3d newDirection = (*this)(r.direction);
    return {newOrigin, newDirection, r.tMax};
}

template <typename T>
Bounds3<T> Transform<T>::operator()(const Bounds3<T> &b) const
{
    const Transform &m = *this;
    Bounds3<T> ret(m(Point3<T>(b.pMin.x(), b.pMin.y(), b.pMin.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMax.x(), b.pMin.y(), b.pMin.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMin.x(), b.pMax.y(), b.pMin.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMin.x(), b.pMin.y(), b.pMax.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMax.x(), b.pMax.y(), b.pMin.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMax.x(), b.pMin.y(), b.pMax.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMin.x(), b.pMax.y(), b.pMax.z())));
    ret = b.boundsUnion(ret, m(Point3<T>(b.pMax.x(), b.pMax.y(), b.pMax.z())));
    return ret;
}

template <typename T>
Transform<T> operator*(const Transform<T> &t1, const Transform<T> &t2)
{
    return {t1.getMatrix() * t2.getMatrix(),
        t2.getInverseMatrix() * t1.getInverseMatrix()};
}

template <typename T>
Transform<T> operator*(const Transform<T> &t, const Vector3<T> &v)
{
    return {t.getMatrix() * v, t.getInverseMatrix() * v};
}

template <typename T>
bool Transform<T>::operator==(const Transform &other) const
{
    return _m == other._m && _mInv == other._mInv;
}

template <typename T>
bool Transform<T>::operator!=(const Transform &other) const
{
    return !(*this == other);
}

template <typename T>
Transform<T> Transform<T>::operator*(const Transform &other) const
{
    return {_m * other._m, other._mInv * _mInv};
}

template <typename T> Transform<T> transpose(const Transform<T> &t)
{
    return {transpose(t.getMatrix()), transpose(t.getInverseMatrix())};
}

template <typename T> Transform<T> inverse(const Transform<T> &t)
{
    return {t.getInverseMatrix(), t.getMatrix()};
}
} // namespace raytracer::maths
