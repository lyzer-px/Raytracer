/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class declaration
*/

#pragma once

#include "Bounds3.hpp"
#include "Bounds2.hpp"
#include "Matrix.hpp"
#include "Matrix4x4.hpp"
#include "Normal.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

template <typename T> class Vector2;

template <typename T> class Vector3;

template <typename T> class Point2;

template <typename T> class Point3;

Vector2<double> operator*(
    const Matrix2x2 &matrix, const Vector2<double> &vector);
Vector3<double> operator*(
    const Matrix3x3 &matrix, const Vector3<double> &vector);

Point2<double> operator*(const Matrix2x2 &matrix, const Point2<double> &point);
Point3<double> operator*(const Matrix3x3 &matrix, const Point3<double> &point);

namespace TransformationMatrices {

// References for transformation matrices

const Matrix3x3 &scalingMatrix3D(double scaleX, double scaleY) noexcept;
const Matrix2x2 &scalingMatrix2D(double scaleX, double scaleY) noexcept;

const Matrix2x2 &rotationMatrix2D(double angle) noexcept;
const Matrix3x3 &rotationMatrix3D(double angle) noexcept;

const Matrix3x3 &translationMatrix3D(
    double translateX, double translateY) noexcept;

const Matrix3x3 &shearingMatrix3D(double shearX, double shearY) noexcept;
const Matrix2x2 &shearingMatrix2D(double shearX, double shearY) noexcept;

const Matrix3x3 &reflectionMatrix3D(bool reflectX, bool reflectY) noexcept;
const Matrix2x2 &reflectionMatrix2D(bool reflectX, bool reflectY) noexcept;

} // namespace TransformationMatrices

class Transform {
public:
    // Constructors
    Transform();                            // identity
    explicit Transform(const Matrix4x4 &m); // inverse computed internally
    Transform(const Matrix4x4 &m, const Matrix4x4 &mInv); // both provided

    // Matrix accessors
    [[nodiscard]] const Matrix4x4 &getMatrix() const;
    [[nodiscard]] const Matrix4x4 &getInverseMatrix() const;

    // Properties
    [[nodiscard]] bool isIdentity() const;
    [[nodiscard]] bool hasScale() const; // true if any axis is non-uniformly scaled
    [[nodiscard]] bool swapHandedness()
        const; // true if det(m) < 0 -- flips surface orientation

    // Application operators -- each type transforms differently
    Point3d operator()(
        const Point3d &p) const; // applies full 4x4 including translation
    Vector3d operator()(const Vector3d &v) const; // w=0 -- translation ignored
    Normal3d operator()(
        const Normal3d &n) const; // applies Transpose(mInv) upper-left 3x3
    Ray operator()(const Ray &r)
        const; // transforms o as Point, d as Vector; tMax unchanged
    Bounds3f operator()(
        const Bounds3f &b) const; // transforms all 8 corners, recomputes AABB

    // Composition -- produces a new Transform whose matrix is m1*m2
    Transform operator*(const Transform &other) const;
    Transform operator*(const Vector3d &other) const;

    bool operator==(const Transform &other) const;
    bool operator!=(const Transform &other) const;

private:
    Matrix4x4 _m;
    Matrix4x4 _mInv;
};

// Free functions -- O(1), no matrix inversion needed
Transform inverse(const Transform &t);   // swaps m and mInv
Transform transpose(const Transform &t); // transposes both m and mInv

Normal3d multiply(const Matrix4x4 &m, const Normal3d &v);

} // namespace raytracer::maths
