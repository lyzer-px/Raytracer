/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IIntegrator
*/

#ifndef RAYTRACER_IINTEGRATOR_HPP
#define RAYTRACER_IINTEGRATOR_HPP

#include "Color.hpp"
#include "Film.hpp"
#include "ICamera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

namespace raytracer {
namespace integrator {
class IIntegrator {
public:
    virtual ~IIntegrator() = default;

    virtual Color Li(const Ray &ray, const scene::Scene &scene,
        int depth) const = 0;

    virtual void render(const scene::Scene &scene,
        const camera::ICamera &camera, camera::Film &film) const = 0;
};
} // integrator
} // raytracer

#endif //RAYTRACER_IINTEGRATOR_HPP
