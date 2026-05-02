/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#ifndef RAYTRACER_SCENE_HPP
#define RAYTRACER_SCENE_HPP

#include <memory>
#include <optional>
#include <vector>

#include "Color.hpp"
#include "ILight.hpp"
#include "IPrimitive.hpp"

namespace raytracer {
namespace scene {
class Scene {
public:
    Scene();

    void addPrimitive(std::unique_ptr<shape::IPrimitive> &primitive);

    void addLight(std::unique_ptr<light::ILight> &light);

    void setBackgroundColor(const Color &color);

    [[nodiscard]] std::optional<shape::SurfaceInteraction> intersect(
        const Ray &ray) const;

    [[nodiscard]] bool intersectAny(const Ray &ray) const;

    [[nodiscard]] const std::vector<std::unique_ptr<light::ILight>> &
    lights() const;

    [[nodiscard]] Color backgroundColor() const;

private:
    std::vector<std::unique_ptr<shape::IPrimitive>> _primitives;
    std::vector<std::unique_ptr<light::ILight>> _lights;
    Color _background;
};
} // scene
} // raytracer

#endif //RAYTRACER_SCENE_HPP
