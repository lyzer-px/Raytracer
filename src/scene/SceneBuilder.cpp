/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** ConfigParser.cpp
*/

#include <string>
#include "ConfigParser.hpp"
#include "jsonParser.hpp"
#include "FactoryTemplate.hpp"
#include "maths/Color.hpp"

namespace raytracer::scene {

void SceneBuilder::buildScene(nlohmann::json &config)
{
    try {
        camera::ICamera *camera = config["camera"];
        for (const auto &materialJson : config["materials"])
            _materials.push_back();
        for (const auto &primitiveJson : config["primitives"])
            _primitives.push_back();
        for (const auto &lightJson : config["lights"])
            _lights.push_back();
    } catch (const std::exception &e) {
        throw std::runtime_error(std::string("Failed to build scene: ") + e.what());
    }
}
}