/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** SceneBuilder.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "FactoryTemplate.hpp"
#include "IMaterial.hpp"
#include "Scene.hpp"
#include "jsonParser.hpp"

namespace raytracer::scene {

class SceneBuilder {
public:
    using PrimitiveFactory = designPattern::FactoryTemplate<shape::IPrimitive, nlohmann::json>;
    using LightFactory = designPattern::FactoryTemplate<light::ILight, nlohmann::json>;
    using MaterialFactory = designPattern::FactoryTemplate<material::IMaterial, nlohmann::json>;
    SceneBuilder() = default;

    void buildScene(nlohmann::json &config);
private:
    const std::vector<std::unique_ptr<shape::IPrimitive>> &_primitives;
    const std::vector<std::unique_ptr<light::ILight>> &_lights;
    const std::vector<std::unique_ptr<material::IMaterial>> &_materials;
    std::unique_ptr<Scene> _scene;
};

} // namespace raytracer::scene
