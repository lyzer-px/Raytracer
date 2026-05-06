/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PerspectiveCamera
*/

#include "PerspectiveCamera.hpp"
#include <memory>

namespace raytracer::camera {
PerspectiveCamera::PerspectiveCamera(const nlohmann::json &config)
    : PerspectiveCamera(
        maths::Point3d(
            config.at("position").at(0).get<double>(),
            config.at("position").at(1).get<double>(),
            config.at("position").at(2).get<double>()
        ),
        maths::Point3d(
            config.at("target").at(0).get<double>(),
            config.at("target").at(1).get<double>(),
            config.at("target").at(2).get<double>()
        ),
        maths::Vector3d(
            config.at("up").at(0).get<double>(),
            config.at("up").at(1).get<double>(),
            config.at("up").at(2).get<double>()
        ),
        CameraProjection{
            .fovDegrees=config.at("fov").get<double>(),
            .aspectRatio=config.contains("resolution")
                ? static_cast<float>(config.at("resolution").at(0).get<double>() /
                                     config.at("resolution").at(1).get<double>())
                : config.at("aspect_ratio").get<float>()
        })
{
}

PerspectiveCamera::PerspectiveCamera(const maths::Point3d &position,
    const maths::Point3d &target, const maths::Vector3d &up,
    const CameraProjection &projection)
    : _origin{position}
{
    const double theta      = projection.fovDegrees * M_PI / 180.0;
    const double halfHeight = std::tan(theta / 2.0);
    const double halfWidth  = projection.aspectRatio * halfHeight;

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

std::unique_ptr<PerspectiveCamera> PerspectiveCamera::create(const nlohmann::json &config)
{
    return std::make_unique<PerspectiveCamera>(config);
}

const maths::Point3d &PerspectiveCamera::origin() const
{
    return _origin;
}

const maths::Point3d &PerspectiveCamera::lowerLeft() const
{
    return _lowerLeft;
}

const maths::Vector3d &PerspectiveCamera::horizontal() const
{
    return _horizontal;
}

const maths::Vector3d &PerspectiveCamera::vertical() const
{
    return _vertical;
}
}
