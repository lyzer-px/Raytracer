/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.hpp
*/

#pragma once

#include "IShape.hpp"
#include "jsonParser.hpp"
#include "Scene.hpp"
#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "ICamera.hpp"
#include <memory>

namespace nlohmann {

template <>
struct adl_serializer<raytracer::camera::ICamera> {
    static void to_json(nlohmann::json &j, const raytracer::camera::ICamera &camera);
    static void from_json(const nlohmann::json &j, raytracer::camera::ICamera &camera);
};

template <>
struct adl_serializer<raytracer::material::IMaterial> {
    static void to_json(nlohmann::json &j, const raytracer::material::IMaterial &material);
    static void from_json(const nlohmann::json &j, raytracer::material::IMaterial &material);
};

template <>
struct adl_serializer<raytracer::primitive::IPrimitive> {
    static void to_json(nlohmann::json &j, const raytracer::primitive::IPrimitive &primitive);
    static void from_json(const nlohmann::json &j, raytracer::primitive::IPrimitive &primitive);
};

template <>
struct adl_serializer<raytracer::light::ILight> {
    static void to_json(nlohmann::json &j, const raytracer::light::ILight &light);
    static void from_json(const nlohmann::json &j, raytracer::light::ILight &light);
};

}