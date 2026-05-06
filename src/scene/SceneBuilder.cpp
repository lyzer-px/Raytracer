/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** ConfigParser.cpp
*/

#include "SceneBuilder.hpp"

#include <string>
#include <unordered_map>

#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "Lambertian.hpp"
#include "GeometricPrimitive.hpp"
#include "PerspectiveCamera.hpp"
#include "Serializer.hpp"
#include "Sphere.hpp"

namespace raytracer::scene {
// NOLINTNEXTLINE(readability-function-cognitive-complexity)

SceneBuilder::SceneBuilder()
{
    registerCreators();
}

void SceneBuilder::registerCreators()
{
    _materialFactory.registerCreator<material::Lambertian>("lambertian");
    _shapeFactory.registerCreator<shape::Sphere>("sphere");
    _primitiveFactory.registerCreator<shape::GeometricPrimitive>(
        "geometric_primitive");
    _lightFactory.registerCreator<light::AmbientLight>("ambient");
    _lightFactory.registerCreator<light::DirectionalLight>("directional");
}

void SceneBuilder::buildScene(nlohmann::json &config)
{
    try {
        _scene = std::make_unique<Scene>();

        if (config.contains("background_color")) {
            ;
            _scene->setBackgroundColor(
                config.at("background_color").get<maths::Color>());
        }
        if (config.contains("camera"))
            _camera = camera::PerspectiveCamera::create(config.at("camera"));
        for (const auto &material: config.at("materials")) {
            auto tmp = _materialFactory.create(
                material.at("type").get<std::string>(), material["config"]);
            _scene->addMaterial(material["id"].get<std::string>(), tmp);
        }
        for (const auto &primitive: config.at("primitives")) {
            auto shapeTmp = _shapeFactory.create(
                primitive.at("shape").at("type").get<std::string>(),
                primitive.at("shape")["config"]);
            auto tmp = _primitiveFactory.create(
                primitive["type"].get<std::string>(), shapeTmp,
                _scene->getMaterial(
                    primitive["material_id"].get<std::string>()));
            _scene->addPrimitive(tmp);
        }
        for (const auto &light: config.at("lights")) {
            auto tmp = _lightFactory.create(
                light.at("type").get<std::string>(), light["config"]);
            _scene->addLight(tmp);
        }
    } catch (const std::exception &e) {
        throw std::runtime_error(
            std::string("Error building scene: ") + e.what());
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
} // namespace raytracer::scene
