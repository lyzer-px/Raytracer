/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** BVHAggregate
*/

#pragma once

#include <array>
#include <deque>
#include <memory>
#include <utility>
#include <vector>

#include "IPrimitive.hpp"

namespace raytracer::accelerator {

class BvhAggregate: public shape::IPrimitive {
public:
    explicit BvhAggregate(std::vector<std::unique_ptr<IPrimitive>> primitives,
        int maxPrimsInNode = 1);

    [[nodiscard]] std::optional<shape::SurfaceInteraction> intersect(
        const maths::Ray &ray) const override;

    [[nodiscard]] bool intersectP(const maths::Ray &ray) const override;

    [[nodiscard]] maths::Bounds3d worldBound() const override;

    [[nodiscard]] const material::IMaterial *material() const override
    {
        return nullptr;
    }

private:
    static constexpr auto N_BUCKETS = 12;

    struct BVHPrimitive {
        BVHPrimitive(size_t primitiveIndex, const maths::Bounds3d &bounds);
        size_t primitiveIndex;
        maths::Bounds3d bounds;
        maths::Point3d centroid;
    };

    struct BVHBuildNode {
        void initLeaf(
            int firstPrimOffset, int nPrimitives, const maths::Bounds3d &b);
        void initInterior(
            int splitAxis, BVHBuildNode *left, BVHBuildNode *right);

        maths::Bounds3d bounds;
        BVHBuildNode *children[2] = {nullptr, nullptr};
        int splitAxis             = 0;
        int firstPrimOffset       = 0;
        int nPrimitives           = 0;
    };

    struct alignas(32) LinearBVHNode {
        maths::Bounds3d bounds;
        union {
            int primitivesOffset;
            int secondChildOffset;
        };
        uint16_t nPrimitives;
        uint8_t axis;
    };

    struct BucketInfo {
        int count = 0;
        maths::Bounds3d bounds;
        bool initialized = false;
    };

    struct SplitPredicate {
        int axis;
        double splitPos;
        bool operator()(const BVHPrimitive &p) const;
    };

    struct CentroidAxisLess {
        int axis;
        bool operator()(const BVHPrimitive &a, const BVHPrimitive &b) const;
    };

    int _maxPrimsInNode;
    std::vector<std::unique_ptr<IPrimitive>> _primitives;
    std::unique_ptr<LinearBVHNode[]> _nodes;
    std::vector<IPrimitive *> _orderedPrims;

    BVHBuildNode *buildRecursive(std::deque<BVHBuildNode> &nodePool,
        std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
        std::vector<IPrimitive *> &orderedPrims);

    BVHBuildNode *buildLeaf(BVHBuildNode *node, const maths::Bounds3d &bounds,
        const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
        std::vector<IPrimitive *> &orderedPrims);

    int flattenBVH(BVHBuildNode *node, int *offset);

    std::optional<shape::SurfaceInteraction> traverseForHit(
        const maths::Ray &ray) const;

    bool traverseForAnyHit(const maths::Ray &ray) const;

    void processLeafHit(const LinearBVHNode &node, const maths::Ray &ray,
        std::optional<shape::SurfaceInteraction> &bestHit) const;

    bool anyHitInLeaf(const LinearBVHNode &node, const maths::Ray &ray) const;

    static std::pair<maths::Vector3d, std::array<int, 3>> computeRaySetup(
        const maths::Ray &ray);

    static maths::Vector3d computeInvDir(const maths::Ray &ray);

    static std::array<int, 3> computeDirNegMask(const maths::Vector3d &invDir);

    static bool popStack(
        std::array<int, 64> &stack, int &toVisit, int &current);

    static void advanceToChild(const LinearBVHNode &node,
        const std::array<int, 3> &dirIsNeg,
        std::array<int, 64> &stack, int &toVisit, int &current);

    static std::pair<int, int> determineSplit(
        std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
        const maths::Bounds3d &bounds);

    static maths::Bounds3d computePrimBounds(
        const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end);

    static maths::Bounds3d computeCentroidBounds(
        const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end);

    static int bucketIndex(
        const BVHPrimitive &prim, int axis, double lo, double extent);

    static void updateBucket(BucketInfo &bucket, const maths::Bounds3d &bounds);

    static std::array<BucketInfo, N_BUCKETS> fillBuckets(
        const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
        int axis, double lo, double extent);

    static std::pair<maths::Bounds3d, int> accumulateBuckets(
        const std::array<BucketInfo, N_BUCKETS> &buckets, int from, int to);

    static std::array<double, N_BUCKETS - 1> computeSAHCosts(
        const std::array<BucketInfo, N_BUCKETS> &buckets, double parentSA);

    static int findMinCostSplit(const std::array<double, N_BUCKETS - 1> &costs);

    static int computeSAHSplit(std::vector<BVHPrimitive> &bvhPrimitives,
        int start, int end, const maths::Bounds3d &bounds,
        const maths::Bounds3d &centroidBounds, int axis);

    static int partitionPrims(std::vector<BVHPrimitive> &bvhPrimitives,
        int start, int end, int axis, double splitPos);
};

} // namespace raytracer::accelerator
