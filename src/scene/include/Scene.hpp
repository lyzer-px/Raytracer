/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include <vector>

#include "ICamera.hpp"
#include "Color.hpp"
#include "ILight.hpp"
#include "IMaterial.hpp"
#include "IPrimitive.hpp"

namespace raytracer::scene {
class Scene {
public:
    Scene();

    void addPrimitive(std::unique_ptr<shape::IPrimitive> &primitive);

    void addLight(std::unique_ptr<light::ILight> &light);

    void addMaterial(const std::string &name, std::unique_ptr<material::IMaterial> &material);

    void setBackgroundColor(const maths::Color &color);

    [[nodiscard]] std::optional<shape::SurfaceInteraction> intersect(
        const maths::Ray &ray) const;

    [[nodiscard]] bool intersectAny(const maths::Ray &ray) const;

    [[nodiscard]] const std::vector<std::unique_ptr<light::ILight>> &
    lights() const;

    [[nodiscard]] maths::Color backgroundColor() const;

    material::IMaterial *getMaterial(const std::string &name) const;

private:
    std::vector<std::unique_ptr<shape::IPrimitive>> _primitives;
    std::vector<std::unique_ptr<light::ILight>> _lights;
    std::unordered_map<std::string, std::unique_ptr<material::IMaterial>> _materials;
    std::unique_ptr<camera::ICamera> _camera;
    maths::Color _background;
};
} // namespace raytracer::scene
