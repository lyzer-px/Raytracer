/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#pragma once

#include "Matrix.hpp"

template <size_t rows, size_t cols, typename T>
constexpr size_t Matrix<rows, cols, T>::getNbRows() const noexcept
{
    return rows;
}

template <size_t rows, size_t cols, typename T>
constexpr size_t Matrix<rows, cols, T>::getNbCols() const noexcept
{
    return cols;
}

template <size_t rows, size_t cols, typename T>
std::array<T, cols>& Matrix<rows, cols, T>::operator[](const size_t i)
{
    return _values[i];
}

/*
template <size_t rows, size_t cols, size_t other_rows, size_t other_cols, typename T>
Matrix<> Matrix<rows, cols, T>::operator*(const Matrix &other) const {
        Matrix<rows, other_cols, T> result;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other_cols; ++j) {
                result[i][j] = 0;
                for (size_t k = 0; k < cols; ++k) {
                    result[i][j] += this-> _values[i][k] * other[k][j];
                }
            }
        }
        return result;
    }
*/
