/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Vector class unit tests
*/

#include "Vector.hpp"

#include <cmath>
#include <stdexcept>
#include <gtest/gtest.h>

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(VectorTest, DefaultConstructor)
{
    Vector<3> vec;
    SUCCEED();

    EXPECT_DOUBLE_EQ(vec[0], 0.0);
    EXPECT_DOUBLE_EQ(vec[1], 0.0);
    EXPECT_DOUBLE_EQ(vec[2], 0.0);
}

TEST(VectorTest, ArrayConstructor)
{
    std::array values = {1.0, 2.0, 3.0};
    Vector vec(values);

    EXPECT_DOUBLE_EQ(vec[0], 1.0);
    EXPECT_DOUBLE_EQ(vec[1], 2.0);
    EXPECT_DOUBLE_EQ(vec[2], 3.0);
}

TEST(VectorTest, ArrayConstructorWithFloat)
{
    Vector<2, float> vec({1.5F, 2.5F});

    EXPECT_FLOAT_EQ(vec[0], 1.5F);
    EXPECT_FLOAT_EQ(vec[1], 2.5F);
}

// ============================================================================
// Norm Tests
// ============================================================================

TEST(VectorTest, ComputeNormZeroVector)
{
    std::array values = {0.0, 0.0, 0.0};
    const Vector vec(values);

    EXPECT_DOUBLE_EQ(vec.length(), 0.0);
}

TEST(VectorTest, ComputeNormUnitVector)
{
    std::array values = {1.0, 0.0, 0.0};
    const Vector vec(values);

    EXPECT_DOUBLE_EQ(vec.length(), 1.0);
}

TEST(VectorTest, ComputeNorm3D)
{
    std::array values = {3.0, 4.0, 0.0};
    const Vector vec(values);

    EXPECT_DOUBLE_EQ(vec.length(), 5.0);
}

TEST(VectorTest, ComputeNormGeneral)
{
    std::array values = {1.0, 2.0, 2.0};
    const Vector vec(values);

    EXPECT_DOUBLE_EQ(vec.length(), 3.0);
}

// ============================================================================
// Normalize Tests
// ============================================================================

TEST(VectorTest, NormalizeVector)
{
    std::array values = {3.0F, 4.0F, 0.0F};
    const Vector vec(values);

    auto normalized = vec.normalize();

    EXPECT_NEAR(normalized[0], 0.6, 1e-7);
    EXPECT_NEAR(normalized[1], 0.8, 1e-7);
    EXPECT_NEAR(normalized[2], 0.0, 1e-7);
    EXPECT_NEAR(normalized.length(), 1.0, 1e-10);
}

TEST(VectorTest, NormalizeZeroVectorThrows)
{
    std::array values = {0.0, 0.0, 0.0};
    const Vector vec(values);
    // auto normal = vec.normalize();

    EXPECT_THROW((void)vec.normalize(), std::runtime_error);
}

// ============================================================================
// Operator Tests - Arithmetic
// ============================================================================

TEST(VectorTest, AdditionOperator)
{
    const Vector<3> vecA({1.0, 2.0, 3.0});
    const Vector<3> vecB({4.0, 5.0, 6.0});

    auto result = vecA + vecB;

    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(result[1], 7.0);
    EXPECT_DOUBLE_EQ(result[2], 9.0);
}

TEST(VectorTest, SubtractionOperator)
{
    const Vector<3> vecA({4.0, 5.0, 6.0});
    const Vector<3> vecB({1.0, 2.0, 3.0});

    auto result = vecA - vecB;

    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
    EXPECT_DOUBLE_EQ(result[2], 3.0);
}

TEST(VectorTest, DotProduct)
{
    const Vector<3> vecA({1.0, 2.0, 3.0});
    const Vector<3> vecB({4.0, 5.0, 6.0});

    const double result = vecA.dot(vecB);

    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(VectorTest, DotProductOrthogonalVectors)
{
    const Vector<3> vecA({1.0, 0.0, 0.0});
    const Vector<3> vecB({0.0, 1.0, 0.0});

    const double result = vecA * vecB;

    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(VectorTest, ScalarMultiplication)
{
    const Vector<3> vec({1.0, 2.0, 3.0});

    auto result = vec * 2.0;

    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
    EXPECT_DOUBLE_EQ(result[2], 6.0);
}

TEST(VectorTest, ScalarDivision)
{
    const Vector<3> vec({2.0, 4.0, 6.0});

    auto result = vec / 2.0;

    EXPECT_DOUBLE_EQ(result[0], 1.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(result[2], 3.0);
}

TEST(VectorTest, ScalarDivisionByZeroThrows)
{
    const Vector<3> vec({1.0, 2.0, 3.0});

    EXPECT_THROW(vec / 0.0, std::runtime_error);
}

TEST(VectorTest, NegationOperator)
{
    const Vector<3> vec({1.0, -2.0, 3.0});

    auto result = -vec;

    EXPECT_DOUBLE_EQ(result[0], -1.0);
    EXPECT_DOUBLE_EQ(result[1], 2.0);
    EXPECT_DOUBLE_EQ(result[2], -3.0);
}

// ============================================================================
// Operator Tests - Comparison
// ============================================================================

TEST(VectorTest, EqualityOperator)
{
    const Vector<3> vecA({1.0, 2.0, 3.0});
    const Vector<3> vecB({1.0, 2.0, 3.0});

    EXPECT_TRUE(vecA == vecB);
}

TEST(VectorTest, InequalityOperator)
{
    const Vector<3> vecA({1.0, 2.0, 3.0});
    const Vector<3> vecB({1.0, 2.0, 4.0});

    EXPECT_TRUE(vecA != vecB);
}

TEST(VectorTest, LessThanOperator)
{
    const Vector<3, double, true> vecA({1.0, 0.0, 0.0});
    const Vector<3, double, true> vecB({3.0, 4.0, 0.0});

    EXPECT_TRUE(vecA < vecB);
    EXPECT_FALSE(vecB < vecA);
}

TEST(VectorTest, LessThanOrEqualOperator)
{
    const Vector<3, double, true> vecA({1.0, 0.0, 0.0});
    const Vector<3, double, true> vecB({3.0, 4.0, 0.0});

    EXPECT_TRUE(vecA < vecB);
    EXPECT_FALSE(vecB < vecA);

    const Vector<3, double, true> vecC({3.0, 4.0, 0.0});
    const Vector<3, double, true> vecD({3.0, 4.0, 0.0});

    EXPECT_TRUE(vecC <= vecD);
}

TEST(VectorTest, GreaterThanOperator)
{
    const Vector<3, double, true> vecA({3.0, 4.0, 0.0});
    const Vector<3, double, true> vecB({1.0, 0.0, 0.0});

    EXPECT_TRUE(vecA > vecB);
    EXPECT_FALSE(vecB > vecA);
}

TEST(VectorTest, GreaterThanOrEqualOperator)
{
    const Vector<3, double, true> vecA({3.0, 4.0, 0.0});
    const Vector<3, double, true> vecB({3.0, 4.0, 0.0});

    EXPECT_TRUE(vecA >= vecB);
}

// ============================================================================
// Index Operator Tests
// ============================================================================

TEST(VectorTest, IndexOperatorRead)
{
    Vector<3> vec({1.0, 2.0, 3.0});

    EXPECT_DOUBLE_EQ(vec[0], 1.0);
    EXPECT_DOUBLE_EQ(vec[1], 2.0);
    EXPECT_DOUBLE_EQ(vec[2], 3.0);
}

TEST(VectorTest, IndexOperatorWrite)
{
    Vector<3> vec({1.0, 2.0, 3.0});

    vec[0] = 10.0;
    EXPECT_DOUBLE_EQ(vec[0], 10.0);
}

TEST(VectorTest, ConstIndexOperator)
{
    const Vector<3> vec({1.0, 2.0, 3.0});

    EXPECT_DOUBLE_EQ(vec[0], 1.0);
}

// ============================================================================
// Iterator Tests
// ============================================================================

TEST(VectorTest, BeginEndIterator)
{
    Vector<3> vec({1.0, 2.0, 3.0});

    auto sum = 0.0;
    for (const double &itt: vec)
        sum += itt;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(VectorTest, ConstBeginEndIterator)
{
    const Vector<3> vec({1.0, 2.0, 3.0});

    auto sum = 0.0;
    for (const double itt : vec)
        sum += itt;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(VectorTest, CBeginCEndIterator)
{
    const Vector<3> vec({1.0, 2.0, 3.0});

    auto sum = 0.0;
    for (const double &itt : vec)
        sum += itt;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(VectorTest, RangeBasedFor)
{
    const Vector<3> vec({1.0, 2.0, 3.0});

    auto sum = 0.0;
    for (const auto& val : vec)
        sum += val;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

// ============================================================================
// Cross Product Tests
// ============================================================================

TEST(VectorTest, CrossProductBasic)
{
    const Vector<3> vecA({1.0, 0.0, 0.0});
    const Vector<3> vecB({0.0, 1.0, 0.0});

    auto result = cross(vecA, vecB);

    EXPECT_DOUBLE_EQ(result[0], 0.0);
    EXPECT_DOUBLE_EQ(result[1], 0.0);
    EXPECT_DOUBLE_EQ(result[2], 1.0);
}

TEST(VectorTest, CrossProductGeneral)
{
    const Vector<3> vecA({1.0, 2.0, 3.0});
    const Vector<3> vecB({4.0, 5.0, 6.0});

    auto result = cross(vecA, vecB);

    // (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (12-15, 12-6, 5-8) = (-3, 6, -3)
    EXPECT_DOUBLE_EQ(result[0], -3.0);
    EXPECT_DOUBLE_EQ(result[1], 6.0);
    EXPECT_DOUBLE_EQ(result[2], -3.0);
}

TEST(VectorTest, CrossProductAnticommutative)
{
    const Vector<3> vecA({1.0, 2.0, 3.0});
    const Vector<3> vecB({4.0, 5.0, 6.0});

    auto resultAB = cross(vecA, vecB);
    auto resultBA = cross(vecB, vecA);

    EXPECT_DOUBLE_EQ(resultAB[0], -resultBA[0]);
    EXPECT_DOUBLE_EQ(resultAB[1], -resultBA[1]);
    EXPECT_DOUBLE_EQ(resultAB[2], -resultBA[2]);
}

// ============================================================================
// Type Alias Tests
// ============================================================================

TEST(VectorTest, Vector2fAlias)
{
    Vector2f vec({1.0F, 2.0F});

    EXPECT_FLOAT_EQ(vec[0], 1.0F);
    EXPECT_FLOAT_EQ(vec[1], 2.0F);
}

TEST(VectorTest, Vector3fAlias)
{
    Vector3f vec({1.0F, 2.0F, 3.0F});

    EXPECT_FLOAT_EQ(vec[0], 1.0F);
    EXPECT_FLOAT_EQ(vec[1], 2.0F);
    EXPECT_FLOAT_EQ(vec[2], 3.0F);
}

TEST(VectorTest, UnitVector2Alias)
{
    const UnitVector2 vec({1.0, 0.0});

    EXPECT_DOUBLE_EQ(vec.length(), 1.0);
}

TEST(VectorTest, UnitVector3Alias)
{
    const UnitVector3 vec({1.0, 0.0, 0.0});

    EXPECT_DOUBLE_EQ(vec.length(), 1.0);
}

// ============================================================================
// 2D Vector Tests
// ============================================================================

TEST(VectorTest, Vector2DOperations)
{
    const Vector<2> vecA({3.0, 4.0});
    const Vector<2> vecB({1.0, 2.0});

    auto sum = vecA + vecB;
    EXPECT_DOUBLE_EQ(sum[0], 4.0);
    EXPECT_DOUBLE_EQ(sum[1], 6.0);

    EXPECT_DOUBLE_EQ(vecA.length(), 5.0);
}
