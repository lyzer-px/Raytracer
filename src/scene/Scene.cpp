/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Scene
*/

#include "include/Scene.hpp"

#include <cassert>

namespace raytracer::scene {
Scene::Scene(): _background{maths::Color{0.0, 0.0, 0.0}}
{}

void Scene::addPrimitive(std::unique_ptr<shape::IPrimitive> &primitive)
{
    assert(primitive != nullptr);
    _primitives.push_back(std::move(primitive));
}

void Scene::buildAccelerator()
{
    _bvh = std::make_unique<accelerator::BvhAggregate>(std::move(_primitives));
}

void Scene::addLight(std::unique_ptr<light::ILight> &light)
{
    assert(light != nullptr);
    _lights.push_back(std::move(light));
}

void Scene::addMaterial(
    const std::string &name, std::unique_ptr<material::IMaterial> &material)
{
    assert(material != nullptr);
    _materials[name] = std::move(material);
}

void Scene::setBackgroundColor(const maths::Color &color)
{
    _background = color;
}

std::optional<shape::SurfaceInteraction> Scene::intersect(
    const maths::Ray &ray) const
{
    if (!_bvh)
        return std::nullopt;
    return _bvh->intersect(ray);
}

bool Scene::intersectAny(const maths::Ray &ray) const
{
    if (!_bvh)
        return false;
    return _bvh->intersectP(ray);
}

bool Scene::isOccluded(
    const maths::Point3d &origin, const maths::Vector3d &dir, double distance) const
{
    maths::Point3d pos = origin;
    double remaining   = distance;
    while (remaining > 0.001) {
        const maths::Ray testRay{pos, dir, remaining};
        const auto blocker = intersect(testRay);
        if (!blocker)
            return false;
        if (blocker->primitive->material()->castsShadow())
            return true;
        const double step = (blocker->hitPoint - pos).length() + 0.0002;
        pos       = pos + dir * step;
        remaining -= step;
    }
    return false;
}


const std::vector<std::unique_ptr<light::ILight>> &Scene::lights() const
{
    return _lights;
}

maths::Color Scene::backgroundColor() const
{
    return _background;
}

material::IMaterial *Scene::getMaterial(const std::string &name) const
{
    if (_materials.contains(name))
        return _materials.at(name).get();
    throw std::runtime_error("Material '" + name + "' not found in scene");
}

} // namespace raytracer::scene
