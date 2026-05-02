/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PerspectiveCamera
*/

#ifndef RAYTRACER_PERSPECTIVECAMERA_HPP
#define RAYTRACER_PERSPECTIVECAMERA_HPP

#include "ICamera.hpp"
#include "maths_types.hpp"

namespace raytracer {
namespace camera {
class PerspectiveCamera: public ICamera {
public:
    PerspectiveCamera(const Point3d &position, const Point3d &target,
        const Vector3d &up, float fovDegrees, float aspectRatio);

    [[nodiscard]] Ray
        generateRay(const float &u, const float &v) const override;

private:
    Point3d _origin;
    Point3d _lowerLeft;
    Vector3d _horizontal;
    Vector3d _vertical;
};
} // camera
} // raytracer

#endif //RAYTRACER_PERSPECTIVECAMERA_HPP
