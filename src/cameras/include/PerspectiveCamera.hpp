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
    PerspectiveCamera(const Point3f &position, const Point3f &target,
        const Vector3f &up, float fovDegrees, float aspectRatio);

    [[nodiscard]] Ray
        generateRay(const float &u, const float &v) const override;

private:
    Point3f _origin;
    Point3f _lowerLeft;
    Vector3f _horizontal;
    Vector3f _vertical;
};
} // camera
} // raytracer

#endif //RAYTRACER_PERSPECTIVECAMERA_HPP
