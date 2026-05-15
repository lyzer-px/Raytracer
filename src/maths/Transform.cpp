/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Transform class implementation
*/

#include "Transform.hpp"

#include <cmath>

namespace raytracer::maths {

namespace {
const auto K_IDENTITY = Matrix4x4<double>{
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};
} // namespace

Transform::Transform(): _m(K_IDENTITY), _mInv(K_IDENTITY)
{}

Transform::Transform(const Matrix4x4<double> &m):
    _m(m), _mInv(maths::inverse(m))
{}

Transform::Transform(const Matrix4x4<double> &m, const Matrix4x4<double> &mInv):
    _m(m), _mInv(mInv)
{}

const Matrix4x4<double> &Transform::getMatrix() const
{
    return _m;
}

const Matrix4x4<double> &Transform::getInverseMatrix() const
{
    return _mInv;
}

bool Transform::isIdentity() const
{
    return _m.isIdentity();
}

bool Transform::hasScale() const
{
    const double la2 =
        (_m[0][0] * _m[0][0]) + (_m[1][0] * _m[1][0]) + (_m[2][0] * _m[2][0]);
    const double lb2 =
        (_m[0][1] * _m[0][1]) + (_m[1][1] * _m[1][1]) + (_m[2][1] * _m[2][1]);
    const double lc2 =
        (_m[0][2] * _m[0][2]) + (_m[1][2] * _m[1][2]) + (_m[2][2] * _m[2][2]);
    return std::abs(la2 - 1.0) > 1e-3 || std::abs(lb2 - 1.0) > 1e-3 ||
        std::abs(lc2 - 1.0) > 1e-3;
}

bool Transform::swapHandedness() const
{
    return _m.determinant() < 0;
}

Transform Transform::translate(const Vector3<double> &delta)
{
    auto m    = Matrix4x4<double>{{1.0, 0.0, 0.0, delta.x()},
           {0.0, 1.0, 0.0, delta.y()}, {0.0, 0.0, 1.0, delta.z()},
           {0.0, 0.0, 0.0, 1.0}};
    auto mInv = Matrix4x4<double>{{1.0, 0.0, 0.0, -delta.x()},
        {0.0, 1.0, 0.0, -delta.y()}, {0.0, 0.0, 1.0, -delta.z()},
        {0.0, 0.0, 0.0, 1.0}};
    return {m, mInv};
}

Transform Transform::scale(double x, double y, double z)
{
    auto m = Matrix4x4<double>{{x, 0.0, 0.0, 0.0}, {0.0, y, 0.0, 0.0},
        {0.0, 0.0, z, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    auto mInv =
        Matrix4x4<double>{{1.0 / x, 0.0, 0.0, 0.0}, {0.0, 1.0 / y, 0.0, 0.0},
            {0.0, 0.0, 1.0 / z, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    return {m, mInv};
}

Transform Transform::rotateX(double angle)
{
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    auto m    = Matrix4x4<double>{{1.0, 0.0, 0.0, 0.0}, {0.0, c, -s, 0.0},
           {0.0, s, c, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    auto mInv = Matrix4x4<double>{{1.0, 0.0, 0.0, 0.0}, {0.0, c, s, 0.0},
        {0.0, -s, c, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    return {m, mInv};
}

Transform Transform::rotateY(double angle)
{
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    auto m    = Matrix4x4<double>{{c, 0.0, s, 0.0}, {0.0, 1.0, 0.0, 0.0},
           {-s, 0.0, c, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    auto mInv = Matrix4x4<double>{{c, 0.0, -s, 0.0}, {0.0, 1.0, 0.0, 0.0},
        {s, 0.0, c, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    return {m, mInv};
}

Transform Transform::rotateZ(double angle)
{
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    auto m    = Matrix4x4<double>{{c, -s, 0.0, 0.0}, {s, c, 0.0, 0.0},
           {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    auto mInv = Matrix4x4<double>{{c, s, 0.0, 0.0}, {-s, c, 0.0, 0.0},
        {0.0, 0.0, 1.0, 0.0}, {0.0, 0.0, 0.0, 1.0}};
    return {m, mInv};
}

Transform Transform::rotate(double angle, const Vector3<double> &axis)
{
    Vector3<double> a = axis.normalize();
    const double c = std::cos(angle);
    const double s = std::sin(angle);
    const double t = 1.0 - c;
    const double x = a.x();
    const double y = a.y();
    const double z = a.z();

    auto m = Matrix4x4<double>{
        {(t * x * x) + c, (t * x * y) - (s * z), (t * x * z) + (s * y), 0.0},
        {(t * x * y) + (s * z), (t * y * y) + c, (t * y * z) - (s * x), 0.0},
        {(t * x * z) - (s * y), (t * y * z) + (s * x), (t * z * z) + c, 0.0},
        {0.0, 0.0, 0.0, 1.0}};
    auto mInv = Matrix4x4<double>{
        {(t * x * x) + c, (t * x * y) + (s * z), (t * x * z) - (s * y), 0.0},
        {(t * x * y) - (s * z), (t * y * y) + c, (t * y * z) + (s * x), 0.0},
        {(t * x * z) + (s * y), (t * y * z) - (s * x), (t * z * z) + c, 0.0},
        {0.0, 0.0, 0.0, 1.0}};
    return {m, mInv};
}

Transform Transform::inverse(const Transform &t)
{
    return {t.getInverseMatrix(), t.getMatrix()};
}

Transform Transform::transpose(const Transform &t)
{
    const auto &m    = t.getMatrix();
    const auto &mInv = t.getInverseMatrix();
    Matrix4x4<double> mT{};
    Matrix4x4<double> mInvT{};
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j) {
            mT[j][i]    = m[i][j];
            mInvT[j][i] = mInv[i][j];
        }
    return {mT, mInvT};
}

Point3<double> Transform::operator()(const Point3<double> &p) const
{
    double x =
        (_m[0][0] * p.x()) + (_m[0][1] * p.y()) + (_m[0][2] * p.z()) + _m[0][3];
    double y =
        (_m[1][0] * p.x()) + (_m[1][1] * p.y()) + (_m[1][2] * p.z()) + _m[1][3];
    double z =
        (_m[2][0] * p.x()) + (_m[2][1] * p.y()) + (_m[2][2] * p.z()) + _m[2][3];
    double w =
        (_m[3][0] * p.x()) + (_m[3][1] * p.y()) + (_m[3][2] * p.z()) + _m[3][3];
    if (w == 1.0)
        return {x, y, z};
    return {x / w, y / w, z / w};
}

Vector3<double> Transform::operator()(const Vector3<double> &v) const
{
    return {(_m[0][0] * v.x()) + (_m[0][1] * v.y()) + (_m[0][2] * v.z()),
        (_m[1][0] * v.x()) + (_m[1][1] * v.y()) + (_m[1][2] * v.z()),
        (_m[2][0] * v.x()) + (_m[2][1] * v.y()) + (_m[2][2] * v.z())};
}

Normal3<double> Transform::operator()(const Normal3<double> &n) const
{
    return {
        (_mInv[0][0] * n.x()) + (_mInv[1][0] * n.y()) + (_mInv[2][0] * n.z()),
        (_mInv[0][1] * n.x()) + (_mInv[1][1] * n.y()) + (_mInv[2][1] * n.z()),
        (_mInv[0][2] * n.x()) + (_mInv[1][2] * n.y()) + (_mInv[2][2] * n.z())};
}

Ray Transform::operator()(const Ray &r) const
{
    return {(*this)(r.origin), (*this)(r.direction), r.tMax};
}

Bounds3<> Transform::operator()(const Bounds3<> &b) const
{
    const double x0 = b.pMin.x();
    const double y0 = b.pMin.y();
    const double z0 = b.pMin.z();
    const double x1 = b.pMax.x();
    const double y1 = b.pMax.y();
    const double z1 = b.pMax.z();
    Bounds3 ret((*this)(Point3(x0, y0, z0)));
    ret = ret.boundsUnion((*this)(Point3(x1, y0, z0)));
    ret = ret.boundsUnion((*this)(Point3(x0, y1, z0)));
    ret = ret.boundsUnion((*this)(Point3(x0, y0, z1)));
    ret = ret.boundsUnion((*this)(Point3(x1, y1, z0)));
    ret = ret.boundsUnion((*this)(Point3(x1, y0, z1)));
    ret = ret.boundsUnion((*this)(Point3(x0, y1, z1)));
    ret = ret.boundsUnion((*this)(Point3(x1, y1, z1)));
    return ret;
}

Transform Transform::operator*(const Transform &other) const
{
    return {_m * other._m, other._mInv * _mInv};
}

bool Transform::operator==(const Transform &other) const
{
    return _m == other._m && _mInv == other._mInv;
}

bool Transform::operator!=(const Transform &other) const
{
    return !(*this == other);
}

} // namespace raytracer::maths
