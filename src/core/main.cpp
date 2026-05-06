/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#include <iostream>
#include <memory>
#include <fstream>

#include "Scene.hpp"
#include "SimpleIntegrator.hpp"
#include "SceneBuilder.hpp"

void start(const std::string configPath)
{
    constexpr auto width  = 1920;
    constexpr auto height = 1080;
    raytracer::camera::Film film(width, height);

    raytracer::scene::SceneBuilder builder;
    raytracer::integrator::SimpleIntegrator integrator;

    std::ifstream ifs(configPath);
    if (!ifs)
        throw std::runtime_error(std::string("Failed to open config file: ") + configPath);
    nlohmann::json config;
    ifs >> config;
    builder.buildScene(config);
    integrator.render(*builder.scene(), *builder.camera(), film);

    const std::string outputPath = "output.ppm";
    raytracer::camera::Film::write(film, outputPath);

    std::cout << "Rendered: " << outputPath << "\n";
}

int main(int ac, char **av)
{
    try {
        if (ac != 2) {
            std::cerr << "Usage: " << av[0] << " <config.json>" << std::endl;
            return 84;
        }
        start(av[1]);

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 84;
    }

    return 0;
}
