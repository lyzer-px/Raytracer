/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PerspectiveCamera
*/

#pragma once

#include "ICamera.hpp"
#include "jsonParser.hpp"

namespace raytracer::camera {

struct CameraProjection {
    double fovDegrees;
    double aspectRatio;
};

class PerspectiveCamera: public ICamera {
public:
    explicit PerspectiveCamera(const nlohmann::json &config);
    explicit PerspectiveCamera(const Point3d &position, const Point3d &target,
        const maths::Vector3d &up, const CameraProjection &projection);

    [[nodiscard]] maths::Ray generateRay(
        const float &u, const float &v) const override;

    static std::unique_ptr<PerspectiveCamera> create(
        const nlohmann::json &config);

private:
    Point3d _origin;
    Point3d _lowerLeft;
    maths::Vector3d _horizontal;
    maths::Vector3d _vertical;
};
} // namespace raytracer::camera
