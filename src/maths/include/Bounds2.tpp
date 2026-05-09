/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Bounds2.tpp
*/

#pragma once

#include <algorithm>

#include "Bounds2.hpp"
#include "Point.hpp"

namespace raytracer::maths {

template <typename T>
Bounds2<T>::Bounds2(const Point2<T> &p1, const Point2<T> &p2):
    pMin(p1), pMax(p2)
{}

template <typename T> Bounds2<T>::Bounds2(const Point2<T> &p): pMin(p), pMax(p)
{}

template <typename T> const Point2<T> &Bounds2<T>::operator[](int i) const
{
    return (i == 0) ? pMin : pMax;
}

template <typename T> Point2<T> &Bounds2<T>::operator[](int i)
{
    return (i == 0) ? pMin : pMax;
}

template <typename T> Point2<T> Bounds2<T>::corner(int i) const
{
    return Point2<T>(
        ((i & 1) != 0) ? pMax.x : pMin.x, ((i & 2) != 0) ? pMax.y : pMin.y);
}
template <typename T> Vector2<T> Bounds2<T>::diagonal() const
{
    return pMax - pMin;
}

template <typename T> T Bounds2<T>::surfaceArea() const
{
    Vector2<T> d = diagonal();
    return 2 * (d.x * d.y);
}

template <typename T> T Bounds2<T>::volume() const
{
    Vector2<T> d = diagonal();
    return d.x * d.y;
}

template <typename T> int Bounds2<T>::maxDimension() const
{
    Vector2<T> d = diagonal();
    return (d.x > d.y) ? 0 : 1;
}

template <typename T> Point2<T> Bounds2<T>::centroid() const
{
    return (pMin + pMax) / static_cast<T>(2);
}

template <typename T> bool Bounds2<T>::operator==(const Bounds2<T> &other) const
{
    return pMin == other.pMin && pMax == other.pMax;
}

template <typename T> bool Bounds2<T>::operator!=(const Bounds2<T> &other) const
{
    return !(*this == other);
}

template <typename T>
bool Bounds2<T>::intersectP(
    const Ray &ray, T tMax, T *tHitNear, T *tHitFar) const
{
    T t0 = static_cast<T>(0);
    T t1 = tMax;

    for (int i = 0; i < 2; ++i) {
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
bool Bounds2<T>::intersectP(const Ray &ray, const Vector2<T> &invDir,
    const std::array<int, 2> &dirIsNeg) const
{
    const Bounds2<T> &bounds = *this;
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

    return (txMin < ray.tMax) && (txMax > static_cast<T>(0));
}
} // namespace raytracer::maths
