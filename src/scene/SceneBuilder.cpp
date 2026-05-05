/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** ConfigParser.cpp
*/

#include <string>
#include <unordered_map>

#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"
#include "GeometricPrimitive.hpp"
#include "PerspectiveCamera.hpp"
#include "SceneBuilder.hpp"

namespace raytracer::scene {
// NOLINTNEXTLINE(readability-function-cognitive-complexity)
void SceneBuilder::buildScene(nlohmann::json &config)
{
    try {
        _scene = std::make_unique<Scene>();

        if (config.contains("camera"))
            _camera = camera::PerspectiveCamera::create(config.at("camera"));
        for (const auto &material : config.at("materials")) {
            auto tmp = _materialFactory.create(material.at("type").get<std::string>(), material["config"]);
            _scene->addMaterial(tmp);
        }
        for (const auto &primitive : config.at("primitives")) {
            auto shapeTmp = _shapeFactory.create(primitive.at("shape").at("type").get<std::string>(), primitive.at("shape")["config"]);
            auto tmp = _primitiveFactory.create(primitive.at("type").get<std::string>(), primitive["config"]);
            _scene->addPrimitive(tmp);
        }
        
    } catch (const std::exception &e) {
        throw std::runtime_error(std::string("Error building scene: ") + e.what());
    }
}

const std::unique_ptr<Scene> &SceneBuilder::scene() const
{
    return _scene;
}
} // namespace raytracer::scene