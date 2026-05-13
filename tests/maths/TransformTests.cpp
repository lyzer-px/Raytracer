/*
** EPITECH PROJECT, 2026
** Raytracer
** File description:
** Transform unit tests
*/

#include <gtest/gtest.h>

#include <numbers>

#include "Bounds3.hpp"
#include "Matrix4x4.hpp"
#include "Transform.hpp"

using raytracer::maths::Bounds3;
using raytracer::maths::Normal3;
using raytracer::maths::Point3;
using raytracer::maths::Ray;
using raytracer::maths::Transform;
using raytracer::maths::Vector3;
using Mat = raytracer::maths::Matrix4x4<double>;

static constexpr double K_EPS     = 1e-9;
static constexpr double K_EPS_TRIG = 1e-9;

static void expectPointNear(
    const Point3<double> &p, double x, double y, double z, double eps = K_EPS)
{
    EXPECT_NEAR(p.x(), x, eps);
    EXPECT_NEAR(p.y(), y, eps);
    EXPECT_NEAR(p.z(), z, eps);
}

static void expectVecNear(
    const Vector3<double> &v, double x, double y, double z, double eps = K_EPS)
{
    EXPECT_NEAR(v.x(), x, eps);
    EXPECT_NEAR(v.y(), y, eps);
    EXPECT_NEAR(v.z(), z, eps);
}

// ── Constructors & accessors ──────────────────────────────────────────────────

TEST(TransformTest, DefaultConstructorIsIdentity)
{
    Transform t;
    EXPECT_TRUE(t.isIdentity());
    EXPECT_FALSE(t.hasScale());
    EXPECT_FALSE(t.swapHandedness());
}

TEST(TransformTest, ConstructFromMatrix)
{
    Mat m{{2.0, 0.0, 0.0, 0.0},
          {0.0, 2.0, 0.0, 0.0},
          {0.0, 0.0, 2.0, 0.0},
          {0.0, 0.0, 0.0, 1.0}};
    Transform t(m);
    EXPECT_EQ(t.getMatrix(), m);
}

TEST(TransformTest, ConstructFromMatrixAndInverse)
{
    Mat m{{1.0, 0.0, 0.0, 5.0},
          {0.0, 1.0, 0.0, 0.0},
          {0.0, 0.0, 1.0, 0.0},
          {0.0, 0.0, 0.0, 1.0}};
    Mat mInv{{1.0, 0.0, 0.0, -5.0},
             {0.0, 1.0, 0.0,  0.0},
             {0.0, 0.0, 1.0,  0.0},
             {0.0, 0.0, 0.0,  1.0}};
    Transform t(m, mInv);
    EXPECT_EQ(t.getMatrix(), m);
    EXPECT_EQ(t.getInverseMatrix(), mInv);
}

// ── Equality ──────────────────────────────────────────────────────────────────

TEST(TransformTest, EqualityDefaultTransforms)
{
    Transform a;
    Transform b;
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(TransformTest, InequalityDistinctTransforms)
{
    auto t = Transform::translate({1.0, 0.0, 0.0});
    Transform id;
    EXPECT_TRUE(t != id);
    EXPECT_FALSE(t == id);
}

// ── translate ─────────────────────────────────────────────────────────────────

TEST(TransformTest, TranslatePoint)
{
    auto t = Transform::translate({3.0, -1.0, 2.0});
    auto result = t(Point3<double>(1.0, 2.0, 3.0));
    expectPointNear(result, 4.0, 1.0, 5.0);
}

TEST(TransformTest, TranslateDoesNotAffectVectors)
{
    auto t = Transform::translate({3.0, -1.0, 2.0});
    auto result = t(Vector3<double>(1.0, 2.0, 3.0));
    expectVecNear(result, 1.0, 2.0, 3.0);
}

TEST(TransformTest, TranslateIsNotIdentity)
{
    auto t = Transform::translate({1.0, 0.0, 0.0});
    EXPECT_FALSE(t.isIdentity());
    EXPECT_FALSE(t.hasScale());
}

TEST(TransformTest, ZeroTranslateIsIdentity)
{
    auto t = Transform::translate({0.0, 0.0, 0.0});
    EXPECT_TRUE(t.isIdentity());
}

// ── scale ─────────────────────────────────────────────────────────────────────

TEST(TransformTest, ScalePoint)
{
    auto t = Transform::scale(2.0, 3.0, 4.0);
    auto result = t(Point3<double>(1.0, 1.0, 1.0));
    expectPointNear(result, 2.0, 3.0, 4.0);
}

TEST(TransformTest, ScaleVector)
{
    auto t = Transform::scale(2.0, 3.0, 4.0);
    auto result = t(Vector3<double>(1.0, 1.0, 1.0));
    expectVecNear(result, 2.0, 3.0, 4.0);
}

TEST(TransformTest, ScaleHasScale)
{
    auto t = Transform::scale(2.0, 3.0, 4.0);
    EXPECT_TRUE(t.hasScale());
}

TEST(TransformTest, UniformScaleOneIsIdentity)
{
    auto t = Transform::scale(1.0, 1.0, 1.0);
    EXPECT_TRUE(t.isIdentity());
    EXPECT_FALSE(t.hasScale());
}

TEST(TransformTest, NegativeScaleSwapsHandedness)
{
    auto t = Transform::scale(-1.0, 1.0, 1.0);
    EXPECT_TRUE(t.swapHandedness());
}

TEST(TransformTest, PositiveScaleDoesNotSwapHandedness)
{
    auto t = Transform::scale(2.0, 3.0, 4.0);
    EXPECT_FALSE(t.swapHandedness());
}

// ── rotateX ───────────────────────────────────────────────────────────────────

TEST(TransformTest, RotateX90DegreesMapsYToZ)
{
    auto t = Transform::rotateX(std::numbers::pi / 2.0);
    auto result = t(Vector3<double>(0.0, 1.0, 0.0));
    expectVecNear(result, 0.0, 0.0, 1.0, K_EPS_TRIG);
}

TEST(TransformTest, RotateX90DegreesMapsZToNegY)
{
    auto t = Transform::rotateX(std::numbers::pi / 2.0);
    auto result = t(Vector3<double>(0.0, 0.0, 1.0));
    expectVecNear(result, 0.0, -1.0, 0.0, K_EPS_TRIG);
}

TEST(TransformTest, RotateXDoesNotAffectX)
{
    auto t = Transform::rotateX(std::numbers::pi / 3.0);
    auto result = t(Vector3<double>(1.0, 0.0, 0.0));
    expectVecNear(result, 1.0, 0.0, 0.0, K_EPS_TRIG);
}

// ── rotateY ───────────────────────────────────────────────────────────────────

TEST(TransformTest, RotateY90DegreesMapsZToX)
{
    auto t = Transform::rotateY(std::numbers::pi / 2.0);
    auto result = t(Vector3<double>(0.0, 0.0, 1.0));
    expectVecNear(result, 1.0, 0.0, 0.0, K_EPS_TRIG);
}

TEST(TransformTest, RotateY90DegreesMapsXToNegZ)
{
    auto t = Transform::rotateY(std::numbers::pi / 2.0);
    auto result = t(Vector3<double>(1.0, 0.0, 0.0));
    expectVecNear(result, 0.0, 0.0, -1.0, K_EPS_TRIG);
}

TEST(TransformTest, RotateYDoesNotAffectY)
{
    auto t = Transform::rotateY(std::numbers::pi / 4.0);
    auto result = t(Vector3<double>(0.0, 1.0, 0.0));
    expectVecNear(result, 0.0, 1.0, 0.0, K_EPS_TRIG);
}

// ── rotateZ ───────────────────────────────────────────────────────────────────

TEST(TransformTest, RotateZ90DegreesMapsXToY)
{
    auto t = Transform::rotateZ(std::numbers::pi / 2.0);
    auto result = t(Vector3<double>(1.0, 0.0, 0.0));
    expectVecNear(result, 0.0, 1.0, 0.0, K_EPS_TRIG);
}

TEST(TransformTest, RotateZ90DegreesMapsYToNegX)
{
    auto t = Transform::rotateZ(std::numbers::pi / 2.0);
    auto result = t(Vector3<double>(0.0, 1.0, 0.0));
    expectVecNear(result, -1.0, 0.0, 0.0, K_EPS_TRIG);
}

TEST(TransformTest, RotateZDoesNotAffectZ)
{
    auto t = Transform::rotateZ(std::numbers::pi / 4.0);
    auto result = t(Vector3<double>(0.0, 0.0, 1.0));
    expectVecNear(result, 0.0, 0.0, 1.0, K_EPS_TRIG);
}

// ── rotate (arbitrary axis) ───────────────────────────────────────────────────

TEST(TransformTest, RotateAroundZAxisMatchesRotateZ)
{
    const double angle = std::numbers::pi / 4.0;
    auto tZ    = Transform::rotateZ(angle);
    auto tAxis = Transform::rotate(angle, {0.0, 0.0, 1.0});
    auto r1 = tZ(Vector3<double>(1.0, 0.0, 0.0));
    auto r2 = tAxis(Vector3<double>(1.0, 0.0, 0.0));
    expectVecNear(r2, r1.x(), r1.y(), r1.z(), K_EPS_TRIG);
}

TEST(TransformTest, RotateAroundXAxisMatchesRotateX)
{
    const double angle = std::numbers::pi / 3.0;
    auto tX    = Transform::rotateX(angle);
    auto tAxis = Transform::rotate(angle, {1.0, 0.0, 0.0});
    auto r1 = tX(Vector3<double>(0.0, 1.0, 0.0));
    auto r2 = tAxis(Vector3<double>(0.0, 1.0, 0.0));
    expectVecNear(r2, r1.x(), r1.y(), r1.z(), K_EPS_TRIG);
}

TEST(TransformTest, Rotate360DegreesIsIdentity)
{
    auto t = Transform::rotate(2.0 * std::numbers::pi, {0.0, 1.0, 0.0});
    auto result = t(Vector3<double>(1.0, 2.0, 3.0));
    expectVecNear(result, 1.0, 2.0, 3.0, K_EPS_TRIG);
}

// ── inverse ───────────────────────────────────────────────────────────────────

TEST(TransformTest, InverseOfTranslate)
{
    auto t    = Transform::translate({5.0, -3.0, 2.0});
    auto tInv = Transform::inverse(t);
    expectPointNear(tInv(Point3<double>(0.0, 0.0, 0.0)), -5.0, 3.0, -2.0);
}

TEST(TransformTest, InverseCompositionIsIdentity)
{
    auto t    = Transform::scale(2.0, 3.0, 4.0);
    auto tInv = Transform::inverse(t);
    EXPECT_TRUE((t * tInv).isIdentity());
}

TEST(TransformTest, InverseOfRotationIsTranspose)
{
    auto t    = Transform::rotateZ(std::numbers::pi / 6.0);
    auto tInv = Transform::inverse(t);
    auto v = Vector3<double>(1.0, 0.0, 0.0);
    auto forward  = t(v);
    auto roundtrip = tInv(forward);
    expectVecNear(roundtrip, 1.0, 0.0, 0.0, K_EPS_TRIG);
}

TEST(TransformTest, InverseOfIdentityIsIdentity)
{
    auto id    = Transform();
    auto idInv = Transform::inverse(id);
    EXPECT_TRUE(idInv.isIdentity());
}

// ── transpose ─────────────────────────────────────────────────────────────────

TEST(TransformTest, TransposeOfIdentityIsIdentity)
{
    auto id  = Transform();
    auto idT = Transform::transpose(id);
    EXPECT_TRUE(idT.isIdentity());
}

TEST(TransformTest, TransposeMatrixEqualsTransposedMatrix)
{
    auto t  = Transform::translate({1.0, 2.0, 3.0});
    auto tT = Transform::transpose(t);
    const auto &m  = t.getMatrix();
    const auto &mT = tT.getMatrix();
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            EXPECT_DOUBLE_EQ(mT[i][j], m[j][i]);
}

TEST(TransformTest, DoubleTransposeIsOriginal)
{
    auto t   = Transform::translate({1.0, 2.0, 3.0});
    auto tTT = Transform::transpose(Transform::transpose(t));
    EXPECT_EQ(tTT.getMatrix(), t.getMatrix());
    EXPECT_EQ(tTT.getInverseMatrix(), t.getInverseMatrix());
}

// ── operator()(Normal3) ───────────────────────────────────────────────────────

TEST(TransformTest, RotationTransformsNormalLikeVector)
{
    auto t = Transform::rotateZ(std::numbers::pi / 2.0);
    Normal3<double> n(1.0, 0.0, 0.0);
    auto result = t(n);
    EXPECT_NEAR(result.x(), 0.0, K_EPS_TRIG);
    EXPECT_NEAR(result.y(), 1.0, K_EPS_TRIG);
    EXPECT_NEAR(result.z(), 0.0, K_EPS_TRIG);
}

TEST(TransformTest, IdentityTransformLeavesNormalUnchanged)
{
    Transform id;
    Normal3<double> n(0.0, 1.0, 0.0);
    auto result = id(n);
    EXPECT_NEAR(result.x(), 0.0, K_EPS);
    EXPECT_NEAR(result.y(), 1.0, K_EPS);
    EXPECT_NEAR(result.z(), 0.0, K_EPS);
}

// ── operator()(Ray) ───────────────────────────────────────────────────────────

TEST(TransformTest, TranslateTransformsRayOriginNotDirection)
{
    auto t = Transform::translate({1.0, 2.0, 3.0});
    Ray r(Point3<double>(0.0, 0.0, 0.0), Vector3<double>(1.0, 0.0, 0.0));
    Ray result = t(r);
    expectPointNear(result.origin, 1.0, 2.0, 3.0);
    expectVecNear(result.direction, 1.0, 0.0, 0.0);
}

TEST(TransformTest, ScaleTransformsRayOriginAndDirection)
{
    auto t = Transform::scale(2.0, 2.0, 2.0);
    Ray r(Point3<double>(1.0, 1.0, 1.0), Vector3<double>(1.0, 0.0, 0.0));
    Ray result = t(r);
    expectPointNear(result.origin, 2.0, 2.0, 2.0);
    expectVecNear(result.direction, 2.0, 0.0, 0.0);
}

// ── operator()(Bounds3) ───────────────────────────────────────────────────────

TEST(TransformTest, TranslateBounds)
{
    auto t = Transform::translate({1.0, 2.0, 3.0});
    Bounds3<double> b(Point3<double>(0.0, 0.0, 0.0), Point3<double>(1.0, 1.0, 1.0));
    auto result = t(b);
    expectPointNear(result.pMin, 1.0, 2.0, 3.0);
    expectPointNear(result.pMax, 2.0, 3.0, 4.0);
}

TEST(TransformTest, ScaleBounds)
{
    auto t = Transform::scale(2.0, 3.0, 4.0);
    Bounds3<double> b(Point3<double>(1.0, 1.0, 1.0), Point3<double>(2.0, 2.0, 2.0));
    auto result = t(b);
    expectPointNear(result.pMin, 2.0, 3.0, 4.0);
    expectPointNear(result.pMax, 4.0, 6.0, 8.0);
}

// ── operator* (composition) ───────────────────────────────────────────────────

TEST(TransformTest, ComposeTranslations)
{
    auto t1 = Transform::translate({1.0, 0.0, 0.0});
    auto t2 = Transform::translate({0.0, 2.0, 0.0});
    auto composed = t1 * t2;
    auto result = composed(Point3<double>(0.0, 0.0, 0.0));
    expectPointNear(result, 1.0, 2.0, 0.0);
}

TEST(TransformTest, ComposeScaleAndTranslate)
{
    auto tScale     = Transform::scale(2.0, 2.0, 2.0);
    auto tTranslate = Transform::translate({1.0, 0.0, 0.0});
    auto composed   = tTranslate * tScale;
    auto result = composed(Point3<double>(1.0, 1.0, 1.0));
    expectPointNear(result, 3.0, 2.0, 2.0);
}

TEST(TransformTest, ComposeWithIdentityIsOriginal)
{
    auto t  = Transform::translate({3.0, -1.0, 2.0});
    auto id = Transform();
    EXPECT_TRUE((t * id) == t);
    EXPECT_TRUE((id * t) == t);
}
