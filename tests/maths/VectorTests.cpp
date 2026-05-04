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

#include "Vector2.hpp"
#include "Vector3.hpp"

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(VectorTest, DefaultConstructor)
{
    raytracer::maths::Vector3d vec;
    SUCCEED();

    EXPECT_DOUBLE_EQ(vec.x(), 0.0);
    EXPECT_DOUBLE_EQ(vec.y(), 0.0);
    EXPECT_DOUBLE_EQ(vec.z(), 0.0);
}

TEST(VectorTest, ArrayConstructor)
{
    raytracer::maths::Vector3d vec(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(vec.x(), 1.0);
    EXPECT_DOUBLE_EQ(vec.y(), 2.0);
    EXPECT_DOUBLE_EQ(vec.z(), 3.0);
}

TEST(VectorTest, ArrayConstructorWithFloat)
{
    raytracer::maths::Vector2<float> vec(1.5F, 2.5F);

    EXPECT_FLOAT_EQ(vec.x(), 1.5F);
    EXPECT_FLOAT_EQ(vec.y(), 2.5F);
}

// ============================================================================
// Norm Tests
// ============================================================================

TEST(VectorTest, ComputeNormZeroVector)
{
    raytracer::maths::Vector3d vec(0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(vec.length(), 0.0);
}

TEST(VectorTest, ComputeNormUnitVector)
{
    raytracer::maths::Vector3d vec(1.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(vec.length(), 1.0);
}

TEST(VectorTest, ComputeNorm3D)
{
    raytracer::maths::Vector3d vec(3.0, 4.0, 0.0);

    EXPECT_DOUBLE_EQ(vec.length(), 5.0);
}

TEST(VectorTest, ComputeNormGeneral)
{
    raytracer::maths::Vector3d vec(1.0, 2.0, 2.0);

    EXPECT_DOUBLE_EQ(vec.length(), 3.0);
}

// ============================================================================
// Normalize Tests
// ============================================================================

TEST(VectorTest, NormalizeVector)
{
    raytracer::maths::Vector3<float> vec(3.0F, 4.0F, 0.0F);

    auto normalized = vec.normalize();

    EXPECT_NEAR(normalized.x(), 0.6, 1e-7);
    EXPECT_NEAR(normalized.y(), 0.8, 1e-7);
    EXPECT_NEAR(normalized.z(), 0.0, 1e-7);
    EXPECT_NEAR(normalized.length(), 1.0, 1e-10);
}

TEST(VectorTest, NormalizeZeroVectorThrows)
{
    raytracer::maths::Vector3d vec(0.0, 0.0, 0.0);
    // auto normal = vec.normalize();

    EXPECT_THROW((void)vec.normalize(), std::runtime_error);
}

// ============================================================================
// Operator Tests - Arithmetic
// ============================================================================

TEST(VectorTest, AdditionOperator)
{
    const raytracer::maths::Vector3d vecA(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d vecB(4.0, 5.0, 6.0);

    auto result = vecA + vecB;

    EXPECT_DOUBLE_EQ(result.x(), 5.0);
    EXPECT_DOUBLE_EQ(result.y(), 7.0);
    EXPECT_DOUBLE_EQ(result.z(), 9.0);
}

TEST(VectorTest, SubtractionOperator)
{
    const raytracer::maths::Vector3d vecA(4.0, 5.0, 6.0);
    const raytracer::maths::Vector3d vecB(1.0, 2.0, 3.0);

    auto result = vecA - vecB;

    EXPECT_DOUBLE_EQ(result.x(), 3.0);
    EXPECT_DOUBLE_EQ(result.y(), 3.0);
    EXPECT_DOUBLE_EQ(result.z(), 3.0);
}

TEST(VectorTest, DotProduct)
{
    const raytracer::maths::Vector3d vecA(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d vecB(4.0, 5.0, 6.0);

    const double result = vecA.dot(vecB);

    // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    EXPECT_DOUBLE_EQ(result, 32.0);
}

TEST(VectorTest, DotProductOrthogonalVectors)
{
    const raytracer::maths::Vector3d vecA(1.0, 0.0, 0.0);
    const raytracer::maths::Vector3d vecB(0.0, 1.0, 0.0);

    const double result = vecA * vecB;

    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(VectorTest, ScalarMultiplication)
{
    const raytracer::maths::Vector3d vec(1.0, 2.0, 3.0);

    auto result = vec * 2.0;

    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), 4.0);
    EXPECT_DOUBLE_EQ(result.z(), 6.0);
}

TEST(VectorTest, ScalarDivision)
{
    const raytracer::maths::Vector3d vec(2.0, 4.0, 6.0);

    auto result = vec / 2.0;

    EXPECT_DOUBLE_EQ(result.x(), 1.0);
    EXPECT_DOUBLE_EQ(result.y(), 2.0);
    EXPECT_DOUBLE_EQ(result.z(), 3.0);
}

TEST(VectorTest, ScalarDivisionByZeroThrows)
{
    const raytracer::maths::Vector3d vec(1.0, 2.0, 3.0);

    EXPECT_THROW(vec / 0.0, std::runtime_error);
}

TEST(VectorTest, NegationOperator)
{
    const raytracer::maths::Vector3d vec(1.0, -2.0, 3.0);

    auto result = -vec;

    EXPECT_DOUBLE_EQ(result.x(), -1.0);
    EXPECT_DOUBLE_EQ(result.y(), 2.0);
    EXPECT_DOUBLE_EQ(result.z(), -3.0);
}

// ============================================================================
// Operator Tests - Comparison
// ============================================================================

TEST(VectorTest, EqualityOperator)
{
    const raytracer::maths::Vector3d vecA(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d vecB(1.0, 2.0, 3.0);

    EXPECT_TRUE(vecA == vecB);
}

TEST(VectorTest, InequalityOperator)
{
    const raytracer::maths::Vector3d vecA(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d vecB(1.0, 2.0, 4.0);

    EXPECT_TRUE(vecA != vecB);
}

TEST(VectorTest, LessThanOperator)
{
    const raytracer::maths::Vector3d vecA(1.0, 0.0, 0.0);
    const raytracer::maths::Vector3d vecB(3.0, 4.0, 0.0);

    EXPECT_TRUE(vecA < vecB);
    EXPECT_FALSE(vecB < vecA);
}

TEST(VectorTest, LessThanOrEqualOperator)
{
    const raytracer::maths::Vector3d vecA(1.0, 0.0, 0.0);
    const raytracer::maths::Vector3d vecB(3.0, 4.0, 0.0);

    EXPECT_TRUE(vecA < vecB);
    EXPECT_FALSE(vecB < vecA);

    const raytracer::maths::Vector3d vecC(3.0, 4.0, 0.0);
    const raytracer::maths::Vector3d vecD(3.0, 4.0, 0.0);

    EXPECT_TRUE(vecC <= vecD);
}

TEST(VectorTest, GreaterThanOperator)
{
    const raytracer::maths::Vector3d vecA(3.0, 4.0, 0.0);
    const raytracer::maths::Vector3d vecB(1.0, 0.0, 0.0);

    EXPECT_TRUE(vecA > vecB);
    EXPECT_FALSE(vecB > vecA);
}

TEST(VectorTest, GreaterThanOrEqualOperator)
{
    const raytracer::maths::Vector3d vecA(3.0, 4.0, 0.0);
    const raytracer::maths::Vector3d vecB(3.0, 4.0, 0.0);

    EXPECT_TRUE(vecA >= vecB);
}

// ============================================================================
// Index Operator Tests
// ============================================================================

TEST(VectorTest, IndexOperatorRead)
{
    raytracer::maths::Vector3d vec(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(vec.x(), 1.0);
    EXPECT_DOUBLE_EQ(vec.y(), 2.0);
    EXPECT_DOUBLE_EQ(vec.z(), 3.0);
}

TEST(VectorTest, IndexOperatorWrite)
{
    raytracer::maths::Vector3d vec(1.0, 2.0, 3.0);

    vec.x() = 10.0;
    EXPECT_DOUBLE_EQ(vec.x(), 10.0);
}

TEST(VectorTest, ConstIndexOperator)
{
    const raytracer::maths::Vector3d vec(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(vec.x(), 1.0);
}

// ============================================================================
// Cross Product Tests
// ============================================================================

TEST(VectorTest, CrossProductBasic)
{
    const raytracer::maths::Vector3d vecA(1.0, 0.0, 0.0);
    const raytracer::maths::Vector3d vecB(0.0, 1.0, 0.0);

    auto result = vecA.cross(vecB);

    EXPECT_DOUBLE_EQ(result.x(), 0.0);
    EXPECT_DOUBLE_EQ(result.y(), 0.0);
    EXPECT_DOUBLE_EQ(result.z(), 1.0);
}

TEST(VectorTest, CrossProductGeneral)
{
    const raytracer::maths::Vector3d vecA(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d vecB(4.0, 5.0, 6.0);

    auto result = vecA.cross(vecB);

    // (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4) = (12-15, 12-6, 5-8) = (-3, 6, -3)
    EXPECT_DOUBLE_EQ(result.x(), -3.0);
    EXPECT_DOUBLE_EQ(result.y(), 6.0);
    EXPECT_DOUBLE_EQ(result.z(), -3.0);
}

TEST(VectorTest, CrossProductAnticommutative)
{
    const raytracer::maths::Vector3d vecA(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d vecB(4.0, 5.0, 6.0);

    auto resultAB = vecA.cross(vecB);
    auto resultBA = vecB.cross(vecA);

    EXPECT_DOUBLE_EQ(resultAB.x(), -resultBA.x());
    EXPECT_DOUBLE_EQ(resultAB.y(), -resultBA.y());
    EXPECT_DOUBLE_EQ(resultAB.z(), -resultBA.z());
}

// ============================================================================
// Type Alias Tests
// ============================================================================

TEST(VectorTest, Vector2fAlias)
{
    raytracer::maths::Vector2<float> vec(1.0F, 2.0F);

    EXPECT_FLOAT_EQ(vec.x(), 1.0F);
    EXPECT_FLOAT_EQ(vec.y(), 2.0F);
}

TEST(VectorTest, Vector3fAlias)
{
    raytracer::maths::Vector3<float> vec(1.0F, 2.0F, 3.0F);

    EXPECT_FLOAT_EQ(vec.x(), 1.0F);
    EXPECT_FLOAT_EQ(vec.y(), 2.0F);
    EXPECT_FLOAT_EQ(vec.z(), 3.0F);
}

// ============================================================================
// 2D Vector Tests
// ============================================================================

TEST(VectorTest, Vector2DOperations)
{
    const raytracer::maths::Vector2d vecA(3.0, 4.0);
    const raytracer::maths::Vector2d vecB(1.0, 2.0);

    auto sum = vecA + vecB;
    EXPECT_DOUBLE_EQ(sum.x(), 4.0);
    EXPECT_DOUBLE_EQ(sum.y(), 6.0);

    EXPECT_DOUBLE_EQ(vecA.length(), 5.0);
}
