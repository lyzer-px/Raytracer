/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** matrix class implementation
*/

#pragma once

#include "Matrix.hpp"

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
std::array<T, cols>& Matrix<rows, cols, T>::operator[](const size_t &index)
{
    return _values[index];
}

template <size_t rows, size_t cols, typename T>
const std::array<T, cols>& Matrix<rows, cols, T>::operator[](const size_t &index) const
{
    return _values[index];
}


template <size_t rows, size_t cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator*(const Matrix &other) const
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
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator/(const Matrix &other) const
{
    return (*this) * (static_cast<T>(1) / other);
}
