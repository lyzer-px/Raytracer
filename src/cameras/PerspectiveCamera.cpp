/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PerspectiveCamera
*/

#include "PerspectiveCamera.hpp"

namespace raytracer {
namespace camera {
PerspectiveCamera::PerspectiveCamera(const Point3d &position,
    const Point3d &target, const Vector3d &up, float fovDegrees,
    float aspectRatio): _origin{position}
{
    const double theta      = fovDegrees * M_PI / 180.0;
    const double halfHeight = std::tan(theta / 2.0);
    const double halfWidth  = aspectRatio * halfHeight;

    Vector3d forward      = (target - position).normalize();
    const Vector3d right  = forward.cross(up.normalize()).normalize();
    const Vector3d trueUp = right.cross(forward);

    const Vector3d offsetRight = right * halfWidth;
    const Vector3d offsetUp    = trueUp * halfHeight;

    _lowerLeft  = _origin + (forward - offsetRight - offsetUp);
    _horizontal = right * (2.0 * halfWidth);
    _vertical   = trueUp * (2.0 * halfHeight);
}

Ray PerspectiveCamera::generateRay(const float &u, const float &v) const
{
    const Point3d target = _lowerLeft + _horizontal * u + _vertical * v;
    const Vector3d direction = (target - _origin).normalize();

    return Ray{_origin, direction};
}
} // camera
} // raytracer
