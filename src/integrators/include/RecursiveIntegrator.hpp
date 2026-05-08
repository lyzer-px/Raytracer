/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** RecursiveIntegrator
*/

#ifndef RAYTRACER_RECURSIVEINTEGRATOR_HPP
#define RAYTRACER_RECURSIVEINTEGRATOR_HPP

#include "IIntegrator.hpp"

namespace raytracer {
namespace integrator {

class RecursiveIntegrator: public IIntegrator {
public:
    explicit RecursiveIntegrator(const int &maxDepth = 5);

    [[nodiscard]] maths::Color accumulatedRadiance(const maths::Ray &ray,
        const scene::Scene &scene, int depth) const override;

    void render(const scene::Scene &scene, const camera::ICamera &camera,
        camera::Film &film) const override;

private:
    int _maxDepth        = 5;
    int _samplesPerPixel = 6;
};

} // integrator
} // raytracer

#endif //RAYTRACER_RECURSIVEINTEGRATOR_HPP
