/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PerspectiveCamera
*/

#include "PerspectiveCamera.hpp"

namespace raytracer {
namespace camera {
PerspectiveCamera::PerspectiveCamera(const maths::Point3d &position,
    const maths::Point3d &target, const maths::Vector3d &up, float fovDegrees,
    float aspectRatio): _origin{position}
{
    const double theta      = fovDegrees * M_PI / 180.0;
    const double halfHeight = std::tan(theta / 2.0);
    const double halfWidth  = aspectRatio * halfHeight;

    maths::Vector3d forward      = (target - position).normalize();
    const maths::Vector3d right  = forward.cross(up.normalize()).normalize();
    const maths::Vector3d trueUp = right.cross(forward);

    const maths::Vector3d offsetRight = right * halfWidth;
    const maths::Vector3d offsetUp    = trueUp * halfHeight;

    _lowerLeft  = _origin + (forward - offsetRight - offsetUp);
    _horizontal = right * (2.0 * halfWidth);
    _vertical   = trueUp * (2.0 * halfHeight);
}

maths::Ray PerspectiveCamera::generateRay(const float &u, const float &v) const
{
    const maths::Point3d target = _lowerLeft + _horizontal * u + _vertical * v;
    const maths::Vector3d direction = (target - _origin).normalize();

    return maths::Ray{_origin, direction};
}
} // camera
} // raytracer
