/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Serializer.hpp
*/

#pragma once

#include "jsonParser.hpp"
#include "maths/Color.hpp"

namespace nlohmann {

template <>
struct adl_serializer<raytracer::maths::Color> {
    static void to_json(json &j, const raytracer::maths::Color &color) {
        j = json{{"r", color.r}, {"g", color.g}, {"b", color.b}};
    }
    static void from_json(const json &j, raytracer::maths::Color &color) {
        j.at("r").get_to(color.r);
        j.at("g").get_to(color.g);
        j.at("b").get_to(color.b);
    }
};

}