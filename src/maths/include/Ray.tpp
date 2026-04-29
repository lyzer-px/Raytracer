/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.tpp
*/

#include "Ray.hpp"

Ray::Ray(const Point3d& origin, const Vector3d& direction)
    : _origin(origin), _direction(direction.normalize()) {}

const Point3d &Ray::getOrigin() const
{
    return _origin;
}

const UnitVector3& Ray::getDirection() const
{
    return _direction;
}

Vector3d Ray::at(double t) const
{
    return _origin.toVector() + _direction * t;
}