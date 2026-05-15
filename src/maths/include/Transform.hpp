/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class declaration
*/

#pragma once

#include "Bounds3.hpp"
#include "Matrix.hpp"
#include "Normal.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

template <typename T> class Vector2;

template <typename T> class Vector3;

template <typename T> class Point2;

template <typename T> class Point3;

template <typename T>
Vector2<T> operator*(const Matrix2x2<T> &matrix, const Vector2<T> &vector);
template <typename T>
Vector3<T> operator*(const Matrix3x3<T> &matrix, const Vector3<T> &vector);
template <typename T>
Point2<T> operator*(const Matrix2x2<T> &matrix, const Point2<T> &point);
template <typename T>
Point3<T> operator*(const Matrix3x3<T> &matrix, const Point3<T> &point);

namespace TransformationMatrices {

// References for transformation matrices
template <typename T>
const Matrix3x3<T> &scalingMatrix3D(double scaleX, double scaleY) noexcept;
template <typename T>
const Matrix2x2<T> &scalingMatrix2D(double scaleX, double scaleY) noexcept;

template <typename T>
const Matrix2x2<T> &rotationMatrix2D(double angle) noexcept;
template <typename T>
const Matrix3x3<T> &rotationMatrix3D(double angle) noexcept;

template <typename T>
const Matrix3x3<T> &translationMatrix3D(
    double translateX, double translateY) noexcept;

template <typename T>
const Matrix3x3<T> &shearingMatrix3D(double shearX, double shearY) noexcept;
template <typename T>
const Matrix2x2<T> &shearingMatrix2D(double shearX, double shearY) noexcept;

template <typename T>
const Matrix3x3<T> &reflectionMatrix3D(bool reflectX, bool reflectY) noexcept;
template <typename T>
const Matrix2x2<T> &reflectionMatrix2D(bool reflectX, bool reflectY) noexcept;

} // namespace TransformationMatrices
template <typename T> class Transform {
public:
    // Constructors
    Transform();                               // identity
    explicit Transform(const Matrix4x4<T> &m); // inverse computed internally
    Transform(const Matrix4x4<T> &m, const Matrix4x4<T> &mInv); // both provided

    // Matrix accessors
    [[nodiscard]] const Matrix4x4<T> &getMatrix() const;
    [[nodiscard]] const Matrix4x4<T> &getInverseMatrix() const;

    // Properties
    [[nodiscard]] bool isIdentity() const;
    [[nodiscard]] bool
        hasScale() const; // true if any axis is non-uniformly scaled
    [[nodiscard]] bool swapHandedness()
        const; // true if det(m) < 0 -- flips surface orientation

    Transform<T> translate(const Vector3<T> &delta) const;
    Transform<T> scale(const Vector3<T> &scale) const;
    Transform<T> rotateX(double angle) const;
    Transform<T> rotateY(double angle) const;
    Transform<T> rotateZ(double angle) const;
    Transform<T> rotate(double angle, const Vector3<T> &axis) const;

    // Application operators -- each type transforms differently
    Point3<T> operator()(
        const Point3<T> &p) const; // applies full 4x4 including translation
    Vector3<T> operator()(
        const Vector3<T> &v) const; // w=0 -- translation ignored
    Normal3<T> operator()(
        const Normal3<T> &n) const; // applies Transpose(mInv) upper-left 3x3
    Ray operator()(const Ray &r)
        const; // transforms o as Point, d as Vector; tMax unchanged
    Bounds3<T> operator()(
        const Bounds3<T> &b) const; // transforms all 8 corners, recomputes AABB

    // Composition -- produces a new Transform whose matrix is m1*m2
    Transform operator*(const Transform &other) const;
    Transform operator*(const Vector3<T> &other) const;

    bool operator==(const Transform &other) const;
    bool operator!=(const Transform &other) const;

private:
    Matrix4x4<T> _m;
    Matrix4x4<T> _mInv;
};

// Free functions -- O(1), no matrix inversion needed
template <typename T>
Transform<T> inverse(
    const Transform<T> &t); // returns a new Transform with m and mInv swapped
template <typename T>
Transform<T> transpose(const Transform<T> &t); // transposes both m and mInv

template <typename T>
Normal3<T> multiply(const Matrix4x4<T> &m, const Normal3<T> &v);

} // namespace raytracer::maths

#include "Transform.tpp"
