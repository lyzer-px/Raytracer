/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Point class unit tests
*/

#include "Point.hpp"

#include <gtest/gtest.h>

#include "Vector3.hpp"

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(PointTest, DefaultConstructor)
{
    [[maybe_unused]] Point3d point;
    SUCCEED();
}

TEST(PointTest, ArrayConstructor)
{
    Point3d point(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(point.x(), 1.0);
    EXPECT_DOUBLE_EQ(point.y(), 2.0);
    EXPECT_DOUBLE_EQ(point.z(), 3.0);
}

TEST(PointTest, ArrayConstructorWithFloat)
{
    Point2<float> point(1.5F, 2.5F);

    EXPECT_FLOAT_EQ(point.x(), 1.5F);
    EXPECT_FLOAT_EQ(point.y(), 2.5F);
}

TEST(PointTest, ArrayConstructor2D)
{
    Point2d point(5.0, 10.0);

    EXPECT_DOUBLE_EQ(point.x(), 5.0);
    EXPECT_DOUBLE_EQ(point.y(), 10.0);
}

// ============================================================================
// Index Operator Tests
// ============================================================================

TEST(PointTest, IndexOperatorRead)
{
    Point3d point(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(point.x(), 1.0);
    EXPECT_DOUBLE_EQ(point.y(), 2.0);
    EXPECT_DOUBLE_EQ(point.z(), 3.0);
}

TEST(PointTest, IndexOperatorWrite)
{
    Point3d point(1.0, 2.0, 3.0);

    point.x() = 10.0;
    point.y() = 20.0;
    point.z() = 30.0;

    EXPECT_DOUBLE_EQ(point.x(), 10.0);
    EXPECT_DOUBLE_EQ(point.y(), 20.0);
    EXPECT_DOUBLE_EQ(point.z(), 30.0);
}

TEST(PointTest, ConstIndexOperator)
{
    const Point3d point(1.0, 2.0, 3.0);

    EXPECT_DOUBLE_EQ(point.x(), 1.0);
    EXPECT_DOUBLE_EQ(point.y(), 2.0);
    EXPECT_DOUBLE_EQ(point.z(), 3.0);
}

// ============================================================================
// Comparison Operator Tests
// ============================================================================

TEST(PointTest, EqualityOperatorTrue)
{
    const Point3d pointA(1.0, 2.0, 3.0);
    const Point3d pointB(1.0, 2.0, 3.0);

    EXPECT_TRUE(pointA == pointB);
}

TEST(PointTest, EqualityOperatorFalse)
{
    const Point3d pointA(1.0, 2.0, 3.0);
    const Point3d pointB(1.0, 2.0, 4.0);

    EXPECT_FALSE(pointA == pointB);
}

TEST(PointTest, InequalityOperatorTrue)
{
    const Point3d pointA(1.0, 2.0, 3.0);
    const Point3d pointB(4.0, 5.0, 6.0);

    EXPECT_TRUE(pointA != pointB);
}

TEST(PointTest, InequalityOperatorFalse)
{
    const Point3d pointA(1.0, 2.0, 3.0);
    const Point3d pointB(1.0, 2.0, 3.0);

    EXPECT_FALSE(pointA != pointB);
}

// ============================================================================
// Point-Vector Arithmetic Tests
// ============================================================================

TEST(PointTest, PointPlusVector)
{
    const Point3d point(1.0, 2.0, 3.0);
    const Vector3d vec(1.0, 1.0, 1.0);

    const Point3d result = point + vec;

    EXPECT_DOUBLE_EQ(result.x(), 2.0);
    EXPECT_DOUBLE_EQ(result.y(), 3.0);
    EXPECT_DOUBLE_EQ(result.z(), 4.0);
}

TEST(PointTest, PointMinusVector)
{
    const Point3d point(5.0, 6.0, 7.0);
    const Vector3d vec(1.0, 2.0, 3.0);

    const Point3d result = point - vec;

    EXPECT_DOUBLE_EQ(result.x(), 4.0);
    EXPECT_DOUBLE_EQ(result.y(), 4.0);
    EXPECT_DOUBLE_EQ(result.z(), 4.0);
}

TEST(PointTest, PointMinusPoint)
{
    const Point3d pointA(5.0, 6.0, 7.0);
    const Point3d pointB(1.0, 2.0, 3.0);

    const Vector3d vec = pointA - pointB;

    EXPECT_DOUBLE_EQ(vec.x(), 4.0);
    EXPECT_DOUBLE_EQ(vec.y(), 4.0);
    EXPECT_DOUBLE_EQ(vec.z(), 4.0);
}

TEST(PointTest, PointPlusEqualsVector)
{
    Point3d point(1.0, 2.0, 3.0);
    const Vector3d vec(1.0, 1.0, 1.0);

    point += vec;

    EXPECT_DOUBLE_EQ(point.x(), 2.0);
    EXPECT_DOUBLE_EQ(point.y(), 3.0);
    EXPECT_DOUBLE_EQ(point.z(), 4.0);
}

TEST(PointTest, PointMinusEqualsVector)
{
    Point3d point(5.0, 6.0, 7.0);
    const Vector3d vec(1.0, 2.0, 3.0);

    point -= vec;

    EXPECT_DOUBLE_EQ(point.x(), 4.0);
    EXPECT_DOUBLE_EQ(point.y(), 4.0);
    EXPECT_DOUBLE_EQ(point.z(), 4.0);
}

// ============================================================================
// Type Alias Tests
// ============================================================================

TEST(PointTest, Point2fAlias)
{
    Point2f point(1.0F, 2.0F);

    EXPECT_FLOAT_EQ(point.x(), 1.0F);
    EXPECT_FLOAT_EQ(point.y(), 2.0F);
}

TEST(PointTest, Point3fAlias)
{
    Point3f point(1.0F, 2.0F, 3.0F);

    EXPECT_FLOAT_EQ(point.x(), 1.0F);
    EXPECT_FLOAT_EQ(point.y(), 2.0F);
    EXPECT_FLOAT_EQ(point.z(), 3.0F);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(PointTest, NegativeValues)
{
    Point3d point(-1.0, -2.0, -3.0);

    EXPECT_DOUBLE_EQ(point.x(), -1.0);
    EXPECT_DOUBLE_EQ(point.y(), -2.0);
    EXPECT_DOUBLE_EQ(point.z(), -3.0);
}

TEST(PointTest, LargeValues)
{
    Point3d point(1e10, 2e10, 3e10);

    EXPECT_DOUBLE_EQ(point.x(), 1e10);
    EXPECT_DOUBLE_EQ(point.y(), 2e10);
    EXPECT_DOUBLE_EQ(point.z(), 3e10);
}

TEST(PointTest, SmallValues)
{
    Point3d point(1e-10, 2e-10, 3e-10);

    EXPECT_DOUBLE_EQ(point.x(), 1e-10);
    EXPECT_DOUBLE_EQ(point.y(), 2e-10);
    EXPECT_DOUBLE_EQ(point.z(), 3e-10);
}
