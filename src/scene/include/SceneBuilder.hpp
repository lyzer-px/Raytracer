/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** SceneBuilder.hpp
*/

#pragma once

#include <memory>
#include "FactoryTemplate.hpp"
#include "IMaterial.hpp"
#include "PerspectiveCamera.hpp"
#include "Scene.hpp"
#include "jsonParser.hpp"

namespace raytracer::scene {

class SceneBuilder {
public:

    using MaterialFactory = designPattern::FactoryTemplate<material::IMaterial, std::string, const nlohmann::json&>;
    using ShapeFactory = designPattern::FactoryTemplate<shape::IShape, std::string, const nlohmann::json&>;
    using PrimitiveFactory = designPattern::FactoryTemplate<shape::IPrimitive, std::string, const nlohmann::json&>;

    SceneBuilder() = default;

    void buildScene(nlohmann::json &config);

    [[nodiscard]] const std::unique_ptr<Scene> &scene() const;

private:
    std::unique_ptr<Scene> _scene;
    std::unique_ptr<camera::PerspectiveCamera> _camera;
    MaterialFactory _materialFactory;
    ShapeFactory _shapeFactory;
    PrimitiveFactory _primitiveFactory;
};

} // namespace raytracer::scene
