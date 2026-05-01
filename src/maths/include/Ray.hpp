/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.hpp
*/

#pragma once

#include "Vector.hpp"
#include "Point.hpp"

class Ray {
public:
    Ray();
    Ray(const Point3d& origin, const Vector3d& direction,
        float tMax = std::numeric_limits<float>::infinity());

    Point3d operator()(float t) const;  // P(t) = o + t*d -- replaces at(t)
    bool    hasNaN() const;

    Point3d       o;      // origin
    Vector3d      d;      // direction (caller responsible for normalization)
    mutable float tMax;   // reduced by each intersection hit -- enables BVH early exit
};

class RayDifferential : public Ray {
public:
    RayDifferential();
    RayDifferential(const Point3d& origin, const Vector3d& direction,
                    float tMax = std::numeric_limits<float>::infinity());

    explicit RayDifferential(const Ray& ray);  // construct from a base Ray

    void scaleDifferentials(float s);          // scale offset rays by s, used for antialiasing
    bool hasNaN() const;

    bool     hasDifferentials;
    Point3d  rxOrigin,    ryOrigin;            // origins of the x/y offset rays
    Vector3d rxDirection, ryDirection;         // directions of the x/y offset rays
};

#include "Ray.tpp"
