/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Bounds3.tpp
*/

#pragma once

#include "Bounds3.hpp"
#include "Point.hpp"

namespace raytracer::maths {

template <typename T>
Bounds3<T>::Bounds3(const Point3<T> &p1, const Point3<T> &p2):
    pMin(p1), pMax(p2)
{}

template <typename T> Bounds3<T>::Bounds3(const Point3<T> &p): pMin(p), pMax(p)
{}

template <typename T>
Bounds3<T> Bounds3<T>::boundsUnion(const Point3<T> &other) const
{
    return Bounds3<T>(
        Point3<T>(std::min(pMin.x(), other.x()), std::min(pMin.y(), other.y()),
            std::min(pMin.z(), other.z())),
        Point3<T>(std::max(pMax.x(), other.x()), std::max(pMax.y(), other.y()),
            std::max(pMax.z(), other.z())));
}

template <typename T>
Bounds3<T> Bounds3<T>::boundsUnion(const Bounds3<T> &other) const
{
    return Bounds3<T>(Point3<T>(std::min(pMin.x(), other.pMin.x()),
                          std::min(pMin.y(), other.pMin.y()),
                          std::min(pMin.z(), other.pMin.z())),
        Point3<T>(std::max(pMax.x(), other.pMax.x()),
            std::max(pMax.y(), other.pMax.y()),
            std::max(pMax.z(), other.pMax.z())));
}
template <typename T> const Point3<T> &Bounds3<T>::operator[](int i) const
{
    return (i == 0) ? pMin : pMax;
}

template <typename T> Point3<T> &Bounds3<T>::operator[](int i)
{
    return (i == 0) ? pMin : pMax;
}

template <typename T> Point3<T> Bounds3<T>::corner(int i) const
{
    return Point3<T>(((i & 1) != 0) ? pMax.x : pMin.x,
        ((i & 2) != 0) ? pMax.y : pMin.y, ((i & 4) != 0) ? pMax.z : pMin.z);
}
template <typename T> Vector3<T> Bounds3<T>::diagonal() const
{
    return pMax - pMin;
}

template <typename T> T Bounds3<T>::surfaceArea() const
{
    Vector3<T> d = diagonal();
    return 2 * ((d.x * d.y) + (d.x * d.z) + (d.y * d.z));
}

template <typename T> T Bounds3<T>::volume() const
{
    Vector3<T> d = diagonal();
    return d.x * d.y * d.z;
}

template <typename T> int Bounds3<T>::maxDimension() const
{
    Vector3<T> d = diagonal();

    if (d.x > d.y && d.x > d.z)
        return 0;
    if (d.y > d.z)
        return 1;
    return 2;
}

template <typename T> Point3<T> Bounds3<T>::centroid() const
{
    return (pMin + pMax) / static_cast<T>(2);
}

template <typename T> bool Bounds3<T>::operator==(const Bounds3<T> &other) const
{
    return pMin == other.pMin && pMax == other.pMax;
}

template <typename T> bool Bounds3<T>::operator!=(const Bounds3<T> &other) const
{
    return !(*this == other);
}

template <typename T>
bool Bounds3<T>::intersectP(
    const Ray &ray, T tMax, T *tHitNear, T *tHitFar) const
{
    T t0 = static_cast<T>(0);
    T t1 = tMax;

    for (int i = 0; i < 3; ++i) {
        T invRayDir = static_cast<T>(1) / ray.direction.data()[i];
        T tNear     = (pMin[i] - ray.origin.data()[i]) * invRayDir;
        T tFar      = (pMax[i] - ray.origin.data()[i]) * invRayDir;

        if (tNear > tFar)
            std::swap(tNear, tFar);

        t0 = std::max(t0, tNear);
        t1 = std::min(t1, tFar);

        if (t0 > t1)
            return false;
    }

    if (tHitNear)
        *tHitNear = t0;
    if (tHitFar)
        *tHitFar = t1;
    return true;
}

template <typename T>
bool Bounds3<T>::intersectP(const Ray &ray, const Vector3<T> &invDir,
    const std::array<int, 3> &dirIsNeg) const
{
    const Bounds3<T> &bounds = *this;
    int i                    = dirIsNeg[0];

    T txMin = (bounds[i].x() - ray.origin.x()) * invDir.x();
    T txMax = (bounds[1 - i].x() - ray.origin.x()) * invDir.x();

    i       = dirIsNeg[1];
    T tyMin = (bounds[i].y() - ray.origin.y()) * invDir.y();
    T tyMax = (bounds[1 - i].y() - ray.origin.y()) * invDir.y();

    if ((txMin > tyMax) || (tyMin > txMax))
        return false;
    if (tyMin > txMin)
        txMin = tyMin;
    if (tyMax < txMax)
        txMax = tyMax;

    i       = dirIsNeg[2];
    T tzMin = (bounds[i].z() - ray.origin.z()) * invDir.z();
    T tzMax = (bounds[1 - i].z() - ray.origin.z()) * invDir.z();

    if ((txMin > tzMax) || (tzMin > txMax))
        return false;
    if (tzMin > txMin)
        txMin = tzMin;
    if (tzMax < txMax)
        txMax = tzMax;

    return (txMin < ray.tMax) && (txMax > static_cast<T>(0));
}

} // namespace raytracer::maths
