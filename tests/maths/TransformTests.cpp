/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Transform unit tests
*/

#include <gtest/gtest.h>

#include "Bounds3.hpp"
#include "Matrix4x4.hpp"
#include "Transform.hpp"

namespace {

using Matrix4x4d = raytracer::maths::Matrix4x4<double>;
using Transformd = raytracer::maths::Transform<double>;
using raytracer::maths::Normal3d;
using raytracer::maths::Vector3d;
using Bounds3d = raytracer::maths::Bounds3<double>;

constexpr double kEps = 1e-5;
constexpr double kPi  = 3.14159265358979323846;

Matrix4x4d identityMatrix()
{
    return {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

Matrix4x4d translationMatrix(double x, double y, double z)
{
    return {{{1, 0, 0, x}, {0, 1, 0, y}, {0, 0, 1, z}, {0, 0, 0, 1}}};
}

Matrix4x4d scaleMatrix(double x, double y, double z)
{
    return {{{x, 0, 0, 0}, {0, y, 0, 0}, {0, 0, z, 0}, {0, 0, 0, 1}}};
}

Matrix4x4d rotationZMatrix(double degrees)
{
    double radians = degrees * kPi / 180.0;
    double c       = std::cos(radians);
    double s       = std::sin(radians);
    return {{{c, -s, 0, 0}, {s, c, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

Matrix4x4d rotationY180Matrix()
{
    return {{{-1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 0}, {0, 0, 0, 1}}};
}

Matrix4x4d inverseTranslationMatrix(double x, double y, double z)
{
    return translationMatrix(-x, -y, -z);
}

Matrix4x4d inverseScaleMatrix(double x, double y, double z)
{
    return scaleMatrix(1.0 / x, 1.0 / y, 1.0 / z);
}

template <typename T>
void expect_point_near(const raytracer::maths::Point3<T> &actual,
    const raytracer::maths::Point3<T> &expected, double eps = kEps)
{
    EXPECT_NEAR(actual.x(), expected.x(), eps);
    EXPECT_NEAR(actual.y(), expected.y(), eps);
    EXPECT_NEAR(actual.z(), expected.z(), eps);
}

template <typename T>
void expect_vector_near(const raytracer::maths::Vector3<T> &actual,
    const raytracer::maths::Vector3<T> &expected, double eps = kEps)
{
    EXPECT_NEAR(actual.x(), expected.x(), eps);
    EXPECT_NEAR(actual.y(), expected.y(), eps);
    EXPECT_NEAR(actual.z(), expected.z(), eps);
}

template <typename T>
void expect_normal_near(const raytracer::maths::Normal3<T> &actual,
    const raytracer::maths::Normal3<T> &expected, double eps = kEps)
{
    EXPECT_NEAR(actual.x(), expected.x(), eps);
    EXPECT_NEAR(actual.y(), expected.y(), eps);
    EXPECT_NEAR(actual.z(), expected.z(), eps);
}

void expect_matrix_near(
    const Matrix4x4d &actual, const Matrix4x4d &expected, double eps = kEps)
{
    for (std::size_t row = 0; row < 4; ++row) {
        for (std::size_t col = 0; col < 4; ++col)
            EXPECT_NEAR(actual[row][col], expected[row][col], eps);
    }
}

} // namespace

TEST(SquareMatrix4Test, DefaultConstructorProducesIdentity)
{
    Matrix4x4d matrix;

    EXPECT_TRUE(matrix.isIdentity());
    expect_matrix_near(matrix, identityMatrix());
}

TEST(SquareMatrix4Test, IdentityMultiplyKeepsMatrix)
{
    Matrix4x4d identity = identityMatrix();
    Matrix4x4d matrix{{{2, 3, 5, 7}, {11, 13, 17, 19}, {23, 29, 31, 37},
        {41, 43, 47, 53}}};

    expect_matrix_near(identity * matrix, matrix);
}

TEST(SquareMatrix4Test, TransposeOfIdentityIsIdentity)
{
    expect_matrix_near(raytracer::maths::Transpose(identityMatrix()),
        identityMatrix());
}

TEST(SquareMatrix4Test, InverseOfIdentityIsIdentity)
{
    expect_matrix_near(raytracer::maths::inverse(identityMatrix()),
        identityMatrix());
}

TEST(SquareMatrix4Test, InverseOfKnownMatrixProducesCorrectResult)
{
    Matrix4x4d matrix{{{4, 0, 0, 0}, {0, 5, 0, 0}, {0, 0, 10, 0}, {0, 0, 0, 2}}};
    Matrix4x4d expectedInverse{{{0.25, 0, 0, 0}, {0, 0.2, 0, 0},
        {0, 0, 0.1, 0}, {0, 0, 0, 0.5}}};

    expect_matrix_near(raytracer::maths::inverse(matrix), expectedInverse);
}

TEST(SquareMatrix4Test, InverseOfSingularMatrixThrows)
{
    Matrix4x4d singular{{{1, 2, 3, 4}, {2, 4, 6, 8}, {3, 6, 9, 12},
        {4, 8, 12, 16}}};

    EXPECT_THROW((void)raytracer::maths::inverse(singular), std::runtime_error);
}

TEST(TransformTest, DefaultConstructorIsIdentity)
{
    Transformd transform;

    EXPECT_TRUE(transform.isIdentity());
    expect_matrix_near(transform.getMatrix(), identityMatrix());
    expect_matrix_near(transform.getInverseMatrix(), identityMatrix());
}

TEST(TransformTest, InverseOfTranslationIsNegativeTranslation)
{
    Transformd translation(translationMatrix(1, 2, 3),
        inverseTranslationMatrix(1, 2, 3));
    Transformd expected(translationMatrix(-1, -2, -3),
        inverseTranslationMatrix(-1, -2, -3));

    expect_matrix_near(raytracer::maths::inverse(translation).getMatrix(),
        expected.getMatrix());
    expect_matrix_near(raytracer::maths::inverse(translation).getInverseMatrix(),
        expected.getInverseMatrix());
}

TEST(TransformTest, ExplicitInverseRoundTripRestoresPoint)
{
    Transformd transform(scaleMatrix(2, 3, 4), inverseScaleMatrix(2, 3, 4));
    Point3d point{1.25, -2.0, 0.5};

    expect_point_near(transform(raytracer::maths::inverse(transform)(point)),
        point);
}

TEST(TransformTest, PointTransformationAppliesTranslation)
{
    Transformd transform(translationMatrix(1, 0, 0),
        inverseTranslationMatrix(1, 0, 0));

    expect_point_near(transform(Point3d{0, 0, 0}), Point3d{1, 0, 0});
}

TEST(TransformTest, VectorTransformationIgnoresTranslation)
{
    Transformd transform(translationMatrix(1, 2, 3),
        inverseTranslationMatrix(1, 2, 3));

    expect_vector_near(transform(Vector3d{4, 5, 6}), Vector3d{4, 5, 6});
}

TEST(TransformTest, NormalTransformationPreservesPerpendicularity)
{
    Transformd transform(scaleMatrix(2, 3, 4), inverseScaleMatrix(2, 3, 4));
    Normal3d normal{1, 1, 0};
    Vector3d tangent{1, -1, 0};
    Normal3d tangentNormal{tangent};

    Normal3d transformedNormal = transform(normal);
    Vector3d transformedTangent = transform(tangent);
    Normal3d transformedTangentNormal{transformedTangent};

    EXPECT_NEAR(transformedNormal.dot(transformedTangentNormal), 0.0, kEps);
    EXPECT_NEAR(normal.dot(tangentNormal), 0.0, kEps);
    expect_normal_near(transformedNormal, Normal3d{0.5, 0.3333333333, 0});
}

TEST(TransformTest, RayTransformationKeepsTMax)
{
    Transformd transform(translationMatrix(1, 2, 3),
        inverseTranslationMatrix(1, 2, 3));
    raytracer::maths::Ray ray(Point3d{1, 2, 3}, Vector3d{4, 5, 6}, 7.5);

    auto transformed = transform(ray);

    expect_point_near(transformed.origin, Point3d{2, 4, 6});
    expect_vector_near(transformed.direction, Vector3d{4, 5, 6}.normalize());
    EXPECT_NEAR(transformed.tMax, 7.5, kEps);
}

TEST(TransformTest, BoundsTransformationProducesEnclosingAabb)
{
    Transformd transform(translationMatrix(1, 2, 3),
        inverseTranslationMatrix(1, 2, 3));
    Bounds3d bounds(Point3d{-1, -1, -1}, Point3d{1, 1, 1});

    Bounds3d transformed = transform(bounds);

    expect_point_near(transformed.pMin, Point3d{0, 1, 2});
    expect_point_near(transformed.pMax, Point3d{2, 3, 4});
}

TEST(TransformTest, SwapsHandednessForNegativeXScale)
{
    Transformd transform(scaleMatrix(-1, 1, 1), inverseScaleMatrix(-1, 1, 1));

    EXPECT_TRUE(transform.swapHandedness());
}

TEST(TransformTest, HasScaleDetectsNonUniformScale)
{
    Transformd scaleTransform(scaleMatrix(2, 1, 1), inverseScaleMatrix(2, 1, 1));
    Transformd rotationTransform(rotationZMatrix(90),
        raytracer::maths::Transpose(rotationZMatrix(90)));

    EXPECT_TRUE(scaleTransform.hasScale());
    EXPECT_FALSE(rotationTransform.hasScale());
}

TEST(TransformFactoryTest, ScaleAppliesToVector)
{
    Transformd transform(scaleMatrix(2, 2, 2), inverseScaleMatrix(2, 2, 2));

    expect_vector_near(transform(Vector3d{1, 0, 0}), Vector3d{2, 0, 0});
}

TEST(TransformFactoryTest, RotateZNinetyDegrees)
{
    Matrix4x4d rotation = rotationZMatrix(90);
    Transformd transform(rotation, raytracer::maths::Transpose(rotation));

    expect_vector_near(transform(Vector3d{1, 0, 0}), Vector3d{0, 1, 0});
}

TEST(TransformFactoryTest, RotateAroundYAxis180Degrees)
{
    Transformd transform(rotationY180Matrix(), rotationY180Matrix());

    expect_point_near(transform(Point3d{1, 0, 0}), Point3d{-1, 0, 0});
}

TEST(TransformFactoryTest, CompositionAppliesScaleThenTranslation)
{
    Transformd translate(translationMatrix(1, 0, 0),
        inverseTranslationMatrix(1, 0, 0));
    Transformd scale(scaleMatrix(2, 3, 4), inverseScaleMatrix(2, 3, 4));
    Transformd composed = translate * scale;

    expect_point_near(composed(Point3d{1, 1, 1}), Point3d{3, 3, 4});
}
