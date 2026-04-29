/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Ray class unit tests
*/

#include "Ray.hpp"

#include <cmath>
#include <gtest/gtest.h>

// ============================================================================
// Helper function to create test data
// ============================================================================

namespace {
    Point3d makeOrigin(double x, double y, double z)
    {
        return Point3d(std::array{x, y, z});
    }

    Vector3d makeDirection(double x, double y, double z)
    {
        return Vector3d(std::array{x, y, z});
    }
}

// ============================================================================
// Constructor Tests
// ============================================================================

TEST(RayTest, ConstructorBasic)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);

    EXPECT_DOUBLE_EQ(ray.getOrigin()[0], 0.0);
    EXPECT_DOUBLE_EQ(ray.getOrigin()[1], 0.0);
    EXPECT_DOUBLE_EQ(ray.getOrigin()[2], 0.0);
    EXPECT_DOUBLE_EQ(ray.getDirection()[0], 1.0);
    EXPECT_DOUBLE_EQ(ray.getDirection()[1], 0.0);
    EXPECT_DOUBLE_EQ(ray.getDirection()[2], 0.0);
}

TEST(RayTest, ConstructorWithNonZeroOrigin)
{
    const Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const Vector3d direction = makeDirection(0.0, 1.0, 0.0);

    const Ray ray(origin, direction);

    EXPECT_DOUBLE_EQ(ray.getOrigin()[0], 1.0);
    EXPECT_DOUBLE_EQ(ray.getOrigin()[1], 2.0);
    EXPECT_DOUBLE_EQ(ray.getOrigin()[2], 3.0);
}

TEST(RayTest, ConstructorNormalizesDirection)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 1.0, 1.0);

    const Ray ray(origin, direction);

    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(ray.getDirection()[0], invSqrt3);
    EXPECT_DOUBLE_EQ(ray.getDirection()[1], invSqrt3);
    EXPECT_DOUBLE_EQ(ray.getDirection()[2], invSqrt3);
}

TEST(RayTest, ConstructorNormalizesNonUnitDirection)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(3.0, 4.0, 0.0);

    const Ray ray(origin, direction);

    // (3, 4, 0) normalized = (0.6, 0.8, 0)
    EXPECT_DOUBLE_EQ(ray.getDirection()[0], 0.6);
    EXPECT_DOUBLE_EQ(ray.getDirection()[1], 0.8);
    EXPECT_DOUBLE_EQ(ray.getDirection()[2], 0.0);
}

// ============================================================================
// GetOrigin Tests
// ============================================================================

TEST(RayTest, GetOriginReturnsCorrectValue)
{
    const Point3d origin = makeOrigin(5.0, -3.0, 7.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    const Point3d& retrievedOrigin = ray.getOrigin();

    EXPECT_DOUBLE_EQ(retrievedOrigin[0], 5.0);
    EXPECT_DOUBLE_EQ(retrievedOrigin[1], -3.0);
    EXPECT_DOUBLE_EQ(retrievedOrigin[2], 7.0);
}

TEST(RayTest, GetOriginReturnsReference)
{
    const Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    const Point3d& ref1 = ray.getOrigin();
    const Point3d& ref2 = ray.getOrigin();

    // Both references should point to the same object
    EXPECT_EQ(&ref1, &ref2);
}

// ============================================================================
// GetDirection Tests
// ============================================================================

TEST(RayTest, GetDirectionReturnsCorrectValue)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(0.0, 0.0, 1.0);

    const Ray ray(origin, direction);
    const UnitVector3& retrievedDirection = ray.getDirection();

    EXPECT_DOUBLE_EQ(retrievedDirection[0], 0.0);
    EXPECT_DOUBLE_EQ(retrievedDirection[1], 0.0);
    EXPECT_DOUBLE_EQ(retrievedDirection[2], 1.0);
}

TEST(RayTest, GetDirectionReturnsReference)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    const UnitVector3& ref1 = ray.getDirection();
    const UnitVector3& ref2 = ray.getDirection();

    // Both references should point to the same object
    EXPECT_EQ(&ref1, &ref2);
}

TEST(RayTest, GetDirectionIsNormalized)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(5.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    const UnitVector3& dir = ray.getDirection();

    // Direction should be normalized to unit length
    double length = std::sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]);
    EXPECT_NEAR(length, 1.0, 1e-10);
}

// ============================================================================
// At (Parametric Point on Ray) Tests
// ============================================================================

TEST(RayTest, AtZeroReturnsOrigin)
{
    const Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(0.0);

    EXPECT_DOUBLE_EQ(point[0], 1.0);
    EXPECT_DOUBLE_EQ(point[1], 2.0);
    EXPECT_DOUBLE_EQ(point[2], 3.0);
}

TEST(RayTest, AtPositiveT)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(5.0);

    EXPECT_DOUBLE_EQ(point[0], 5.0);
    EXPECT_DOUBLE_EQ(point[1], 0.0);
    EXPECT_DOUBLE_EQ(point[2], 0.0);
}

TEST(RayTest, AtNegativeT)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(-3.0);

    // Negative t goes in opposite direction
    EXPECT_DOUBLE_EQ(point[0], -3.0);
    EXPECT_DOUBLE_EQ(point[1], 0.0);
    EXPECT_DOUBLE_EQ(point[2], 0.0);
}

TEST(RayTest, AtWithNonZeroOrigin)
{
    const Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(2.0);

    // origin + 2 * direction = (1, 2, 3) + 2 * (1, 0, 0) = (3, 2, 3)
    EXPECT_DOUBLE_EQ(point[0], 3.0);
    EXPECT_DOUBLE_EQ(point[1], 2.0);
    EXPECT_DOUBLE_EQ(point[2], 3.0);
}

TEST(RayTest, AtWithDiagonalDirection)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 1.0, 1.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(2.0);

    // Direction is normalized: (1/sqrt(3), 1/sqrt(3), 1/sqrt(3))
    // origin + 2 * normalized_direction
    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(point[0], 2.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point[1], 2.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point[2], 2.0 * invSqrt3);
}

TEST(RayTest, AtWithFractionalT)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(2.0, 4.0, 6.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(0.5);

    // Direction is normalized: (2, 4, 6) / sqrt(4+16+36) = (2, 4, 6) / sqrt(56)
    const double norm = std::sqrt(56.0);
    EXPECT_DOUBLE_EQ(point[0], 0.5 * (2.0 / norm));
    EXPECT_DOUBLE_EQ(point[1], 0.5 * (4.0 / norm));
    EXPECT_DOUBLE_EQ(point[2], 0.5 * (6.0 / norm));
}

TEST(RayTest, AtWithNegativeDirection)
{
    const Point3d origin = makeOrigin(5.0, 5.0, 5.0);
    const Vector3d direction = makeDirection(-1.0, -1.0, -1.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(3.0);

    // Direction normalized: (-1/sqrt(3), -1/sqrt(3), -1/sqrt(3))
    // origin + 3 * normalized_direction
    const double invSqrt3 = 1.0 / std::sqrt(3.0);
    EXPECT_DOUBLE_EQ(point[0], 5.0 - 3.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point[1], 5.0 - 3.0 * invSqrt3);
    EXPECT_DOUBLE_EQ(point[2], 5.0 - 3.0 * invSqrt3);
}

TEST(RayTest, AtWithNonZeroOriginAndDiagonalDirection)
{
    const Point3d origin = makeOrigin(1.0, 2.0, 3.0);
    const Vector3d direction = makeDirection(1.0, 1.0, 1.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(std::sqrt(3.0));

    // t = sqrt(3) means we move 1 unit along each axis (since direction is normalized)
    // origin + sqrt(3) * (1/sqrt(3), 1/sqrt(3), 1/sqrt(3)) = (1, 2, 3) + (1, 1, 1) = (2, 3, 4)
    EXPECT_NEAR(point[0], 2.0, 1e-10);
    EXPECT_NEAR(point[1], 3.0, 1e-10);
    EXPECT_NEAR(point[2], 4.0, 1e-10);
}

// ============================================================================
// Ray Practical Scenarios
// ============================================================================

TEST(RayTest, RayAlongXAxis)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);

    // Check multiple points along the ray
    for (auto t = 0.0; t <= 10.0; t += 1.0) {
        Vector3d point = ray.at(t);
        EXPECT_DOUBLE_EQ(point[0], t);
        EXPECT_DOUBLE_EQ(point[1], 0.0);
        EXPECT_DOUBLE_EQ(point[2], 0.0);
    }
}

TEST(RayTest, RayAlongYAxis)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(0.0, 1.0, 0.0);

    const Ray ray(origin, direction);

    Vector3d point = ray.at(7.5);
    EXPECT_DOUBLE_EQ(point[0], 0.0);
    EXPECT_DOUBLE_EQ(point[1], 7.5);
    EXPECT_DOUBLE_EQ(point[2], 0.0);
}

TEST(RayTest, RayAlongZAxis)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(0.0, 0.0, 1.0);

    const Ray ray(origin, direction);

    Vector3d point = ray.at(4.2);
    EXPECT_DOUBLE_EQ(point[0], 0.0);
    EXPECT_DOUBLE_EQ(point[1], 0.0);
    EXPECT_DOUBLE_EQ(point[2], 4.2);
}

TEST(RayTest, RayFromCameraScenario)
{
    // Simulating a ray from camera origin through a pixel
    const Point3d cameraOrigin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d pixelDirection = makeDirection(0.5, 0.5, -1.0);

    const Ray ray(cameraOrigin, pixelDirection);

    // Direction is normalized: (0.5, 0.5, -1) / sqrt(0.25 + 0.25 + 1) = (0.5, 0.5, -1) / sqrt(1.5)
    const double norm = std::sqrt(1.5);
    const double dirX = 0.5 / norm;
    const double dirY = 0.5 / norm;
    const double dirZ = -1.0 / norm;

    Vector3d nearPoint = ray.at(1.0);
    EXPECT_DOUBLE_EQ(nearPoint[0], dirX);
    EXPECT_DOUBLE_EQ(nearPoint[1], dirY);
    EXPECT_DOUBLE_EQ(nearPoint[2], dirZ);

    Vector3d farPoint = ray.at(100.0);
    EXPECT_DOUBLE_EQ(farPoint[0], 100.0 * dirX);
    EXPECT_DOUBLE_EQ(farPoint[1], 100.0 * dirY);
    EXPECT_DOUBLE_EQ(farPoint[2], 100.0 * dirZ);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(RayTest, AtWithVeryLargeT)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(1e10);

    EXPECT_DOUBLE_EQ(point[0], 1e10);
    EXPECT_DOUBLE_EQ(point[1], 0.0);
    EXPECT_DOUBLE_EQ(point[2], 0.0);
}

TEST(RayTest, AtWithVerySmallT)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(1e-10);

    EXPECT_NEAR(point[0], 1e-10, 1e-20);
    EXPECT_DOUBLE_EQ(point[1], 0.0);
    EXPECT_DOUBLE_EQ(point[2], 0.0);
}

TEST(RayTest, RayWithLargeOriginCoordinates)
{
    const Point3d origin = makeOrigin(1e6, 1e6, 1e6);
    const Vector3d direction = makeDirection(1.0, 0.0, 0.0);

    const Ray ray(origin, direction);
    Vector3d point = ray.at(100.0);

    EXPECT_DOUBLE_EQ(point[0], 1e6 + 100.0);
    EXPECT_DOUBLE_EQ(point[1], 1e6);
    EXPECT_DOUBLE_EQ(point[2], 1e6);
}

TEST(RayTest, DirectionRemainsNormalizedAfterConstruction)
{
    const Point3d origin = makeOrigin(0.0, 0.0, 0.0);
    const Vector3d direction = makeDirection(100.0, 0.0, 0.0);

    const Ray ray(origin, direction);

    // Even with a large input vector, direction should be normalized
    EXPECT_DOUBLE_EQ(ray.getDirection()[0], 1.0);
    EXPECT_DOUBLE_EQ(ray.getDirection()[1], 0.0);
    EXPECT_DOUBLE_EQ(ray.getDirection()[2], 0.0);
}