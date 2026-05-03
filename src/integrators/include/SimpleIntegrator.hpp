/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SimpleIntegrator
*/

#ifndef RAYTRACER_SIMPLEINTEGRATOR_HPP
#define RAYTRACER_SIMPLEINTEGRATOR_HPP

#include "IIntegrator.hpp"

namespace raytracer {
namespace integrator {
class SimpleIntegrator: public IIntegrator {
public:
    explicit SimpleIntegrator(int maxDepth = 0);

    Color Li(const Ray &ray,
        const scene::Scene &scene,
        int depth) const override;

    void render(const scene::Scene &scene, const camera::ICamera &camera,
        camera::Film &film) const override;

private:
    int _maxDepth;
};
} // integrator
} // raytracer

#endif //RAYTRACER_SIMPLEINTEGRATOR_HPP
