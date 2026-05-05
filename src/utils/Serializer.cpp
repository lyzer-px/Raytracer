/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.cpp
*/

#include "Serializer.hpp"
#include "Color.hpp"

namespace nlohmann {

template <>
void adl_serializer<raytracer::camera::ICamera>::to_json(nlohmann::json &j, const raytracer::camera::ICamera &camera)
{
    throw std::runtime_error("Serialization of ICamera is not implemented");
}

template <>
void adl_serializer<raytracer::camera::ICamera>::from_json(const nlohmann::json &j, raytracer::camera::ICamera &camera)
{
    camera.resolution = j["camera"]["resolution"];
    camera.position = j["camera"]["position"];
    camera.target = j["camera"]["target"];
    camera.up = j["camera"]["up"];
    camera.fov = j["camera"]["fov"];
}

template <>
void adl_serializer<raytracer::material::IMaterial>::to_json(nlohmann::json &j, const raytracer::material::IMaterial &material)
{
    throw std::runtime_error("Serialization of IMaterial is not implemented");
}

template <>
void adl_serializer<raytracer::material::IMaterial>::from_json(const nlohmann::json &j, raytracer::material::IMaterial &material)
{
    material.id = j["material"]["id"];
    material.type = j["material"]["type"];
    material.config = j["material"]["config"];
}

template <>
void adl_serializer<raytracer::primitive::IPrimitive>::to_json(nlohmann::json &j, const raytracer::primitive::IPrimitive &primitive)
{
    throw std::runtime_error("Serialization of IPrimitive is not implemented");
}

template <>
void adl_serializer<raytracer::primitive::IPrimitive>::from_json(const nlohmann::json &j, raytracer::primitive::IPrimitive &primitive)
{
    primitive.type = j["primitive"]["type"];
    primitive.materialId = j["primitive"]["materialId"];
    primitive.config = j["primitive"]["config"];
}

template <>
void adl_serializer<raytracer::light::ILight>::to_json(nlohmann::json &j, const raytracer::light::ILight &light)
{
    throw std::runtime_error("Serialization of ILight is not implemented");
}

template <>
void adl_serializer<raytracer::light::ILight>::from_json(const nlohmann::json &j, raytracer::light::ILight &light)
{
    light.type = j["light"]["type"];
    light.config = j["light"]["config"];
}

}