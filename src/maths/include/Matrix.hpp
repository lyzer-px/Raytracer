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
#include <initializer_list>

namespace raytracer::maths {

template <size_t rows, size_t cols, typename T = double>
class Matrix {
public:
    Matrix() = default;
    Matrix(std::array<std::array<T, cols>, rows> values);
    Matrix(std::initializer_list<std::array<T, cols>> values);

    [[nodiscard]] constexpr size_t getNbRows() const noexcept;
    [[nodiscard]] constexpr size_t getNbCols() const noexcept;

    std::array<T, cols>& operator[](const size_t &index);
    const std::array<T, cols>& operator[](const size_t &index) const;

    Matrix operator*(const Matrix &other) const;
    Matrix operator/(const Matrix &other) const;

    bool operator==(const Matrix &other) const;
    bool operator!=(const Matrix &other) const;

    [[nodiscard]] bool isIdentity() const;

    [[nodiscard]] double determinant() const requires (rows == cols) && (rows == 4);

private:
    std::array<std::array<T, cols>, rows> _values;
};

class MatrixOperationException : public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override {
            return "invalid operation";
        }
    };

using Matrix2x2 = Matrix<2, 2>;
using Matrix3x3 = Matrix<3, 3>;

} // namespace raytracer::maths

#include "Matrix.tpp"
