/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Ray.tpp
*/

#include "Ray.hpp"

Ray::Ray(const Point3f& origin, const UnitVector3& direction)
    : _origin(origin), _direction(direction) {}

Ray::const Point3f& Ray::getOrigin() const
{
    return _origin;
}

Ray::const UnitVector3& Ray::getDirection() const
{
    return _direction;
}

Point3f Ray::at(double t) const
{
    return _origin + (_direction * t);
}