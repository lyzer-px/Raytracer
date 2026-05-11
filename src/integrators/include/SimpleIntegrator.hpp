/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SimpleIntegrator
*/

#pragma once

#include "IIntegrator.hpp"

namespace raytracer::integrator {
class SimpleIntegrator: public IIntegrator {
public:
    explicit SimpleIntegrator(int maxDepth = 0);

    [[nodiscard]] maths::Color accumulatedRadiance(const maths::Ray &ray,
        const scene::Scene &scene, int depth) const override;

    void render(const scene::Scene &scene, const camera::ICamera &camera,
        camera::Film &film) const override;

private:
    int _maxDepth;
};
} // namespace raytracer::integrator
