/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class declaration
*/

#pragma once

#include "Bounds3.hpp"
#include "Matrix4x4.hpp"
#include "Normal.hpp"
#include "Point.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

class Transform {
public:
    Transform();
    explicit Transform(const Matrix4x4<double> &m);
    Transform(const Matrix4x4<double> &m, const Matrix4x4<double> &mInv);

    [[nodiscard]] const Matrix4x4<double> &getMatrix() const;
    [[nodiscard]] const Matrix4x4<double> &getInverseMatrix() const;

    [[nodiscard]] bool isIdentity() const;
    [[nodiscard]] bool hasScale() const;
    [[nodiscard]] bool swapHandedness() const;

    static Transform translate(const Vector3<double> &delta);
    static Transform scale(double x, double y, double z);
    static Transform rotateX(double angle);
    static Transform rotateY(double angle);
    static Transform rotateZ(double angle);
    static Transform rotate(double angle, const Vector3<double> &axis);


    static Transform inverse(const Transform &t);
    static Transform transpose(const Transform &t);

    Point3<double>  operator()(const Point3<double> &p)  const;
    Vector3<double> operator()(const Vector3<double> &v) const;
    Normal3<double> operator()(const Normal3<double> &n) const;
    Ray             operator()(const Ray &r)             const;
    Bounds3<double> operator()(const Bounds3<double> &b) const;

    Transform operator*(const Transform &other) const;

    bool operator==(const Transform &other) const;
    bool operator!=(const Transform &other) const;

private:
    Matrix4x4<double> _m;
    Matrix4x4<double> _mInv;
};

} // namespace raytracer::maths
