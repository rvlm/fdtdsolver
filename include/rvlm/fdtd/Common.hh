#pragma once
#include <cstddef>
#include <rvlm/core/Vector3d.hh>
#include <rvlm/core/Cuboid.hh>
#include "rvlm/core/HalfOpenRange.hh"
#include "rvlm/core/SolidArray3d.hh"

namespace rvlm {
namespace fdtd {

typedef ptrdiff_t IndexType;
typedef rvlm::core::HalfOpenRange<IndexType> HalfOpenIndexRange;

typedef double DefaultValueType;

template <typename T>
using ArrayType = rvlm::core::SolidArray3d<T, IndexType>;

template <typename T>
using Triple = std::tuple<T, T, T>;

template <typename T>
Triple<T> make_triple(T const& item1, T const& item2, T const& item3) {
    return std::make_tuple(item1, item2, item3);
}

typedef Triple<IndexType> Indices;
using IndicesRange = Triple<HalfOpenIndexRange>;

static
Triple<HalfOpenIndexRange> expandRangePlus(Triple<HalfOpenIndexRange> const& range) {
    auto rangeX = std::get<0>(range);
    auto rangeY = std::get<1>(range);
    auto rangeZ = std::get<2>(range);
    return make_triple(HalfOpenIndexRange(rangeX.start, rangeX.stop+1),
                       HalfOpenIndexRange(rangeY.start, rangeY.stop+1),
                       HalfOpenIndexRange(rangeZ.start, rangeZ.stop+1));
}

static
Triple<HalfOpenIndexRange> expandRangeMinus(Triple<HalfOpenIndexRange> const& range) {
    auto rangeX = std::get<0>(range);
    auto rangeY = std::get<1>(range);
    auto rangeZ = std::get<2>(range);
    return make_triple(HalfOpenIndexRange(rangeX.start-1, rangeX.stop),
                       HalfOpenIndexRange(rangeY.start-1, rangeY.stop),
                       HalfOpenIndexRange(rangeZ.start-1, rangeZ.stop));
}
}

}
