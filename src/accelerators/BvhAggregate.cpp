/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** BvhAggregate
*/

#include <algorithm>
#include <array>

#include "BvhAggregate.hpp"

namespace raytracer {
namespace accelerator {

// ── BVHPrimitive ─────────────────────────────────────────────────────────────

BvhAggregate::BVHPrimitive::BVHPrimitive(
    size_t idx, const maths::Bounds3d &b):
    primitiveIndex(idx), bounds(b), centroid(b.centroid())
{}

// ── BVHBuildNode ─────────────────────────────────────────────────────────────

void BvhAggregate::BVHBuildNode::initLeaf(
    int firstOffset, int n, const maths::Bounds3d &b)
{
    firstPrimOffset = firstOffset;
    nPrimitives = n;
    bounds = b;
    children[0] = children[1] = nullptr;
}

void BvhAggregate::BVHBuildNode::initInterior(
    int axis, BVHBuildNode *left, BVHBuildNode *right)
{
    splitAxis = axis;
    children[0] = left;
    children[1] = right;
    bounds = left->bounds.boundsUnion(right->bounds);
    nPrimitives = 0;
}

// ── Constructor ───────────────────────────────────────────────────────────────

BvhAggregate::BvhAggregate(
    std::vector<std::unique_ptr<IPrimitive>> primitives, int maxPrimsInNode):
    _maxPrimsInNode{maxPrimsInNode},
    _primitives{std::move(primitives)}
{
    if (_primitives.empty())
        return;
    std::vector<BVHPrimitive> bvhPrimitives;
    bvhPrimitives.reserve(_primitives.size());
    for (size_t i = 0; i < _primitives.size(); ++i)
        bvhPrimitives.emplace_back(i, _primitives[i]->worldBound());
    std::deque<BVHBuildNode> nodePool;
    std::vector<IPrimitive *> orderedPrims;
    orderedPrims.reserve(_primitives.size());
    BVHBuildNode *root = buildRecursive(
        nodePool, bvhPrimitives, 0, static_cast<int>(bvhPrimitives.size()), orderedPrims);
    _nodes = std::make_unique<LinearBVHNode[]>(nodePool.size());
    int offset = 0;
    flattenBVH(root, &offset);
    _orderedPrims = std::move(orderedPrims);
}

// ── Build helpers ─────────────────────────────────────────────────────────────

maths::Bounds3d BvhAggregate::computePrimBounds(
    const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end)
{
    maths::Bounds3d bounds = bvhPrimitives[start].bounds;
    for (int i = start + 1; i < end; ++i)
        bounds = bounds.boundsUnion(bvhPrimitives[i].bounds);
    return bounds;
}

maths::Bounds3d BvhAggregate::computeCentroidBounds(
    const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end)
{
    maths::Bounds3d centroidBounds{bvhPrimitives[start].centroid};
    for (int i = start + 1; i < end; ++i)
        centroidBounds = centroidBounds.boundsUnion(bvhPrimitives[i].centroid);
    return centroidBounds;
}

auto BvhAggregate::fillBuckets(const std::vector<BVHPrimitive> &bvhPrimitives,
    int start, int end, int axis, double lo, double extent)
    -> std::array<BucketInfo, N_BUCKETS>
{
    std::array<BucketInfo, N_BUCKETS> buckets;
    for (int i = start; i < end; ++i) {
        const auto &prim = bvhPrimitives[i];
        int b = static_cast<int>(N_BUCKETS * (prim.centroid.data()[axis] - lo) / extent);
        if (b == N_BUCKETS)
            b = N_BUCKETS - 1;
        buckets[b].count++;
        if (!buckets[b].initialized) {
            buckets[b].bounds = prim.bounds;
            buckets[b].initialized = true;
        } else {
            buckets[b].bounds = buckets[b].bounds.boundsUnion(prim.bounds);
        }
    }
    return buckets;
}

std::pair<maths::Bounds3d, int> BvhAggregate::accumulateBuckets(
    const std::array<BucketInfo, N_BUCKETS> &buckets, int from, int to)
{
    maths::Bounds3d b;
    bool init = false;
    int count = 0;
    for (int j = from; j < to; ++j) {
        if (buckets[j].count == 0)
            continue;
        if (!init) { b = buckets[j].bounds; init = true; }
        else b = b.boundsUnion(buckets[j].bounds);
        count += buckets[j].count;
    }
    return {b, count};
}

auto BvhAggregate::computeSAHCosts(
    const std::array<BucketInfo, N_BUCKETS> &buckets, double parentSA)
    -> std::array<double, N_BUCKETS - 1>
{
    std::array<double, N_BUCKETS - 1> cost;
    for (int i = 0; i < N_BUCKETS - 1; ++i) {
        auto [b0, c0] = accumulateBuckets(buckets, 0, i + 1);
        auto [b1, c1] = accumulateBuckets(buckets, i + 1, N_BUCKETS);
        double sa0 = c0 > 0 ? b0.surfaceArea() : 0.0;
        double sa1 = c1 > 0 ? b1.surfaceArea() : 0.0;
        cost[i] = 1.0 + (sa0 * c0 + sa1 * c1) / parentSA;
    }
    return cost;
}

int BvhAggregate::findMinCostSplit(const std::array<double, N_BUCKETS - 1> &costs)
{
    int minSplit = 0;
    for (int i = 1; i < N_BUCKETS - 1; ++i)
        if (costs[i] < costs[minSplit])
            minSplit = i;
    return minSplit;
}

bool BvhAggregate::SplitPredicate::operator()(const BVHPrimitive &p) const
{
    return p.centroid.data()[axis] < splitPos;
}

bool BvhAggregate::CentroidAxisLess::operator()(
    const BVHPrimitive &a, const BVHPrimitive &b) const
{
    return a.centroid.data()[axis] < b.centroid.data()[axis];
}

int BvhAggregate::partitionPrims(
    std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
    int axis, double splitPos)
{
    auto *mid = std::partition(bvhPrimitives.data() + start, bvhPrimitives.data() + end,
        SplitPredicate{axis, splitPos});
    int midIdx = static_cast<int>(mid - bvhPrimitives.data());
    if (midIdx == start || midIdx == end) {
        midIdx = (start + end) / 2;
        std::nth_element(bvhPrimitives.data() + start, bvhPrimitives.data() + midIdx,
            bvhPrimitives.data() + end, CentroidAxisLess{axis});
    }
    return midIdx;
}

int BvhAggregate::computeSAHSplit(std::vector<BVHPrimitive> &bvhPrimitives,
    int start, int end, const maths::Bounds3d &bounds,
    const maths::Bounds3d &centroidBounds, int axis)
{
    double lo = centroidBounds.pMin.data()[axis];
    double extent = centroidBounds.pMax.data()[axis] - lo;
    auto buckets = fillBuckets(bvhPrimitives, start, end, axis, lo, extent);
    auto costs = computeSAHCosts(buckets, bounds.surfaceArea());
    int minSplit = findMinCostSplit(costs);
    if (costs[minSplit] >= static_cast<double>(end - start))
        return -1;
    double splitPos = lo + (minSplit + 1) * extent / N_BUCKETS;
    return partitionPrims(bvhPrimitives, start, end, axis, splitPos);
}

BvhAggregate::BVHBuildNode *BvhAggregate::buildLeaf(
    BVHBuildNode *node, const maths::Bounds3d &bounds,
    const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
    std::vector<IPrimitive *> &orderedPrims)
{
    int firstOffset = static_cast<int>(orderedPrims.size());
    for (int i = start; i < end; ++i)
        orderedPrims.push_back(_primitives[bvhPrimitives[i].primitiveIndex].get());
    node->initLeaf(firstOffset, end - start, bounds);
    return node;
}

BvhAggregate::BVHBuildNode *BvhAggregate::buildRecursive(
    std::deque<BVHBuildNode> &nodePool, std::vector<BVHPrimitive> &bvhPrimitives,
    int start, int end, std::vector<IPrimitive *> &orderedPrims)
{
    nodePool.emplace_back();
    BVHBuildNode *node = &nodePool.back();
    maths::Bounds3d bounds = computePrimBounds(bvhPrimitives, start, end);
    if (end - start <= _maxPrimsInNode)
        return buildLeaf(node, bounds, bvhPrimitives, start, end, orderedPrims);
    maths::Bounds3d centroidBounds = computeCentroidBounds(bvhPrimitives, start, end);
    int axis = centroidBounds.maxDimension();
    if (centroidBounds.pMin.data()[axis] == centroidBounds.pMax.data()[axis])
        return buildLeaf(node, bounds, bvhPrimitives, start, end, orderedPrims);
    int mid = computeSAHSplit(bvhPrimitives, start, end, bounds, centroidBounds, axis);
    if (mid < 0)
        return buildLeaf(node, bounds, bvhPrimitives, start, end, orderedPrims);
    node->initInterior(axis,
        buildRecursive(nodePool, bvhPrimitives, start, mid, orderedPrims),
        buildRecursive(nodePool, bvhPrimitives, mid, end, orderedPrims));
    return node;
}

// ── Flatten ───────────────────────────────────────────────────────────────────

int BvhAggregate::flattenBVH(BVHBuildNode *node, int *offset)
{
    LinearBVHNode *linearNode = &_nodes[*offset];
    linearNode->bounds = node->bounds;
    int myOffset = (*offset)++;
    if (node->nPrimitives > 0) {
        linearNode->primitivesOffset = node->firstPrimOffset;
        linearNode->nPrimitives = static_cast<uint16_t>(node->nPrimitives);
        linearNode->axis = 0;
    } else {
        linearNode->axis = static_cast<uint8_t>(node->splitAxis);
        linearNode->nPrimitives = 0;
        flattenBVH(node->children[0], offset);
        linearNode->secondChildOffset = flattenBVH(node->children[1], offset);
    }
    return myOffset;
}

// ── Traversal ─────────────────────────────────────────────────────────────────

std::optional<shape::SurfaceInteraction> BvhAggregate::intersect(
    const maths::Ray &ray) const
{
    if (!_nodes)
        return std::nullopt;
    maths::Vector3d invDir{
        1.0 / ray.direction.x(),
        1.0 / ray.direction.y(),
        1.0 / ray.direction.z()};
    std::array<int, 3> dirIsNeg{
        static_cast<int>(invDir.x() < 0),
        static_cast<int>(invDir.y() < 0),
        static_cast<int>(invDir.z() < 0)};
    std::optional<shape::SurfaceInteraction> bestHit;
    std::array<int, 64> stack;
    int toVisit = 0;
    int current = 0;
    while (true) {
        const LinearBVHNode &node = _nodes[current];
        if (node.bounds.intersectP(ray, invDir, dirIsNeg)) {
            if (node.nPrimitives > 0) {
                for (int i = 0; i < node.nPrimitives; ++i) {
                    auto hit = _orderedPrims[node.primitivesOffset + i]->intersect(ray);
                    if (hit)
                        bestHit = hit;
                }
                if (toVisit == 0) break;
                current = stack[--toVisit];
            } else {
                if (dirIsNeg[node.axis]) {
                    stack[toVisit++] = current + 1;
                    current = node.secondChildOffset;
                } else {
                    stack[toVisit++] = node.secondChildOffset;
                    current = current + 1;
                }
            }
        } else {
            if (toVisit == 0) break;
            current = stack[--toVisit];
        }
    }
    return bestHit;
}

bool BvhAggregate::intersectP(const maths::Ray &ray) const
{
    if (!_nodes)
        return false;
    maths::Vector3d invDir{
        1.0 / ray.direction.x(),
        1.0 / ray.direction.y(),
        1.0 / ray.direction.z()};
    std::array<int, 3> dirIsNeg{
        static_cast<int>(invDir.x() < 0),
        static_cast<int>(invDir.y() < 0),
        static_cast<int>(invDir.z() < 0)};
    std::array<int, 64> stack;
    int toVisit = 0;
    int current = 0;
    while (true) {
        const LinearBVHNode &node = _nodes[current];
        if (node.bounds.intersectP(ray, invDir, dirIsNeg)) {
            if (node.nPrimitives > 0) {
                for (int i = 0; i < node.nPrimitives; ++i) {
                    if (_orderedPrims[node.primitivesOffset + i]->intersectP(ray))
                        return true;
                }
            } else {
                if (dirIsNeg[node.axis]) {
                    stack[toVisit++] = current + 1;
                    current = node.secondChildOffset;
                } else {
                    stack[toVisit++] = node.secondChildOffset;
                    current = current + 1;
                }
                continue;
            }
        }
        if (toVisit == 0) break;
        current = stack[--toVisit];
    }
    return false;
}

maths::Bounds3d BvhAggregate::worldBound() const
{
    if (!_nodes)
        return maths::Bounds3d{maths::Point3d{0, 0, 0}};
    return _nodes[0].bounds;
}

} // namespace accelerator
} // namespace raytracer
