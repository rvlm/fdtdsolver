#pragma once
#include <cstddef>
#include <rvlm/core/Vector3d.hh>
#include <rvlm/core/Cuboid.hh>
#include "rvlm/core/HalfOpenRange.hh"
#include "rvlm/core/SolidArray3d.hh"

namespace rvlm {
namespace fdtd {

typedef ptrdiff_t IndexType;
typedef rvlm::core::Vector3d<IndexType> Indices;
typedef rvlm::core::Cuboid<IndexType> IndicesRange;
typedef rvlm::core::HalfOpenRange<IndexType> HalfOpenIndexRange;

typedef double DefaultValueType;

template <typename T>
using ArrayType = rvlm::core::SolidArray3d<T, IndexType>;

template <typename T>
using Triple = std::tuple<T, T, T>;

}


}
