/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IIntegrator
*/

#pragma once

#include "Color.hpp"
#include "Film.hpp"
#include "ICamera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

namespace raytracer::integrator {
class IIntegrator {
public:
    virtual ~IIntegrator() = default;

    virtual maths::Color Li(
        const maths::Ray &ray, const scene::Scene &scene, int depth) const = 0;

    virtual void render(const scene::Scene &scene,
        const camera::ICamera &camera, camera::Film &film) const = 0;
};
} // namespace raytracer::integrator
