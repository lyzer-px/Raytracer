/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#include <iostream>
#include <memory>

#include "AmbientLight.hpp"
#include "Color.hpp"
#include "DirectionalLight.hpp"
#include "Film.hpp"
#include "FlatColor.hpp"
#include "GeometricPrimitive.hpp"
#include "maths_types.hpp"
#include "PerspectiveCamera.hpp"
#include "Scene.hpp"
#include "SimpleIntegrator.hpp"
#include "Sphere.hpp"

static raytracer::scene::Scene buildScene()
{
    raytracer::scene::Scene scene;

    std::unique_ptr<raytracer::shape::IShape> sphere = std::make_unique<
        raytracer::shape::Sphere>(Point3d{60.0, 5.0, 40.0}, 25.0);
    std::unique_ptr<raytracer::material::IMaterial> sphereMaterial =
        std::make_unique<
            raytracer::material::FlatColor>(Color{1.0, 0.25, 0.25});
    std::unique_ptr<raytracer::shape::IPrimitive> spherePrimitive =
        std::make_unique<raytracer::shape::GeometricPrimitive>(sphere,
            sphereMaterial);
    scene.addPrimitive(spherePrimitive);

    std::unique_ptr<raytracer::shape::IShape> sphere2 = std::make_unique<
        raytracer::shape::Sphere>(Point3d{0.0, 0.0, 0.0}, 25.0);
    std::unique_ptr<raytracer::material::IMaterial> sphereMaterial2 =
        std::make_unique<
            raytracer::material::FlatColor>(Color{0.0, 1.0, 0.0});
    std::unique_ptr<raytracer::shape::IPrimitive> spherePrimitive2 =
        std::make_unique<raytracer::shape::GeometricPrimitive>(sphere2,
            sphereMaterial2);
    scene.addPrimitive(spherePrimitive2);

    std::unique_ptr<raytracer::light::ILight> ambient = std::make_unique<
        raytracer::light::AmbientLight>(Color{0.3, 0.3, 0.3});
    scene.addLight(ambient);

    std::unique_ptr<raytracer::light::ILight> directional = std::make_unique<
        raytracer::light::DirectionalLight>(Vector3d{-1.0, -1.0, -1.0},
        Color{1.0, 1.0, 1.0});
    scene.addLight(directional);

    scene.setBackgroundColor(Color{0.2, 0.3, 1.0});

    return scene;
}

int main()
{
    try {
        const raytracer::scene::Scene scene = buildScene();

        const raytracer::camera::PerspectiveCamera camera(
            Point3d{0.0, -100.0, 10.0},
            Point3d{0.0, 0.0, 0.0},
            Vector3d{0.0, 0.0, 1.0},
            72.0,
            16.0 / 9.0
        );

        constexpr auto width  = 1920;
        constexpr auto height = 1080;
        raytracer::camera::Film film(width, height);

        raytracer::integrator::SimpleIntegrator integrator;
        integrator.render(scene, camera, film);

        const std::string outputPath = "output.ppm";
        raytracer::camera::Film::write(film, outputPath);

        std::cout << "Rendered: " << outputPath << "\n";

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 84;
    }

    return 0;
}
