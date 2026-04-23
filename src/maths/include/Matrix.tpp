/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#ifndef MATRIX_TPP
#define MATRIX_TPP

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

#endif // !MATRIX
