/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "Color.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"

namespace raytracer::scene {
class Scene {
public:
    Scene();

    void addPrimitive(std::unique_ptr<shape::IPrimitive> &primitive);

    void addLight(std::unique_ptr<light::ILight> &light);

    void setBackgroundColor(const maths::Color &color);

    [[nodiscard]] std::optional<shape::SurfaceInteraction> intersect(
        const maths::Ray &ray) const;

    [[nodiscard]] bool intersectAny(const maths::Ray &ray) const;

    [[nodiscard]] const std::vector<std::unique_ptr<light::ILight>> &
    lights() const;

    [[nodiscard]] maths::Color backgroundColor() const;

private:
    std::vector<std::unique_ptr<shape::IPrimitive>> _primitives;
    std::vector<std::unique_ptr<light::ILight>> _lights;
    maths::Color _background;
};
} // namespace raytracer::scene
