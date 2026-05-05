/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.cpp
*/

#include <memory>
#include <stdexcept>

#include "Serializer.hpp"
#include "ICamera.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"
#include "IMaterial.hpp"
#include "Color.hpp"
#include "PerspectiveCamera.hpp"
#include "Point.hpp"
#include "jsonParser.hpp"

namespace nlohmann {

void adl_serializer<raytracer::maths::Vector3d>::to_json(json &, const raytracer::maths::Vector3d &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Vector3d>::from_json(const json &json,std::unique_ptr<raytracer::maths::Vector3d> &a)
{
    a = std::make_unique<raytracer::maths::Vector3d>(json["resolution"].get<raytracer::maths::Vector3d>());
}

void adl_serializer<raytracer::maths::Color>::to_json(json &, const std::unique_ptr<raytracer::maths::Color> &c)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Color>::from_json(const json &j, const std::unique_ptr<raytracer::maths::Color> &a)
{
    a = std::make_unique<raytracer::maths::Color>(j[0], j[1], j[2]);
}

void adl_serializer<raytracer::maths::Normal3d>::to_json(json &, const std::unique_ptr<raytracer::maths::Normal3d> &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Normal3d>::from_json(const json &j, const std::unique_ptr<raytracer::maths::Normal3d> &a)
{
    a = std::make_unique<raytracer::maths::Normal3d>(j[0], j[1], j[2]);
}

void adl_serializer<raytracer::maths::Point3d>::to_json(json &, const std::unique_ptr<raytracer::maths::Point3d> &)
{
    throw std::runtime_error("Unimplemented");
}

void adl_serializer<raytracer::maths::Point3d>::from_json(const json &j, const std::unique_ptr<raytracer::maths::Point3d> &a)
{
    a = std::make_unique<raytracer::maths::Point3d>(j[0], j[1], j[2]);
}

}