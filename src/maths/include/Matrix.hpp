/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** matrix class declaration
*/

#pragma once

#include <cstddef>
#include <exception>
#include <array>

template <size_t rows, size_t cols, typename T = double>
class Matrix {
public:
    Matrix() = default;
    Matrix(std::array<std::array<T, cols>, rows> values) : _values(values) {}

    constexpr size_t getNbRows() const noexcept;
    constexpr size_t getNbCols() const noexcept;

    std::array<T, cols>& operator[](const size_t &i);
    const std::array<T, cols>& operator[](const size_t &i) const;

    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;

private:
    std::array<std::array<T, cols>, rows> _values;
};

class MatrixOperationException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "invalid operation";
        }
    };

using Matrix3x3 = Matrix<3, 3>;
using Matrix4x4 = Matrix<4, 4>;

#include "Matrix.tpp"
