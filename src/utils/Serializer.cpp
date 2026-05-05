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
#include "jsonParser.hpp"

namespace nlohmann {

template<>
void adl_serializer<raytracer::maths::Vector3d>::to_json(json &j, const std::unique_ptr<raytracer::maths::Color> &c)
{
    throw std::runtime_error("Unimplemented");
}

template<>
void adl_serializer<raytracer::maths::Vector3d>from_json(const json &j, std::unique_ptr<Vector3d> &a)
{
    auto arr = json::array();
    
    a = std::make_unique(a[0], a[1], a[2]);
}

template<>
void adl_serializer<raytracer::maths::Color>::to_json(json &j, const std::unique_pt<raytracer::maths::Color> &c)
{
    throw std::runtime_error("Unimplemented");
}

template<>
void adl_serializer<raytracer::maths::Color>from_json(const json &j, const std::unique_ptr<raytracer::maths::Color> &a)
{
    a = std::make_unique(a[0], a[1], a[2]);
}

}
