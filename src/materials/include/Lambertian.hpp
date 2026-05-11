/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** FlatColor
*/

#ifndef RAYTRACER_FLATCOLOR_HPP
#define RAYTRACER_FLATCOLOR_HPP

#include "Color.hpp"
#include "IMaterial.hpp"
#include "IShape.hpp"
#include "Serializer.hpp"

namespace raytracer {
namespace material {

class Lambertian: public IMaterial {
public:
    explicit Lambertian(const maths::Color &color);

    [[nodiscard]] static std::unique_ptr<IMaterial> create(
        const nlohmann::json &config);

    [[nodiscard]] std::optional<ScatterRecord> scatter(const maths::Ray &ray,
        const shape::SurfaceInteraction &si) const override;

private:
    maths::Color _albedo;
};

} // material
} // raytracer

#endif //RAYTRACER_FLATCOLOR_HPP
