/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#include "include/Scene.hpp"

#include <cassert>

namespace raytracer {
namespace scene {
void Scene::addPrimitive(std::unique_ptr<shape::IPrimitive> &primitive)
{
    assert(primitive != nullptr);
    _primitives.push_back(std::move(primitive));
}

void Scene::addLight(std::unique_ptr<light::ILight> &light)
{
    assert(light != nullptr);
    _lights.push_back(std::move(light));
}

void Scene::setBackgroundColor(const Color &color)
{
    _background = color;
}

std::optional<shape::SurfaceInteraction> Scene::intersect(const Ray &ray) const
{
    std::optional<shape::SurfaceInteraction> hitPointData = std::nullopt;

    for (const auto &primitive: _primitives) {
        const auto si = primitive->intersect(ray);
        if (si)
            hitPointData = si;
    }

    return hitPointData;
}

bool Scene::intersectAny(const Ray &ray) const
{
    for (const auto &primitive: _primitives) {
        if (primitive->intersectP(ray))
            return true;
    }

    return false;
}

const std::vector<std::unique_ptr<light::ILight>> & Scene::lights() const
{
    return _lights;
}

Color Scene::backgroundColor() const
{
    return _background;
}
} // scene
} // raytracer