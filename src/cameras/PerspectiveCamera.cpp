/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** PerspectiveCamera
*/

#include "PerspectiveCamera.hpp"

#include <cmath>
#include <memory>

#include "Serializer.hpp"

namespace raytracer::camera {

PerspectiveCamera::PerspectiveCamera(const nlohmann::json &config):
    PerspectiveCamera(
        config.at("position").get<maths::Point3d>(),
        config.at("target").get<maths::Point3d>(),
        config.at("up").get<maths::Vector3d>(),
        CameraProjection{.fovDegrees = config.at("fov").get<double>(),
            .aspectRatio = config.at("resolution").at(0).get<double>() /
                config.at("resolution").at(1).get<double>()},
        config.contains("transform") ? parseTransformOps(config.at("transform"))
                                     : maths::Transform{})
{}

PerspectiveCamera::PerspectiveCamera(const maths::Point3d &position,
    const maths::Point3d &target, const maths::Vector3d &up,
    const CameraProjection &projection, const maths::Transform &extraTransform)
{
    const double theta = projection.fovDegrees * M_PI / 180.0;
    _halfHeight        = std::tan(theta / 2.0);
    _halfWidth         = projection.aspectRatio * _halfHeight;
    _cameraToWorld     = maths::Transform::lookAt(position, target, up) * extraTransform;
}

maths::Ray PerspectiveCamera::generateRay(const float &u, const float &v) const
{
    const double px = (2.0 * static_cast<double>(u) - 1.0) * _halfWidth;
    const double py = (2.0 * static_cast<double>(v) - 1.0) * _halfHeight;
    const maths::Ray cameraRay(
        maths::Point3d{0.0, 0.0, 0.0},
        maths::Vector3d{px, py, 1.0}.normalize());
    return _cameraToWorld(cameraRay);
}

std::unique_ptr<PerspectiveCamera> PerspectiveCamera::create(
    const nlohmann::json &config)
{
    return std::make_unique<PerspectiveCamera>(config);
}

maths::Transform PerspectiveCamera::parseTransformOps(const nlohmann::json &ops)
{
    maths::Transform result{};
    for (const auto &op : ops) {
        if (op.contains("translate"))
            result = result * maths::Transform::translate(
                op.at("translate").get<maths::Vector3d>());
        else if (op.contains("scale")) {
            const auto s = op.at("scale").get<maths::Vector3d>();
            result       = result * maths::Transform::scale(s.x(), s.y(), s.z());
        } else if (op.contains("rotateX"))
            result = result * maths::Transform::rotateX(op.at("rotateX").get<double>());
        else if (op.contains("rotateY"))
            result = result * maths::Transform::rotateY(op.at("rotateY").get<double>());
        else if (op.contains("rotateZ"))
            result = result * maths::Transform::rotateZ(op.at("rotateZ").get<double>());
    }
    return result;
}

} // namespace raytracer::camera
