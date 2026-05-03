/*
** EPITECH PROJECT, 2026
** OOP
** File description:
** Vector class implementation
*/

#pragma once

#include "Vector3.hpp"

template <typename T>
Vector3<T>::Vector3() : Vector<Vector3, 3, T>() {}

template <typename T>
Vector3<T>::Vector3(T x, T y, T z) noexcept : Vector<Vector3, 3, T>() {

    this->_data[0] = x;
    this->_data[1] = y;
    this->_data[2] = z;
}
