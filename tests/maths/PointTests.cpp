/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Point class unit tests
*/

#include "Point.hpp"

#include <array>
#include <gtest/gtest.h>

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(PointTest, DefaultConstructor)
{
    [[maybe_unused]] Point<3> point;
    SUCCEED();
}

TEST(PointTest, ArrayConstructor)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    EXPECT_DOUBLE_EQ(point[0], 1.0);
    EXPECT_DOUBLE_EQ(point[1], 2.0);
    EXPECT_DOUBLE_EQ(point[2], 3.0);
}

TEST(PointTest, ArrayConstructorWithFloat)
{
    Point<2, float> point({1.5F, 2.5F});

    EXPECT_FLOAT_EQ(point[0], 1.5F);
    EXPECT_FLOAT_EQ(point[1], 2.5F);
}

TEST(PointTest, ArrayConstructor2D)
{
    constexpr std::array values = {5.0, 10.0};
    Point point(values);

    EXPECT_DOUBLE_EQ(point[0], 5.0);
    EXPECT_DOUBLE_EQ(point[1], 10.0);
}

// ============================================================================
// Index Operator Tests
// ============================================================================

TEST(PointTest, IndexOperatorRead)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    EXPECT_DOUBLE_EQ(point[0], 1.0);
    EXPECT_DOUBLE_EQ(point[1], 2.0);
    EXPECT_DOUBLE_EQ(point[2], 3.0);
}

TEST(PointTest, IndexOperatorWrite)
{
    std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    point[0] = 10.0;
    point[1] = 20.0;
    point[2] = 30.0;

    EXPECT_DOUBLE_EQ(point[0], 10.0);
    EXPECT_DOUBLE_EQ(point[1], 20.0);
    EXPECT_DOUBLE_EQ(point[2], 30.0);
}

TEST(PointTest, ConstIndexOperator)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    const Point point(values);

    EXPECT_DOUBLE_EQ(point[0], 1.0);
    EXPECT_DOUBLE_EQ(point[1], 2.0);
    EXPECT_DOUBLE_EQ(point[2], 3.0);
}

// ============================================================================
// Comparison Operator Tests
// ============================================================================

TEST(PointTest, EqualityOperatorTrue)
{
    constexpr std::array valuesA = {1.0, 2.0, 3.0};
    constexpr std::array valuesB = {1.0, 2.0, 3.0};
    const Point pointA(valuesA);
    const Point pointB(valuesB);

    EXPECT_TRUE(pointA == pointB);
}

TEST(PointTest, EqualityOperatorFalse)
{
    constexpr std::array valuesA = {1.0, 2.0, 3.0};
    constexpr std::array valuesB = {1.0, 2.0, 4.0};
    const Point pointA(valuesA);
    const Point pointB(valuesB);

    EXPECT_FALSE(pointA == pointB);
}

TEST(PointTest, InequalityOperatorTrue)
{
    constexpr std::array valuesA = {1.0, 2.0, 3.0};
    constexpr std::array valuesB = {4.0, 5.0, 6.0};
    const Point pointA(valuesA);
    const Point pointB(valuesB);

    EXPECT_TRUE(pointA != pointB);
}

TEST(PointTest, InequalityOperatorFalse)
{
    constexpr std::array valuesA = {1.0, 2.0, 3.0};
    constexpr std::array valuesB = {1.0, 2.0, 3.0};
    const Point pointA(valuesA);
    const Point pointB(valuesB);

    EXPECT_FALSE(pointA != pointB);
}

// ============================================================================
// Increment/Decrement Operator Tests
// ============================================================================

TEST(PointTest, IncrementOperator)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    ++point;

    EXPECT_DOUBLE_EQ(point[0], 2.0);
    EXPECT_DOUBLE_EQ(point[1], 3.0);
    EXPECT_DOUBLE_EQ(point[2], 4.0);
}

TEST(PointTest, IncrementOperatorReturnsTrue)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    EXPECT_TRUE(++point);
}

TEST(PointTest, DecrementOperator)
{
    constexpr std::array values = {5.0, 6.0, 7.0};
    Point point(values);

    --point;

    EXPECT_DOUBLE_EQ(point[0], 4.0);
    EXPECT_DOUBLE_EQ(point[1], 5.0);
    EXPECT_DOUBLE_EQ(point[2], 6.0);
}

TEST(PointTest, DecrementOperatorReturnsTrue)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    EXPECT_TRUE(--point);
}

TEST(PointTest, MultipleIncrements)
{
    constexpr std::array values = {0.0, 0.0, 0.0};
    Point point(values);

    ++point;
    ++point;
    ++point;

    EXPECT_DOUBLE_EQ(point[0], 3.0);
    EXPECT_DOUBLE_EQ(point[1], 3.0);
    EXPECT_DOUBLE_EQ(point[2], 3.0);
}

// ============================================================================
// toVector Tests
// ============================================================================

TEST(PointTest, ToVector)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    const Point point(values);

    auto vec = point.toVector();

    EXPECT_DOUBLE_EQ(vec[0], 1.0);
    EXPECT_DOUBLE_EQ(vec[1], 2.0);
    EXPECT_DOUBLE_EQ(vec[2], 3.0);
}

TEST(PointTest, ToVectorPreservesType)
{
    constexpr std::array values = {1.5F, 2.5F};
    const Point point(values);

    auto vec = point.toVector();

    EXPECT_FLOAT_EQ(vec[0], 1.5F);
    EXPECT_FLOAT_EQ(vec[1], 2.5F);
}

TEST(PointTest, ToVectorZeroPoint)
{
    constexpr std::array values = {0.0, 0.0, 0.0};
    const Point point(values);

    auto vec = point.toVector();

    EXPECT_DOUBLE_EQ(vec[0], 0.0);
    EXPECT_DOUBLE_EQ(vec[1], 0.0);
    EXPECT_DOUBLE_EQ(vec[2], 0.0);
}

// ============================================================================
// Iterator Tests
// ============================================================================

TEST(PointTest, BeginEndIterator)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    auto sum = 0.0;
    for (const double &itt: point)
        sum += itt;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(PointTest, ConstBeginEndIterator)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    const Point point(values);

    auto sum = 0.0;
    for (const double itt: point)
        sum += itt;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(PointTest, CBeginCEndIterator)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    const Point point(values);

    auto sum = 0.0;
    for (const double itt: point)
        sum += itt;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(PointTest, RangeBasedFor)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    auto sum = 0.0;
    for (const auto &val: point)
        sum += val;

    EXPECT_DOUBLE_EQ(sum, 6.0);
}

TEST(PointTest, IteratorModification)
{
    constexpr std::array values = {1.0, 2.0, 3.0};
    Point point(values);

    for (auto &val: point) {
        val *= 2.0;
    }

    EXPECT_DOUBLE_EQ(point[0], 2.0);
    EXPECT_DOUBLE_EQ(point[1], 4.0);
    EXPECT_DOUBLE_EQ(point[2], 6.0);
}

// ============================================================================
// Type Alias Tests
// ============================================================================

TEST(PointTest, Point2fAlias)
{
    Point2f point({1.0F, 2.0F});

    EXPECT_FLOAT_EQ(point[0], 1.0F);
    EXPECT_FLOAT_EQ(point[1], 2.0F);
}

TEST(PointTest, Point3fAlias)
{
    Point3f point({1.0F, 2.0F, 3.0F});

    EXPECT_FLOAT_EQ(point[0], 1.0F);
    EXPECT_FLOAT_EQ(point[1], 2.0F);
    EXPECT_FLOAT_EQ(point[2], 3.0F);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(PointTest, NegativeValues)
{
    constexpr std::array values = {-1.0, -2.0, -3.0};
    Point point(values);

    EXPECT_DOUBLE_EQ(point[0], -1.0);
    EXPECT_DOUBLE_EQ(point[1], -2.0);
    EXPECT_DOUBLE_EQ(point[2], -3.0);
}

TEST(PointTest, LargeValues)
{
    constexpr std::array values = {1e10, 2e10, 3e10};
    Point point(values);

    EXPECT_DOUBLE_EQ(point[0], 1e10);
    EXPECT_DOUBLE_EQ(point[1], 2e10);
    EXPECT_DOUBLE_EQ(point[2], 3e10);
}

TEST(PointTest, SmallValues)
{
    constexpr std::array values = {1e-10, 2e-10, 3e-10};
    Point point(values);

    EXPECT_DOUBLE_EQ(point[0], 1e-10);
    EXPECT_DOUBLE_EQ(point[1], 2e-10);
    EXPECT_DOUBLE_EQ(point[2], 3e-10);
}
