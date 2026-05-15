/*
** EPITECH PROJECT, 2025
** Raytracer
** File description:
** Matrix4x4.cpp
*/

#include "Matrix4x4.hpp"

#include <array>
#include <stdexcept>

namespace raytracer::maths {

const Matrix4x4<double> IDENTITY_MATRIX4X4{
    {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};

template <typename T> Matrix4x4<T> transpose(const Matrix4x4<T> &other)
{
    Matrix4x4<T> result;
    for (size_t i = 0; i < other.getNbRows(); ++i) {
        for (size_t j = 0; j < other.getNbCols(); ++j) {
            result[j][i] = other[i][j];
        }
    }
    return result;
}

template <typename T> Matrix4x4<T> inverse(const Matrix4x4<T> &mat)
{
    std::array<double, 16> invOut{};
    const double *m = mat[0].data();

    const double s0 = (m[0] * m[5]) - (m[4] * m[1]);
    const double s1 = (m[0] * m[6]) - (m[4] * m[2]);
    const double s2 = (m[0] * m[7]) - (m[4] * m[3]);
    const double s3 = (m[1] * m[6]) - (m[5] * m[2]);
    const double s4 = (m[1] * m[7]) - (m[5] * m[3]);
    const double s5 = (m[2] * m[7]) - (m[6] * m[3]);

    const double c5 = (m[10] * m[15]) - (m[14] * m[11]);
    const double c4 = (m[9] * m[15]) - (m[13] * m[11]);
    const double c3 = (m[9] * m[14]) - (m[13] * m[10]);
    const double c2 = (m[8] * m[15]) - (m[12] * m[11]);
    const double c1 = (m[8] * m[14]) - (m[12] * m[10]);
    const double c0 = (m[8] * m[13]) - (m[12] * m[9]);

    invOut[0] = ((m[5] * c5) - (m[6] * c4)) + (m[7] * c3);
    invOut[1] = ((-m[1] * c5) + (m[2] * c4)) - (m[3] * c3);
    invOut[2] = ((m[13] * s5) - (m[14] * s4)) + (m[15] * s3);
    invOut[3] = ((-m[9] * s5) + (m[10] * s4)) - (m[11] * s3);

    invOut[4] = ((-m[4] * c5) + (m[6] * c2)) - (m[7] * c1);
    invOut[5] = ((m[0] * c5) - (m[2] * c2)) + (m[3] * c1);
    invOut[6] = ((-m[12] * s5) + (m[14] * s2)) - (m[15] * s1);
    invOut[7] = ((m[8] * s5) - (m[10] * s2)) + (m[11] * s1);

    invOut[8]  = ((m[4] * c4) - (m[5] * c2)) + (m[7] * c0);
    invOut[9]  = ((-m[0] * c4) + (m[1] * c2)) - (m[3] * c0);
    invOut[10] = ((m[12] * s4) - (m[13] * s2)) + (m[15] * s0);
    invOut[11] = ((-m[8] * s4) + (m[9] * s2)) - (m[11] * s0);

    invOut[12] = ((-m[4] * c3) + (m[5] * c1)) - (m[6] * c0);
    invOut[13] = ((m[0] * c3) - (m[1] * c1)) + (m[2] * c0);
    invOut[14] = ((-m[12] * s3) + (m[13] * s1)) - (m[14] * s0);
    invOut[15] = ((m[8] * s3) - (m[9] * s1)) + (m[10] * s0);

    double det = (m[0] * invOut[0]) + (m[1] * invOut[4]) + (m[2] * invOut[8]) +
        (m[3] * invOut[12]);
    if (det == 0.0)
        throw std::runtime_error(
            "Matrix4x4::inverse: matrix is singular and cannot be inverted");

    det = 1.0 / det;
    for (int i = 0; i < 16; ++i)
        invOut[i] *= det;

    return Matrix4x4<T>({{invOut[0], invOut[1], invOut[2], invOut[3]},
        {invOut[4], invOut[5], invOut[6], invOut[7]},
        {invOut[8], invOut[9], invOut[10], invOut[11]},
        {invOut[12], invOut[13], invOut[14], invOut[15]}});
}

template Matrix4x4<double> transpose(const Matrix4x4<double> &);
template Matrix4x4<double> inverse(const Matrix4x4<double> &);

} // namespace raytracer::maths
