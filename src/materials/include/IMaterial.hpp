/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IMaterial
*/

#ifndef RAYTRACER_IMATERIAL_HPP
#define RAYTRACER_IMATERIAL_HPP

#include "Color.hpp"
#include "IShape.hpp"

namespace raytracer {
namespace material {

class IMaterial {
public:
    virtual ~IMaterial() = default;

    [[nodiscard]] virtual Color getColor(
        const shape::SurfaceInteraction &si) const = 0; //NOLINT
};

} // material
} // raytracer

#endif //RAYTRACER_IMATERIAL_HPP
