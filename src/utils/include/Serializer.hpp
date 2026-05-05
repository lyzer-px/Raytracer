/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.hpp
*/

#pragma once

#include "IShape.hpp"
#include "Matrix.hpp"
#include "PerspectiveCamera.hpp"
#include "jsonParser.hpp"
#include "maths_types.hpp"
#include "Scene.hpp"
#include "IMaterial.hpp"
#include "IPrimitive.hpp"
#include "ILight.hpp"
#include "ICamera.hpp"
#include <memory>

namespace nlohmann {

template <>
struct adl_serializer<raytracer::maths::Vector3d> {
    static void to_json(json &j, const raytracer::maths::Vector3d &c); // NOLINT
    static void from_json(const json &j, raytracer::maths::Vector3d &c); // NOLINT
};

template <>
struct adl_serializer<raytracer::maths::Color> {
    static void to_json(json &j, const std::unique_ptr<raytracer::maths::Color> &c);
    static void from_json(const json &j, std::unique_ptr<raytracer::maths::Color> &c);
};

template <>
struct adl_serializer<raytracer::maths::Normal3d> {
    static void to_json(json &j, const std::unique_ptr<raytracer::maths::Normal3d> &c);
    static void from_json(const json &j, std::unique_ptr<raytracer::maths::Normal3d> &c);
};

template <>
struct adl_serializer<raytracer::maths::Point3d> {
    static void to_json(json &j, const std::unique_ptr<raytracer::maths::Point3d> &c);
    static void from_json(const json &j, std::unique_ptr<raytracer::maths::Point3d> &c);
};
template <>
struct adl_serializer<raytracer::camera::PerspectiveCamera> {
    static void to_json(json &j, const std::unique_ptr<raytracer::camera::PerspectiveCamera> &c);
    static void from_json(const json &j, std::unique_ptr<raytracer::camera::PerspectiveCamera> &c);
};

}
