/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** BvhAggregate
*/

#include <algorithm>
#include <array>
#ifdef RAYTRACER_DEBUG
#include <cstdio>
#endif

#include "BvhAggregate.hpp"


namespace raytracer::accelerator {

BvhAggregate::BvhAggregate(
    std::vector<std::unique_ptr<IPrimitive>> primitives, int maxPrimsInNode):
    _maxPrimsInNode{maxPrimsInNode}, _primitives{std::move(primitives)}
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
    BVHBuildNode *root = buildRecursive(nodePool, bvhPrimitives, 0,
        static_cast<int>(bvhPrimitives.size()), orderedPrims);
    _nodes             = std::make_unique<LinearBVHNode[]>(nodePool.size());
    int offset         = 0;
    flattenBVH(root, &offset);
    _orderedPrims = std::move(orderedPrims);
#ifdef RAYTRACER_DEBUG
    printf("BVH built: %zu total nodes, %zu ordered prims\n",
        nodePool.size(), _orderedPrims.size());
    for (size_t ni = 0; ni < nodePool.size(); ++ni) {
        const LinearBVHNode &n = _nodes[ni];
        if (n.nPrimitives > 0)
            printf("  Leaf[%zu]: primOffset=%d nPrims=%d bounds=[(%g,%g,%g)..(%g,%g,%g)]\n",
                ni, n.primitivesOffset, n.nPrimitives,
                n.bounds.pMin.x(), n.bounds.pMin.y(), n.bounds.pMin.z(),
                n.bounds.pMax.x(), n.bounds.pMax.y(), n.bounds.pMax.z());
    }
    printf("BVH primitive bounds per original index:\n");
    for (size_t i = 0; i < bvhPrimitives.size(); ++i)
        printf("  prim[%zu]: centroid=(%g,%g,%g) bounds=[(%g,%g,%g)..(%g,%g,%g)]\n",
            i, bvhPrimitives[i].centroid.x(), bvhPrimitives[i].centroid.y(),
            bvhPrimitives[i].centroid.z(),
            bvhPrimitives[i].bounds.pMin.x(), bvhPrimitives[i].bounds.pMin.y(),
            bvhPrimitives[i].bounds.pMin.z(),
            bvhPrimitives[i].bounds.pMax.x(), bvhPrimitives[i].bounds.pMax.y(),
            bvhPrimitives[i].bounds.pMax.z());
#endif
}

std::optional<shape::SurfaceInteraction> BvhAggregate::intersect(
    const maths::Ray &ray) const
{
    if (!_nodes)
        return std::nullopt;
    return traverseForHit(ray);
}

bool BvhAggregate::intersectP(const maths::Ray &ray) const
{
    if (!_nodes)
        return false;
    return traverseForAnyHit(ray);
}

maths::Bounds3d BvhAggregate::worldBound() const
{
    if (!_nodes)
        return maths::Bounds3d{maths::Point3d{0, 0, 0}};
    return _nodes[0].bounds;
}

BvhAggregate::BVHPrimitive::BVHPrimitive(size_t idx, const maths::Bounds3d &b):
    primitiveIndex(idx), bounds(b), centroid(b.centroid())
{}

void BvhAggregate::BVHBuildNode::initLeaf(
    int firstOffset, int n, const maths::Bounds3d &b)
{
    firstPrimOffset = firstOffset;
    nPrimitives     = n;
    bounds          = b;
    children[0] = children[1] = nullptr;
}

void BvhAggregate::BVHBuildNode::initInterior(
    int axis, BVHBuildNode *left, BVHBuildNode *right)
{
    splitAxis   = axis;
    children[0] = left;
    children[1] = right;
    bounds      = left->bounds.boundsUnion(right->bounds);
    nPrimitives = 0;
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

BvhAggregate::BVHBuildNode *BvhAggregate::buildRecursive(
    std::deque<BVHBuildNode> &nodePool,
    std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
    std::vector<IPrimitive *> &orderedPrims)
{
    nodePool.emplace_back();
    BVHBuildNode *node     = &nodePool.back();
    maths::Bounds3d bounds = computePrimBounds(bvhPrimitives, start, end);
    if (end - start <= _maxPrimsInNode)
        return buildLeaf(node, bounds, bvhPrimitives, start, end, orderedPrims);
    auto [axis, mid] = determineSplit(bvhPrimitives, start, end, bounds);
    if (mid < 0)
        return buildLeaf(node, bounds, bvhPrimitives, start, end, orderedPrims);
    node->initInterior(axis,
        buildRecursive(nodePool, bvhPrimitives, start, mid, orderedPrims),
        buildRecursive(nodePool, bvhPrimitives, mid, end, orderedPrims));
    return node;
}

BvhAggregate::BVHBuildNode *BvhAggregate::buildLeaf(BVHBuildNode *node,
    const maths::Bounds3d &bounds,
    const std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
    std::vector<IPrimitive *> &orderedPrims)
{
    int firstOffset = static_cast<int>(orderedPrims.size());
    for (int i = start; i < end; ++i)
        orderedPrims.push_back(
            _primitives[bvhPrimitives[i].primitiveIndex].get());
    node->initLeaf(firstOffset, end - start, bounds);
    return node;
}

int BvhAggregate::flattenBVH(BVHBuildNode *node, int *offset)
{
    LinearBVHNode *linearNode = &_nodes[*offset];
    linearNode->bounds        = node->bounds;
    int myOffset              = (*offset)++;
    if (node->nPrimitives > 0) {
        linearNode->primitivesOffset = node->firstPrimOffset;
        linearNode->nPrimitives      = static_cast<uint16_t>(node->nPrimitives);
        linearNode->axis             = 0;
    } else {
        linearNode->axis        = static_cast<uint8_t>(node->splitAxis);
        linearNode->nPrimitives = 0;
        flattenBVH(node->children[0], offset);
        linearNode->secondChildOffset = flattenBVH(node->children[1], offset);
    }
    return myOffset;
}

std::optional<shape::SurfaceInteraction> BvhAggregate::traverseForHit(
    const maths::Ray &ray) const
{
    auto [inv, dirIsNeg] = computeRaySetup(ray);
    std::optional<shape::SurfaceInteraction> bestHit;
    std::array<int, 64> stack;
    int toVisit = 0, current = 0;
    while (true) {
        const LinearBVHNode &node = _nodes[current];
        bool hit                  = node.bounds.intersectP(ray, inv, dirIsNeg);
#ifdef RAYTRACER_DEBUG
        printf("  BVH node %d: nPrim=%d hit=%d bounds=[(%f,%f,%f)..(%f,%f,%f)]\n",
            current, node.nPrimitives, (int)hit,
            node.bounds.pMin.x(), node.bounds.pMin.y(), node.bounds.pMin.z(),
            node.bounds.pMax.x(), node.bounds.pMax.y(), node.bounds.pMax.z());
#endif
        if (hit && node.nPrimitives > 0) {
            processLeafHit(node, ray, bestHit);
#ifdef RAYTRACER_DEBUG
            printf("  after processLeafHit: bestHit=%s\n", bestHit ? "YES" : "NO");
#endif
            if (!popStack(stack, toVisit, current))
                break;
        } else if (hit) {
            advanceToChild(node, dirIsNeg, stack, toVisit, current);
        } else if (!popStack(stack, toVisit, current)) {
            break;
        }
    }
    return bestHit;
}

bool BvhAggregate::traverseForAnyHit(const maths::Ray &ray) const
{
    auto [inv, dirIsNeg] = computeRaySetup(ray);
    std::array<int, 64> stack;
    int toVisit = 0, current = 0;
    while (true) {
        const LinearBVHNode &node = _nodes[current];
        bool hit                  = node.bounds.intersectP(ray, inv, dirIsNeg);
        if (hit && node.nPrimitives > 0) {
            if (anyHitInLeaf(node, ray))
                return true;
        } else if (hit) {
            advanceToChild(node, dirIsNeg, stack, toVisit, current);
            continue;
        }
        if (!popStack(stack, toVisit, current))
            break;
    }
    return false;
}

void BvhAggregate::processLeafHit(const LinearBVHNode &node,
    const maths::Ray &ray,
    std::optional<shape::SurfaceInteraction> &bestHit) const
{
    for (int i = 0; i < node.nPrimitives; ++i) {
        auto hit = _orderedPrims[node.primitivesOffset + i]->intersect(ray);
        if (hit)
            bestHit = hit;
    }
}

bool BvhAggregate::anyHitInLeaf(
    const LinearBVHNode &node, const maths::Ray &ray) const
{
    for (int i = 0; i < node.nPrimitives; ++i)
        if (_orderedPrims[node.primitivesOffset + i]->intersectP(ray))
            return true;
    return false;
}

std::pair<maths::Vector3d, std::array<int, 3>> BvhAggregate::computeRaySetup(
    const maths::Ray &ray)
{
    auto inv = computeInvDir(ray);
    return {inv, computeDirNegMask(inv)};
}

maths::Vector3d BvhAggregate::computeInvDir(const maths::Ray &ray)
{
    return {1.0 / ray.direction.x(), 1.0 / ray.direction.y(),
        1.0 / ray.direction.z()};
}

std::array<int, 3> BvhAggregate::computeDirNegMask(
    const maths::Vector3d &invDir)
{
    return {static_cast<int>(invDir.x() < 0), static_cast<int>(invDir.y() < 0),
        static_cast<int>(invDir.z() < 0)};
}

bool BvhAggregate::popStack(
    std::array<int, 64> &stack, int &toVisit, int &current)
{
    if (toVisit == 0)
        return false;
    current = stack[--toVisit];
    return true;
}

void BvhAggregate::advanceToChild(const LinearBVHNode &node,
    const std::array<int, 3> &dirIsNeg, std::array<int, 64> &stack,
    int &toVisit, int &current)
{
    if (dirIsNeg[node.axis]) {
        stack[toVisit++] = current + 1;
        current          = node.secondChildOffset;
    } else {
        stack[toVisit++] = node.secondChildOffset;
        current          = current + 1;
    }
}

std::pair<int, int> BvhAggregate::determineSplit(
    std::vector<BVHPrimitive> &bvhPrimitives, int start, int end,
    const maths::Bounds3d &bounds)
{
    maths::Bounds3d cb = computeCentroidBounds(bvhPrimitives, start, end);
    int axis           = cb.maxDimension();
    if (cb.pMin.data()[axis] == cb.pMax.data()[axis])
        return {axis, -1};
    return {axis, computeSAHSplit(bvhPrimitives, start, end, bounds, cb, axis)};
}

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
    maths::Bounds3d cb{bvhPrimitives[start].centroid};
    for (int i = start + 1; i < end; ++i)
        cb = cb.boundsUnion(bvhPrimitives[i].centroid);
    return cb;
}

int BvhAggregate::bucketIndex(
    const BVHPrimitive &prim, int axis, double lo, double extent)
{
    int b = static_cast<int>(
        N_BUCKETS * (prim.centroid.data()[axis] - lo) / extent);
    return std::clamp(b, 0, N_BUCKETS - 1);
}

void BvhAggregate::updateBucket(
    BucketInfo &bucket, const maths::Bounds3d &bounds)
{
    bucket.count++;
    if (!bucket.initialized) {
        bucket.bounds      = bounds;
        bucket.initialized = true;
    } else {
        bucket.bounds = bucket.bounds.boundsUnion(bounds);
    }
}

auto BvhAggregate::fillBuckets(const std::vector<BVHPrimitive> &bvhPrimitives,
    int start, int end, int axis, double lo, double extent)
    -> std::array<BucketInfo, N_BUCKETS>
{
    std::array<BucketInfo, N_BUCKETS> buckets;
    for (int i = start; i < end; ++i) {
        const auto &prim = bvhPrimitives[i];
        updateBucket(buckets[bucketIndex(prim, axis, lo, extent)], prim.bounds);
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
        if (!init) {
            b    = buckets[j].bounds;
            init = true;
        } else
            b = b.boundsUnion(buckets[j].bounds);
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
        double sa0    = c0 > 0 ? b0.surfaceArea() : 0.0;
        double sa1    = c1 > 0 ? b1.surfaceArea() : 0.0;
        cost[i]       = 1.0 + (sa0 * c0 + sa1 * c1) / parentSA;
    }
    return cost;
}

int BvhAggregate::findMinCostSplit(
    const std::array<double, N_BUCKETS - 1> &costs)
{
    int minSplit = 0;
    for (int i = 1; i < N_BUCKETS - 1; ++i)
        if (costs[i] < costs[minSplit])
            minSplit = i;
    return minSplit;
}

int BvhAggregate::computeSAHSplit(std::vector<BVHPrimitive> &bvhPrimitives,
    int start, int end, const maths::Bounds3d &bounds,
    const maths::Bounds3d &centroidBounds, int axis)
{
    double lo     = centroidBounds.pMin.data()[axis];
    double extent = centroidBounds.pMax.data()[axis] - lo;
    auto buckets  = fillBuckets(bvhPrimitives, start, end, axis, lo, extent);
    auto costs    = computeSAHCosts(buckets, bounds.surfaceArea());
    int minSplit  = findMinCostSplit(costs);
    if (costs[minSplit] >= static_cast<double>(end - start))
        return -1;
    double splitPos = lo + (minSplit + 1) * extent / N_BUCKETS;
    return partitionPrims(bvhPrimitives, start, end, axis, splitPos);
}

int BvhAggregate::partitionPrims(std::vector<BVHPrimitive> &bvhPrimitives,
    int start, int end, int axis, double splitPos)
{
    auto *mid  = std::partition(bvhPrimitives.data() + start,
         bvhPrimitives.data() + end, SplitPredicate{axis, splitPos});
    int midIdx = static_cast<int>(mid - bvhPrimitives.data());
    if (midIdx == start || midIdx == end) {
        midIdx = (start + end) / 2;
        std::nth_element(bvhPrimitives.data() + start,
            bvhPrimitives.data() + midIdx, bvhPrimitives.data() + end,
            CentroidAxisLess{axis});
    }
    return midIdx;
}

} // namespace raytracer::accelerator

