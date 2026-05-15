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
#include "IShape.hpp"
#include "jsonParser.hpp"
#include "PerspectiveCamera.hpp"
#include "Scene.hpp"

namespace raytracer::scene {

class SceneBuilder {
public:
    using MaterialFactory = designPattern::FactoryTemplate<material::IMaterial,
        std::string, const nlohmann::json &>;
    using ShapeFactory = designPattern::FactoryTemplate<shape::IShape,
        std::string, const nlohmann::json &>;
    using PrimitiveFactory = designPattern::FactoryTemplate<shape::IPrimitive,
        std::string, maths::Transform, maths::Transform,
        std::unique_ptr<shape::IShape> &, material::IMaterial *>;
    using LightFactory = designPattern::FactoryTemplate<light::ILight,
        std::string, const nlohmann::json &>;

    SceneBuilder();

    void buildScene(nlohmann::json &config);

    [[nodiscard]] const std::unique_ptr<Scene> &scene() const;

    [[nodiscard]] const std::unique_ptr<camera::PerspectiveCamera> &
    camera() const;

private:
    std::unique_ptr<Scene> _scene;
    std::unique_ptr<camera::PerspectiveCamera> _camera;
    MaterialFactory _materialFactory;
    ShapeFactory _shapeFactory;
    PrimitiveFactory _primitiveFactory;
    LightFactory _lightFactory;

    void registerCreators();

    void buildBackground(const nlohmann::json &config) const;

    void buildCamera(const nlohmann::json &config);

    void buildMaterials(const nlohmann::json &config);

    void buildPrimitives(const nlohmann::json &config);

    void buildLights(const nlohmann::json &config);

    void buildMesh(const nlohmann::json &primitive);

    [[nodiscard]] static maths::Transform parseTransform(
        const nlohmann::json &operations);
};

} // namespace raytracer::scene
