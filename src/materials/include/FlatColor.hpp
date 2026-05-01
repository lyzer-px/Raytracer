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

namespace raytracer {
namespace material {

class FlatColor: public IMaterial {
public:
    explicit FlatColor(const Color &color);

    [[nodiscard]] Color
        getColor(const shape::SurfaceInteraction &si) const override; // NOLINT

private:
    Color _color;
};

} // material
} // raytracer

#endif //RAYTRACER_FLATCOLOR_HPP
