/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** matrix class implementation
*/

#pragma once

#include <stdexcept>

#include "Matrix.hpp"
#include "Matrix4x4.hpp"

namespace raytracer::maths {

template <size_t rows, size_t cols, typename T>
Matrix<rows, cols, T>::Matrix(std::array<std::array<T, cols>, rows> values):
    _values(values)
{}

template <size_t rows, size_t cols, typename T>
Matrix<rows, cols, T>::Matrix(std::initializer_list<std::array<T, cols>> values)
{
    size_t rowIndex = 0;
    for (const auto &row: values) {
        if (rowIndex >= rows)
            break;
        _values[rowIndex++] = row;
    }
}

template <size_t rows, size_t cols, typename T>
[[nodiscard]] constexpr size_t Matrix<rows, cols, T>::getNbRows() const noexcept
{
    return rows;
}

template <size_t rows, size_t cols, typename T>
[[nodiscard]] constexpr size_t Matrix<rows, cols, T>::getNbCols() const noexcept
{
    return cols;
}

template <size_t rows, size_t cols, typename T>
std::array<T, cols> &Matrix<rows, cols, T>::operator[](const size_t &index)
{
    return _values[index];
}

template <size_t rows, size_t cols, typename T>
const std::array<T, cols> &Matrix<rows, cols, T>::operator[](
    const size_t &index) const
{
    return _values[index];
}

template <size_t rows, size_t cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator*(
    const Matrix &other) const
{
    if (cols != other.getNbRows())
        throw MatrixOperationException();

    std::array<std::array<T, cols>, rows> result{};

    std::size_t otherCols = other.getNbCols();
    for (size_t i = 0; i != rows; i++)
        for (size_t j = 0; j != otherCols; j++)
            for (size_t k = 0; k != cols; k++)
                result[i][j] += _values[i][k] * other[k][j];

    return Matrix(result);
}

template <size_t rows, size_t cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator/(
    const Matrix &other) const
{
    return (*this) * (static_cast<T>(1) / other);
}

template <size_t rows, size_t cols, typename T>
bool Matrix<rows, cols, T>::operator==(const Matrix &other) const
{
    return _values == other._values;
}

template <size_t rows, size_t cols, typename T>
bool Matrix<rows, cols, T>::operator!=(const Matrix &other) const
{
    return !(*this == other);
}

template <size_t rows, size_t cols, typename T>
[[nodiscard]] bool Matrix<rows, cols, T>::isIdentity() const
{
    if (rows != cols)
        return false;
    for (size_t i = 0; i != rows; i++)
        for (size_t j = 0; j != cols; j++)
            if ((i == j && _values[i][j] != static_cast<T>(1)) ||
                (i != j && _values[i][j] != static_cast<T>(0)))
                return false;
    return true;
}

template <size_t rows, size_t cols, typename T>
[[nodiscard]] double Matrix<rows, cols, T>::determinant() const
{
    throw std::runtime_error(
        "Determinant not implemented for this matrix size");
}

template <>
[[nodiscard]] inline double Matrix<4, 4, double>::determinant() const
{
    const auto &m  = _values;
    const auto a00 = m[0][0], a01 = m[0][1], a02 = m[0][2], a03 = m[0][3];
    const auto a10 = m[1][0], a11 = m[1][1], a12 = m[1][2], a13 = m[1][3];
    const auto a20 = m[2][0], a21 = m[2][1], a22 = m[2][2], a23 = m[2][3];
    const auto a30 = m[3][0], a31 = m[3][1], a32 = m[3][2], a33 = m[3][3];

    const auto m00 = (a11 * ((a22 * a33) - (a23 * a32))) -
        (a12 * ((a21 * a33) - (a23 * a31))) +
        (a13 * ((a21 * a32) - (a22 * a31)));
    const auto m01 = (a10 * ((a22 * a33) - (a23 * a32))) -
        (a12 * ((a20 * a33) - (a23 * a30))) +
        (a13 * ((a20 * a32) - (a22 * a30)));
    const auto m02 = (a10 * ((a21 * a33) - (a23 * a31))) -
        (a11 * ((a20 * a33) - (a23 * a30))) +
        (a13 * ((a20 * a31) - (a21 * a30)));
    const auto m03 = (a10 * ((a21 * a32) - (a22 * a31))) -
        (a11 * ((a20 * a32) - (a22 * a30))) +
        (a12 * ((a20 * a31) - (a21 * a30)));

    return (a00 * m00) - (a01 * m01) + (a02 * m02) - (a03 * m03);
}

} // namespace raytracer::maths
