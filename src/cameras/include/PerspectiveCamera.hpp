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
    PerspectiveCamera(const maths::Point3d &position, const maths::Point3d &target,
        const maths::Vector3d &up, float fovDegrees, float aspectRatio);

    [[nodiscard]] maths::Ray
        generateRay(const float &u, const float &v) const override;

private:
    maths::Point3d _origin;
    maths::Point3d _lowerLeft;
    maths::Vector3d _horizontal;
    maths::Vector3d _vertical;
};
} // camera
} // raytracer

#endif //RAYTRACER_PERSPECTIVECAMERA_HPP
