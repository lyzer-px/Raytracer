/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** RecursiveIntegrator
*/

#include "RecursiveIntegrator.hpp"
#include "maths.hpp"

namespace raytracer {
namespace integrator {
RecursiveIntegrator::RecursiveIntegrator(const int &maxDepth, int samplesPerPixel)
    : _maxDepth{maxDepth}, _samplesPerPixel{samplesPerPixel}
{}

maths::Color RecursiveIntegrator::accumulatedRadiance(const maths::Ray &ray,
    const scene::Scene &scene, int depth) const
{
    const auto si = scene.intersect(ray);

    if (!si)
        return scene.backgroundColor();

    const material::IMaterial *material = si->primitive->material();
    const maths::Color emitted          = material->emitted(*si);
    const auto scatter                  = material->scatter(ray, *si);

    if (!scatter)
        return emitted;

    maths::Color direct(0.0, 0.0, 0.0);
    for (const auto &light: scene.lights()) {
        light::LightSample ls = light->sample(si->hitPoint);

        if (!light->isDelta()) {
            direct = direct + scatter->attenuation * ls.radiance;
            continue;
        }

        maths::Point3d shadowOrigin =
            si->hitPoint + maths::Vector3d(si->normal) * 0.0001;
        maths::Ray shadowRay(shadowOrigin, -ls.wi, ls.distance);

        if (scene.intersectAny(shadowRay))
            continue;

        const double cosTheta =
            std::max(-(maths::Vector3d{si->normal}.dot(ls.wi)), 0.0);
        direct = direct + scatter->attenuation * ls.radiance * cosTheta;
    }

    if (depth == 0)
        return emitted + direct;

    const maths::Color indirect =
        scatter->attenuation * accumulatedRadiance(scatter->scattered, scene,
            depth - 1);

    return emitted + direct + indirect;
}

void RecursiveIntegrator::render(const scene::Scene &scene,
    const camera::ICamera &camera, camera::Film &film) const
{
    for (auto y = 0; y < film.height(); ++y) {
        for (auto x = 0; x < film.width(); ++x) {
            maths::Color accumulated(0.0, 0.0, 0.0);

            for (int s = 0; s < _samplesPerPixel; ++s) {
                const double u =
                    (x + maths::randomNumber<double>()) /
                    static_cast<double>(film.width());
                const double v =
                    (y + maths::randomNumber<double>()) /
                    static_cast<double>(film.height());

                maths::Ray ray = camera.generateRay(u, v);
                accumulated    =
                    accumulated + accumulatedRadiance(ray, scene, _maxDepth);
            }

            film.addSample(x, y, accumulated * (1.0 / _samplesPerPixel));
        }
    }
}
} // integrator
} // raytracer
