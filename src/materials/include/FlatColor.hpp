/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#ifndef RAYTRACER_FLATCOLOR_HPP
#define RAYTRACER_FLATCOLOR_HPP

#include "Color.hpp"
#include "IMaterial.hpp"
#include "IShape.hpp"
#include <sys/stat.h>

namespace raytracer {
namespace material {

class FlatColor: public IMaterial {
public:
    explicit FlatColor(nlohmann::json &config);
    explicit FlatColor(const maths::Color &color);

    [[nodiscard]] maths::Color
        getColor(const shape::SurfaceInteraction &si) const override; // NOLINT

    static void create(const nlohmann::json &config);
private:
    maths::Color _color;
};

} // material
} // raytracer

#endif //RAYTRACER_FLATCOLOR_HPP
