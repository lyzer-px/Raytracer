/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** IPrimitive
*/

#ifndef RAYTRACER_IPRIMITIVE_HPP
#define RAYTRACER_IPRIMITIVE_HPP
#include <optional>

#include "IMaterial.hpp"
#include "IShape.hpp"

namespace raytracer {
namespace shape {
class IPrimitive {
public:
    virtual ~IPrimitive() = default;

    [[nodiscard]] virtual std::optional<SurfaceInteraction> intersect(
        const Ray& ray) const = 0;

    [[nodiscard]] virtual bool intersectP(const Ray& ray) const = 0;

    [[nodiscard]] virtual const material::IMaterial* material() const = 0;
};
} // shape
} // raytracer

#endif //RAYTRACER_IPRIMITIVE_HPP
