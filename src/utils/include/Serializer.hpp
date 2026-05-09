/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.hpp
*/

#pragma once

#include "jsonParser.hpp"
#include "Color.hpp"
#include "Normal.hpp"
#include "PerspectiveCamera.hpp"
#include "Point.hpp"
#include "Vector3.hpp"
#include <memory>

namespace nlohmann {

// NOLINTBEGIN(readability-identifier-naming)
template <>
struct adl_serializer<raytracer::maths::Vector3d> {
    static void to_json(json &j, const raytracer::maths::Vector3d &c);
    static void from_json(const json &j, raytracer::maths::Vector3d &c);
};

template <>
struct adl_serializer<raytracer::maths::Color> {
    static void to_json(json &j, const raytracer::maths::Color &c);
    static void from_json(const json &j, raytracer::maths::Color &c);
};

template <>
struct adl_serializer<raytracer::maths::Normal3d> {
    static void to_json(json &j, const raytracer::maths::Normal3d &c);
    static void from_json(const json &j, raytracer::maths::Normal3d &c);
};

template <>
struct adl_serializer<Point3d> {
    static void to_json(json &j, const Point3d &c);
    static void from_json(const json &j, Point3d &c);
};
template <>
struct adl_serializer<raytracer::camera::PerspectiveCamera> {
    static void to_json(json &j, const std::unique_ptr<raytracer::camera::PerspectiveCamera> &c);
    static void from_json(const json &j, std::unique_ptr<raytracer::camera::PerspectiveCamera> &c);
};

// NOLINTEND(readability-identifier-naming)

}
