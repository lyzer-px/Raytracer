/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.cpp
*/

#include "Serializer.hpp"

#include <memory>
#include <stdexcept>

#include "jsonParser.hpp"

namespace nlohmann {

void adl_serializer<raytracer::maths::Vector3d>::to_json(
    json &, const raytracer::maths::Vector3d &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Vector3d>::from_json(
    const json &j, raytracer::maths::Vector3d &c)
{
    c = raytracer::maths::Vector3d(
        j.at(0).get<double>(), j.at(1).get<double>(), j.at(2).get<double>());
}

void adl_serializer<raytracer::maths::Color>::to_json(
    json &, const raytracer::maths::Color &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Color>::from_json(
    const json &j, raytracer::maths::Color &c)
{
    c = raytracer::maths::Color(
        j.at(0).get<double>() / raytracer::maths::MAX_RGB_VALUE,
        j.at(1).get<double>() / raytracer::maths::MAX_RGB_VALUE,
        j.at(2).get<double>() / raytracer::maths::MAX_RGB_VALUE);
}

void adl_serializer<raytracer::maths::Normal3d>::to_json(
    json &, const raytracer::maths::Normal3d &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Normal3d>::from_json(
    const json &j, raytracer::maths::Normal3d &c)
{
    c = raytracer::maths::Normal3d(
        j.at(0).get<double>(), j.at(1).get<double>(), j.at(2).get<double>());
}

void adl_serializer<raytracer::maths::Point3d>::to_json(
    json &, const raytracer::maths::Point3d &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Point3d>::from_json(
    const json &j, raytracer::maths::Point3d &c)
{
    c = raytracer::maths::Point3d(
        j.at(0).get<double>(), j.at(1).get<double>(), j.at(2).get<double>());
}

void adl_serializer<raytracer::camera::PerspectiveCamera>::to_json(
    json &, const std::unique_ptr<raytracer::camera::PerspectiveCamera> &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::camera::PerspectiveCamera>::from_json(
    const json &j, std::unique_ptr<raytracer::camera::PerspectiveCamera> &c)
{
    c = std::make_unique<raytracer::camera::PerspectiveCamera>(j);
}

} // namespace nlohmann
