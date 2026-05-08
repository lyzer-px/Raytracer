/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector class implementation
*/

#pragma once

#include "maths.hpp"
#include "Vector3.hpp"

namespace raytracer::maths {

template <typename T> Vector3<T>::Vector3(): Vector<Vector3, 3, T>()
{}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) noexcept: Vector<Vector3, 3, T>()
{

    this->_data[0] = x;
    this->_data[1] = y;
    this->_data[2] = z;
}

template <typename T>
template <typename U>
Vector3<T>::Vector3(const Point3<U> &v):
    Vector<Vector3, 3, T>(
        {static_cast<T>(v.x()), static_cast<T>(v.y()), static_cast<T>(v.z())})
{}

template <typename T>
template <typename U>
Vector3<T>::Vector3(const Normal3<U> &v):
    Vector<Vector3, 3, T>(
        {static_cast<T>(v.x()), static_cast<T>(v.y()), static_cast<T>(v.z())})
{}

template <typename T>
Vector3<T> Vector3<T>::randomUnitVector() noexcept
{
    // static std::random_device randomDevice;
    // static std::default_random_engine engine(randomDevice());
    // static std::uniform_real_distribution<T> distribute(static_cast<T>(-1),
    //     static_cast<T>(1));
    static constexpr T low  = static_cast<T>(-1);
    static constexpr T high = static_cast<T>(1);

    Vector3d res{
        randomNumber(low, high),
        randomNumber(low, high),
        randomNumber(low, high)
    };

    if (res.dot(res) < static_cast<T>(1))
        return res.normalize();
    return randomUnitVector();
}

template <typename T>
Vector3<T> Vector3<T>::reflect(const Normal3<T> &normal) const
{
    return *this - normal * static_cast<T>(2.0) * this->dot(normal);
}

template <typename T>
Vector3<T> Vector3<T>::refract(const Vector3 &normal, const double &ratio)
{
    double cosTheta = std::min(-(*this).dot(normal), 1.0);
    Vector3 rPerp   = (*this + normal * cosTheta) * ratio;
    Vector3 rPara   = normal * -std::sqrt(std::abs(1.0 - rPerp.dot(rPerp)));

    return rPerp + rPara;
}

template <typename T>
std::optional<Vector3<T>> Vector3<T>::refraction(const Vector3 &normal,
    const double &ratio) const
{
    Vector3 normalized = this->normalize();
    const double cosTheta = normalized.dot(normal);
    double discriminant = 1.0 - (ratio * ratio * (1.0 - (cosTheta * cosTheta)));

    if (discriminant > 0)
        return (normalized - normal * cosTheta) * ratio - normal * std::sqrt(
            discriminant);

    return std::nullopt;
}

template <typename T>
double Vector3<T>::dot(const Normal3<T> &normal) const
{
    return (this->x() * normal.x()) + (this->y() * normal.y()) + (this->z() *
        normal.z());
}

// template <typename T>
// double Vector3<T>::dot(const Vector3 &other) const
// {
//     return (this->x() * other.x()) + (this->y() * other.y()) + (this->z() *
//         other.z());
// }

template <typename T>
Vector3<T> Vector3<T>::operator+(const Normal3<T> &normal) const noexcept
{
    return Vector3{
        this->x() + normal.x(),
        this->y() + normal.y(),
        this->z() + normal.z()
    };
}

template <typename T>
Vector3<T> Vector3<T>::operator-(const Normal3<T> &normal) const noexcept
{
    return Vector3{
        this->x() - normal.x(),
        this->y() - normal.y(),
        this->z() - normal.z()
    };
}

} // namespace raytracer::maths
