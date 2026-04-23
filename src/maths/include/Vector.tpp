/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** 
*/

#pragma once

#include <array>
#include <string>
#include "Vector.hpp"

template<std::size_t N, typename T>
Vector<N, T>::Vector(std::array<T, N> &values) : _data(values) {}

template<std::size_t N, typename T>
T& Vector<N, T>::operator[](std::size_t i)
{
    return _data[i];
}

template<std::size_t N, typename T>
const T& Vector<N, T>::operator[](std::size_t i) const
{
    return _data[i];
}


template<std::size_t N, typename T>
Vector<N, T> Vector<N, T>::operator+(const Vector<N, T>& other) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] + other[i]; 
    }
    return Vector(array);
}

template<std::size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-(const Vector& other) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] - other[i]; 
    }
    return Vector(array);

}

template<std::size_t N, typename T>
Vector<N, T> Vector<N, T>::operator*(T scalar) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] * scalar; 
    }
    return Vector(array);

}

template<std::size_t N, typename T>
Vector<N, T> Vector<N, T>::operator/(T scalar) const
{
    std::array<T, N> array;

    for (std::size_t i = 0; i != N; i++) {
        array[i] = _data[i] / scalar; 
    }
    return Vector(array);

}

template<std::size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-() const
{
    return *this * static_cast<T>(-1);
}


template<std::size_t N, typename T>
std::ostream &Vector<N, T>::operator<<(std::ostream &o) const
{
    o << "Vector<" << N << "> {";
    for (std::size_t i = 0; i != N; ++i) {
        o << std::to_string(_data[i]) + (i != N ? "," : "");
    }
    o << "}";
    return o;
}
