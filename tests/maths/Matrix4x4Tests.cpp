/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Matrix4x4 unit tests
*/

#include <gtest/gtest.h>
#include "Matrix4x4.hpp"

using raytracer::maths::Matrix4x4;

static void expect_matrix_near(const Matrix4x4 &a, const Matrix4x4 &b, double eps = 1e-9) // NOLINT
{
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            EXPECT_NEAR(a[i][j], b[i][j], eps);
}

TEST(Matrix4x4Test, ConstructorAndIdentity)
{
    Matrix4x4 I{{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};
    EXPECT_TRUE(I.isIdentity());
    // explicit element checks
    EXPECT_DOUBLE_EQ(I[0][0], 1.0);
    EXPECT_DOUBLE_EQ(I[1][1], 1.0);
    EXPECT_DOUBLE_EQ(I[2][2], 1.0);
    EXPECT_DOUBLE_EQ(I[3][3], 1.0);
}

TEST(Matrix4x4Test, Transpose)
{
    Matrix4x4 m{{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}}};
    Matrix4x4 expected{{{1,5,9,13},{2,6,10,14},{3,7,11,15},{4,8,12,16}}};
    expect_matrix_near(raytracer::maths::Transpose(m), expected);
}

TEST(Matrix4x4Test, DeterminantIdentityAndZero)
{
    Matrix4x4 I{{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};
    EXPECT_DOUBLE_EQ(I.determinant(), 1.0);

    // Matrix with dependent rows -> det == 0
    Matrix4x4 singular{{{1,2,3,4},{2,4,6,8},{3,6,9,12},{4,8,12,16}}};
    EXPECT_DOUBLE_EQ(singular.determinant(), 0.0);
}

TEST(Matrix4x4Test, MultiplyIdentity)
{
    Matrix4x4 m{{{2,3,5,7},{11,13,17,19},{23,29,31,37},{41,43,47,53}}};
    Matrix4x4 I{{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};
    expect_matrix_near(m * I, m);
    expect_matrix_near(I * m, m);
}

TEST(Matrix4x4Test, InverseDiagonal)
{
    // diagonal matrix, inverse is reciprocal on diagonal
    Matrix4x4 diag{{{2,0,0,0},{0,3,0,0},{0,0,4,0},{0,0,0,5}}};
    Matrix4x4 invExpected{{{1.0/2,0,0,0},{0,1.0/3,0,0},{0,0,1.0/4,0},{0,0,0,1.0/5}}};
    Matrix4x4 inv = raytracer::maths::Inverse(diag);
    expect_matrix_near(inv, invExpected);

    // product should be identity
    Matrix4x4 prod = diag * inv;
    Matrix4x4 I{{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};
    expect_matrix_near(prod, I);
}

TEST(Matrix4x4Test, InverseThrowsOnSingular)
{
    Matrix4x4 singular{{{1,2,3,4},{1,2,3,4},{5,6,7,8},{9,10,11,12}}};
    EXPECT_THROW((void)raytracer::maths::Inverse(singular), std::runtime_error);
}
