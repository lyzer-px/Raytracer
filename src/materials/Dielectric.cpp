/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Dielectric
*/

#include "include/Dielectric.hpp"

namespace raytracer {
namespace material {
double Dielectric::schlick(const double &cosTheta, const double &ratio)
{
    double r0 = (1.0 - ratio) / (1.0 + ratio);
    r0 = r0 * r0;

    return r0 + ((1.0 - r0) * std::pow(1.0 - cosTheta, 5.0));
}
} // material
} // raytracer