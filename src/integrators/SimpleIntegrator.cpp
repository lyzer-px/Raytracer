/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** SimpleIntegrator
*/

#include "SimpleIntegrator.hpp"

namespace raytracer {
namespace integrator {
SimpleIntegrator::SimpleIntegrator(int maxDepth): _maxDepth{maxDepth}
{}

maths::Color SimpleIntegrator::Li(const maths::Ray &ray, const scene::Scene &scene,
    int) const
{
    const auto si = scene.intersect(ray);

    if (!si)
        return scene.backgroundColor();

    const material::IMaterial *mat = si->primitive->material();
    const maths::Color surfaceColor       = mat->getColor(*si);

    maths::Color accumulatedRadiance(0.0, 0.0, 0.0);

    for (const auto &light: scene.lights()) {
        light::LightSample ls = light->sample(si->hitPoint);

        if (!light->isDelta()) {
            accumulatedRadiance = accumulatedRadiance + surfaceColor * ls.
                radiance;
            continue;
        }

        maths::Point3d shadowOrigin = si->hitPoint + (maths::Vector3d(si->normal) * 0.0001);
        maths::Ray shadowRay(shadowOrigin, -ls.wi, ls.distance);

        if (scene.intersectAny(shadowRay))
            continue;

        const double cosTheta = std::max(-(maths::Vector3d{si->normal}.dot(ls.wi)),
            0.0);

        accumulatedRadiance = accumulatedRadiance + surfaceColor * ls.radiance *
            cosTheta;
    }

    return accumulatedRadiance;
}

void SimpleIntegrator::render(const scene::Scene &scene,
    const camera::ICamera &camera, camera::Film &film) const
{
    for (auto y = 0; y < film.height(); ++y) {
        for (auto x = 0; x < film.width(); ++x) {
            const double u = (x + 0.5) / static_cast<double>(film.width());
            const double v = (y + 0.5) / static_cast<double>(film.height());

            maths::Ray ray = camera.generateRay(u, v);

            maths::Color color = Li(ray, scene, _maxDepth);

            film.addSample(x, y, color);
        }
    }
}
} // integrator
} // raytracer
