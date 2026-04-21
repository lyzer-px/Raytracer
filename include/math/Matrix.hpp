/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <cstddef>
#include <exception>

template <size_t rows, size_t cols, typename T = double>
class Matrix {
public:
    Matrix() = default;
    Matrix(std::array<std::array<T, cols>, rows> values) : _values(values) {}

    constexpr size_t getNbRows() const noexcept { return rows; }
    constexpr size_t getNbCols() const noexcept { return cols; }

    class MatrixOperationException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "invalid operation";
        }
    };

    std::array<T, cols>& operator[](size_t i) {
        return _values[i];
    }

    const std::array<T, cols>& operator[](size_t i) const {
        return _values[i];
    }

    template <size_t other_cols>
    Matrix<rows, other_cols, T> operator*(const Matrix<cols, other_cols, T>& other) const {
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

private:
    std::array<std::array<T, cols>, rows> _values;
};

using Matrix3x3 = Matrix<3, 3>;

#endif // !MATRIX
