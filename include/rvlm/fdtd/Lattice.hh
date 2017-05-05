#pragma once
#include <vector>
#include "Common.hh"
#include "Field.hh"

namespace rvlm {
namespace fdtd {

template <typename T>
class Sublattice {
public:
    //
};

template <typename T>
class Lattice {
public:

    Lattice(IndexType nx, IndexType ny, IndexType nz) {

    }

    T const& getField(Field field, IndexType ix, IndexType iy, IndexType iz);

private:
    std::vector<T> mCoordinateX_FieldEx;
    std::vector<T> mCoordinateX_FieldEy;
    std::vector<T> mCoordinateX_FieldEz;
    std::vector<T> mCoordinateY_FieldEx;
    std::vector<T> mCoordinateY_FieldEy;
    std::vector<T> mCoordinateY_FieldEz;
    std::vector<T> mCoordinateZ_FieldEx;
    std::vector<T> mCoordinateZ_FieldEy;
    std::vector<T> mCoordinateZ_FieldEz;
};

}
}
