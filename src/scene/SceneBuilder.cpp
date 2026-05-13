/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** ConfigParser.cpp
*/

#include "SceneBuilder.hpp"

#include <string>

#include "AmbientLight.hpp"
#include "Dielectric.hpp"
#include "DirectionalLight.hpp"
#include "GeometricPrimitive.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "PerspectiveCamera.hpp"
#include "Plane.hpp"
#include "Serializer.hpp"
#include "Sphere.hpp"
#include "Transform.hpp"

namespace raytracer::scene {
// NOLINTNEXTLINE(readability-function-cognitive-complexity)

SceneBuilder::SceneBuilder()
{
    registerCreators();
}

void SceneBuilder::registerCreators()
{
    _materialFactory.registerCreator<material::Lambertian>("lambertian");
    _materialFactory.registerCreator<material::Metal>("metal");
    _materialFactory.registerCreator<material::Dielectric>("dielectric");
    _shapeFactory.registerCreator<shape::Sphere>("sphere");
    _shapeFactory.registerCreator<shape::Plane>("plane");
    _primitiveFactory.registerCreator<shape::GeometricPrimitive>(
        "geometric_primitive");
    _lightFactory.registerCreator<light::AmbientLight>("ambient");
    _lightFactory.registerCreator<light::DirectionalLight>("directional");
}

void SceneBuilder::buildScene(nlohmann::json &config)
{
    try {
        _scene = std::make_unique<Scene>();
        buildBackground(config);
        buildCamera(config);
        buildMaterials(config);
        buildPrimitives(config);
        buildLights(config);
    } catch (const std::exception &e) {
        throw std::runtime_error(
            std::string("Error building scene: ") + e.what());
    }
}

void SceneBuilder::buildBackground(const nlohmann::json &config) const
{
    if (config.contains("background_color"))
        _scene->setBackgroundColor(
            config.at("background_color").get<maths::Color>());
}

void SceneBuilder::buildCamera(const nlohmann::json &config)
{
    if (config.contains("camera"))
        _camera = camera::PerspectiveCamera::create(config.at("camera"));
}

void SceneBuilder::buildMaterials(const nlohmann::json &config)
{
    if (!config.contains("materials"))
        return;
    for (const auto &material: config.at("materials")) {
        auto tmp = _materialFactory.create(
            material.at("type").get<std::string>(), material["config"]);
        _scene->addMaterial(material["id"].get<std::string>(), tmp);
    }
}

void SceneBuilder::buildPrimitives(const nlohmann::json &config)
{
    if (!config.contains("primitives"))
        return;
    for (const auto &primitive: config.at("primitives")) {
        const auto &shapeConfig = primitive["shape"]["config"];
        auto objectToWorld      = shapeConfig.contains("position")
            ? maths::Transform::translate(
                shapeConfig.at("position").get<maths::Vector3d>())
            : maths::Transform{};
        if (primitive.contains("transform"))
            objectToWorld = objectToWorld * parseTransform(
                primitive["transform"]);
        auto shapeTmp = _shapeFactory.create(
            primitive.at("shape").at("type").get<std::string>(), shapeConfig);
        auto tmp = _primitiveFactory.create(
            primitive["type"].get<std::string>(),
            maths::Transform::inverse(objectToWorld), objectToWorld, shapeTmp,
            _scene->getMaterial(primitive["material_id"].get<std::string>()));
        _scene->addPrimitive(tmp);
    }
}

void SceneBuilder::buildLights(const nlohmann::json &config)
{
    if (!config.contains("lights"))
        return;
    for (const auto &light: config.at("lights")) {
        auto tmp = _lightFactory.create(
            light.at("type").get<std::string>(), light["config"]);
        _scene->addLight(tmp);
    }
}

const std::unique_ptr<Scene> &SceneBuilder::scene() const
{
    return _scene;
}

const std::unique_ptr<camera::PerspectiveCamera> &SceneBuilder::camera() const
{
    return _camera;
}

maths::Transform SceneBuilder::parseTransform(const nlohmann::json &operations)
{
    maths::Transform result;
    for (const auto &op: operations) {
        if (op.contains("translate"))
            result = result * maths::Transform::translate(
                op["translate"].get<maths::Vector3d>());
        else if (op.contains("scale")) {
            const auto s = op["scale"].get<maths::Vector3d>();
            result = result * maths::Transform::scale(s.x(), s.y(), s.z());
        } else if (op.contains("rotateX"))
            result = result * maths::Transform::rotateX(
                op["rotateX"].get<double>());
        else if (op.contains("rotateY"))
            result = result * maths::Transform::rotateY(
                op["rotateY"].get<double>());
        else if (op.contains("rotateZ"))
            result = result * maths::Transform::rotateZ(
                op["rotateZ"].get<double>());
    }
    return result;
}
} // namespace raytracer::scene
