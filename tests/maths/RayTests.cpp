/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** raytracer::maths::Ray class unit tests
*/

#include "Ray.hpp"

#include <cmath>
#include <gtest/gtest.h>

// ============================================================================
// Helper function to create test data
// ============================================================================

namespace {
    raytracer::maths::Point3d makeOrigin(double x, double y, double z)
    {
        return raytracer::maths::Point3d(x, y, z);
    }

    raytracer::maths::Vector3d makeDirection(double x, double y, double z)
    {
        return raytracer::maths::Vector3d(x, y, z);
    }
}

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(RayTest, ConstructorBasic)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);

    EXPECT_DOUBLE_EQ(ray.origin.x(), 0.0);
    EXPECT_DOUBLE_EQ(ray.origin.y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.origin.z(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction.x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.direction.y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction.z(), 0.0);
}

TEST(RayTest, ConstructorWithNonZeroOrigin)
{
    const raytracer::maths::Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d direction = makeDirection(0.0, 1.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);

    EXPECT_DOUBLE_EQ(ray.origin.x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.origin.y(), 2.0);
    EXPECT_DOUBLE_EQ(ray.origin.z(), 3.0);
}

TEST(RayTest, ConstructorNormalizesDirection)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 1.0, 1.0);

    const raytracer::maths::Ray ray(origin, direction);

    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(ray.direction.x(), invSqrt3);
    EXPECT_DOUBLE_EQ(ray.direction.y(), invSqrt3);
    EXPECT_DOUBLE_EQ(ray.direction.z(), invSqrt3);
}

TEST(RayTest, ConstructorNormalizesNonUnitDirection)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(3.0, 4.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);

    // (3, 4, 0) normalized = (0.6, 0.8, 0)
    EXPECT_DOUBLE_EQ(ray.direction.x(), 0.6);
    EXPECT_DOUBLE_EQ(ray.direction.y(), 0.8);
    EXPECT_DOUBLE_EQ(ray.direction.z(), 0.0);
}

// ============================================================================
// Origin and Direction Access Tests
// ============================================================================

TEST(RayTest, OriginAccess)
{
    const raytracer::maths::Point3d origin = makeOrigin(5.0, -3.0, 7.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    const raytracer::maths::Point3d& retrievedOrigin = ray.origin;

    EXPECT_DOUBLE_EQ(retrievedOrigin.x(), 5.0);
    EXPECT_DOUBLE_EQ(retrievedOrigin.y(), -3.0);
    EXPECT_DOUBLE_EQ(retrievedOrigin.z(), 7.0);
}

TEST(RayTest, OriginIsReference)
{
    const raytracer::maths::Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    const raytracer::maths::Point3d& ref1 = ray.origin;
    const raytracer::maths::Point3d& ref2 = ray.origin;

    // Both references should point to the same object
    EXPECT_EQ(&ref1, &ref2);
}

// ============================================================================
// Direction Access Tests
// ============================================================================

TEST(RayTest, DirectionAccess)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(0.0, 0.0, 1.0);

    const raytracer::maths::Ray ray(origin, direction);
    const raytracer::maths::Vector3d& retrievedDirection = ray.direction;

    EXPECT_DOUBLE_EQ(retrievedDirection.x(), 0.0);
    EXPECT_DOUBLE_EQ(retrievedDirection.y(), 0.0);
    EXPECT_DOUBLE_EQ(retrievedDirection.z(), 1.0);
}

TEST(RayTest, DirectionIsReference)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    const raytracer::maths::Vector3d& ref1 = ray.direction;
    const raytracer::maths::Vector3d& ref2 = ray.direction;

    // Both references should point to the same object
    EXPECT_EQ(&ref1, &ref2);
}

TEST(RayTest, DirectionIsNormalized)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(5.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    const raytracer::maths::Vector3d& dir = ray.direction;

    // Direction should be normalized to unit length
    double length = std::sqrt(dir.x() * dir.x() + dir.y() * dir.y() + dir.z() * dir.z());
    EXPECT_NEAR(length, 1.0, 1e-10);
}

// ============================================================================
// At (Parametric Point on raytracer::maths::Ray) Tests
// ============================================================================

TEST(RayTest, ParametricZeroReturnsOrigin)
{
    const raytracer::maths::Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(0.0);

    EXPECT_DOUBLE_EQ(point.x(), 1.0);
    EXPECT_DOUBLE_EQ(point.y(), 2.0);
    EXPECT_DOUBLE_EQ(point.z(), 3.0);
}

TEST(RayTest, ParametricPositiveT)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(5.0);

    EXPECT_DOUBLE_EQ(point.x(), 5.0);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), 0.0);
}

TEST(RayTest, ParametricNegativeT)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(-3.0);

    // Negative t goes in opposite direction
    EXPECT_DOUBLE_EQ(point.x(), -3.0);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), 0.0);
}

TEST(RayTest, ParametricWithNonZeroOrigin)
{
    const raytracer::maths::Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(2.0);

    // origin + 2 * direction = (1, 2, 3) + 2 * (1, 0, 0) = (3, 2, 3)
    EXPECT_DOUBLE_EQ(point.x(), 3.0);
    EXPECT_DOUBLE_EQ(point.y(), 2.0);
    EXPECT_DOUBLE_EQ(point.z(), 3.0);
}

TEST(RayTest, ParametricWithDiagonalDirection)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 1.0, 1.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(2.0);

    // Direction is normalized: (1/sqrt(3), 1/sqrt(3), 1/sqrt(3))
    // origin + 2 * normalized_direction
    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(point.x(), 2.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point.y(), 2.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point.z(), 2.0 * invSqrt3);
}

TEST(RayTest, ParametricWithFractionalT)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(2.0, 4.0, 6.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(0.5);

    // Direction is normalized: (2, 4, 6) / sqrt(4+16+36) = (2, 4, 6) / sqrt(56)
    const double norm = std::sqrt(56.0);
    EXPECT_DOUBLE_EQ(point.x(), 0.5 * (2.0 / norm));
    EXPECT_DOUBLE_EQ(point.y(), 0.5 * (4.0 / norm));
    EXPECT_DOUBLE_EQ(point.z(), 0.5 * (6.0 / norm));
}

TEST(RayTest, ParametricWithNegativeDirection)
{
    const raytracer::maths::Point3d origin = makeOrigin(5.0, 5.0, 5.0);
    const raytracer::maths::Vector3d direction = makeDirection(-1.0, -1.0, -1.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(3.0);

    // Direction normalized: (-1/sqrt(3), -1/sqrt(3), -1/sqrt(3))
    // origin + 3 * normalized_direction
    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(point.x(), 5.0 - 3.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point.y(), 5.0 - 3.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point.z(), 5.0 - 3.0 * invSqrt3);
}

TEST(RayTest, ParametricWithNonZeroOriginAndDiagonalDirection)
{
    const raytracer::maths::Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 1.0, 1.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(std::sqrt(3.0));

    // t = sqrt(3) means we move 1 unit along each axis (since direction is normalized)
    // origin + sqrt(3) * (1/sqrt(3), 1/sqrt(3), 1/sqrt(3)) = (1, 2, 3) + (1, 1, 1) = (2, 3, 4)
    EXPECT_NEAR(point.x(), 2.0, 1e-10);
    EXPECT_NEAR(point.y(), 3.0, 1e-10);
    EXPECT_NEAR(point.z(), 4.0, 1e-10);
}

// ============================================================================
// raytracer::maths::Ray Practical Scenarios
// ============================================================================

TEST(RayTest, RayAlongXAxis)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);

    // Check multiple points along the ray
    for (auto t = 0.0; t <= 10.0; t += 1.0) {
        raytracer::maths::Point3d point = ray(t);
        EXPECT_DOUBLE_EQ(point.x(), t);
        EXPECT_DOUBLE_EQ(point.y(), 0.0);
        EXPECT_DOUBLE_EQ(point.z(), 0.0);
    }
}

TEST(RayTest, RayAlongYAxis)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(0.0, 1.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);

    raytracer::maths::Point3d point = ray(7.5);
    EXPECT_DOUBLE_EQ(point.x(), 0.0);
    EXPECT_DOUBLE_EQ(point.y(), 7.5);
    EXPECT_DOUBLE_EQ(point.z(), 0.0);
}

TEST(RayTest, RayAlongZAxis)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(0.0, 0.0, 1.0);

    const raytracer::maths::Ray ray(origin, direction);

    raytracer::maths::Point3d point = ray(4.2);
    EXPECT_DOUBLE_EQ(point.x(), 0.0);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), 4.2);
}

TEST(RayTest, RayFromCameraScenario)
{
    // Simulating a ray from camera origin through a pixel
    const raytracer::maths::Point3d cameraOrigin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d pixelDirection = makeDirection(0.5, 0.5, -1.0);

    const raytracer::maths::Ray ray(cameraOrigin, pixelDirection);

    // Direction is normalized: (0.5, 0.5, -1) / sqrt(0.25 + 0.25 + 1) = (0.5, 0.5, -1) / sqrt(1.5)
    const double norm = std::sqrt(1.5);
    const double dirX = 0.5 / norm;
    const double dirY = 0.5 / norm;
    const double dirZ = -1.0 / norm;

    raytracer::maths::Point3d nearPoint = ray(1.0);
    EXPECT_DOUBLE_EQ(nearPoint.x(), dirX);
    EXPECT_DOUBLE_EQ(nearPoint.y(), dirY);
    EXPECT_DOUBLE_EQ(nearPoint.z(), dirZ);

    raytracer::maths::Point3d farPoint = ray(100.0);
    EXPECT_DOUBLE_EQ(farPoint.x(), 100.0 * dirX);
    EXPECT_DOUBLE_EQ(farPoint.y(), 100.0 * dirY);
    EXPECT_DOUBLE_EQ(farPoint.z(), 100.0 * dirZ);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(RayTest, ParametricWithVeryLargeT)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(1e10);

    EXPECT_DOUBLE_EQ(point.x(), 1e10);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), 0.0);
}

TEST(RayTest, ParametricWithVerySmallT)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(1e-10);

    EXPECT_NEAR(point.x(), 1e-10, 1e-20);
    EXPECT_DOUBLE_EQ(point.y(), 0.0);
    EXPECT_DOUBLE_EQ(point.z(), 0.0);
}

TEST(RayTest, RayWithLargeOriginCoordinates)
{
    const raytracer::maths::Point3d origin = makeOrigin(1e6, 1e6, 1e6);
    const raytracer::maths::Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);
    raytracer::maths::Point3d point = ray(100.0);

    EXPECT_DOUBLE_EQ(point.x(), 1e6 + 100.0);
    EXPECT_DOUBLE_EQ(point.y(), 1e6);
    EXPECT_DOUBLE_EQ(point.z(), 1e6);
}

TEST(RayTest, DirectionRemainsNormalizedAfterConstruction)
{
    const raytracer::maths::Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const raytracer::maths::Vector3d direction = makeDirection(100.0, 0.0, 0.0);

    const raytracer::maths::Ray ray(origin, direction);

    // Even with a large input vector, direction should be normalized
    EXPECT_DOUBLE_EQ(ray.direction.x(), 1.0);
    EXPECT_DOUBLE_EQ(ray.direction.y(), 0.0);
    EXPECT_DOUBLE_EQ(ray.direction.z(), 0.0);
}