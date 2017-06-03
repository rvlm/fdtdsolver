#pragma once
#include <stdexcept>
#include <tuple>
#include <vector>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/range.hpp>
#include "rvlm/core/HalfOpenRange.hh"
#include "rvlm/fdtd/Common.hh"
#include "rvlm/fdtd/Field.hh"

namespace rvlm {
namespace fdtd {

template <typename T=double>
class Lattice {
public:

    using Iterator = typename std::vector<T>::const_iterator;

    /**
     * Creates tridimentional Yee lattice with equidistant nodes.
     *
     * @param dims
     * A triple of @em positive integer numbers (dimX, dimY, dimZ) which specify
     * the number of well-defined Yee cells along each axis. After the object
     * created, the total number of well-defined cells will be dimX⋅dimY⋅dimZ.
     * Since there will be additional layers of partially defined cells on each
     * side of lattice, the total number of Yee cells (both well-defined and
     * partially defined) will be equal to (dimX+2)⋅(dimY+2)⋅(dimZ+2).
     *
     * @param deltas
     * A triple of @em positive real numbers (deltaX, deltaY, deltaZ) which
     * specify the distances between the neighbour nodes of the lattice in each
     * axis direction. These delta numbers thought as the distances between
     * the electric planes of the Yee cells; the magnetic planes are
     * automatically put to the midpoints of electric planes.
     *
     * TODO: There should be a picture to illustrate the Yee cell's planes.
     *
     * @throws std::invalid_argument
     * @throws std::bad_alloc
     */
    Lattice(Triple<IndexType> const& dims, Triple<T> const& deltas) {

        T const& deltaX = std::get<0>(deltas);
        T const& deltaY = std::get<1>(deltas);
        T const& deltaZ = std::get<2>(deltas);

        if (deltaX <= 0 || deltaY <= 0 || deltaZ <= 0)
            throw std::invalid_argument("Bad lattice delta: must be positive.");

        std::size_t nx, ny, nz;

        try {
            nx = boost::numeric_cast<std::size_t>(std::get<0>(dims));
            ny = boost::numeric_cast<std::size_t>(std::get<1>(dims));
            nz = boost::numeric_cast<std::size_t>(std::get<2>(dims));
        }
        catch (boost::bad_numeric_cast const&) {
            std::throw_with_nested(std::invalid_argument(
                "Bad lattice dimensions: must fit to std::size_t"));
        }

        if (nx < 1 || ny < 1 || nz < 1) {
            throw std::invalid_argument(
                "Bad lattice dimensions: must contain at least one Yee cell");
        }

        try {
            mEyzTicksX.resize(nx+1);
            mExzTicksY.resize(ny+1);
            mExyTicksZ.resize(nz+1);
            mHyzTicksX.resize(nx+1);
            mHxzTicksY.resize(ny+1);
            mHxyTicksZ.resize(nz+1);

            mEyzDeltasX.resize(nx, deltaX);
            mExzDeltasY.resize(ny, deltaY);
            mExyDeltasZ.resize(nz, deltaZ);
            mHyzDeltasX.resize(nx, deltaX);
            mHxzDeltasY.resize(ny, deltaY);
            mHxyDeltasZ.resize(nz, deltaZ);
        }
        catch (...) {
            // The standard doesn't say which exception std::vector::resize()
            // throws on failure. Let's catch 'em all.
            std::throw_with_nested(std::bad_alloc());
        }

        for (std::size_t ux = 0; ux < nx+1; ++ux)
            mEyzTicksX[ux] = deltaX * ux;

        for (std::size_t uy = 0; uy < ny+1; ++uy)
            mEyzTicksX[uy] = deltaY * uy;

        for (std::size_t uz = 0; uz < nz+1; ++uz)
            mEyzTicksX[uz] = deltaZ * uz;

        for (std::size_t ux = 0; ux < nx+1; ++ux)
            mHyzDeltasX[ux] = deltaX * ux - deltaX/2;

        for (std::size_t uy = 0; uy < ny+1; ++uy)
            mHyzDeltasX[uy] = deltaY * uy - deltaY/2;

        for (std::size_t uz = 0; uz < ny+1; ++uz)
            mHyzDeltasX[uz] = deltaZ * uz - deltaZ/2;
    }

    Triple<IndexType> const& getDimensions() const {
        return mDimensions;
    }

    Iterator getTickIterator(Field field, Axis axis, IndexType idx) const {

        // TODO: Optimize out unnecessary 'vector.cbegin()' evaluations.
        // The current implementation (probably) causes a lot of code bloat;
        // with no doubt it can be transformed into a more compact form with
        // fewer function calls.
        //
        // Optimization hints:
        //    (a) rely on sequential ordering of enum constants;
        //    (b) organize tick vectors (or pointers for them) in a static
        //        array and do a simple index lookup;
        //    (c) ditto for delta vectors;
        //
        switch (field) {
            case Field::Ex:
                return selectAxis(axis, mHyzTicksX.cbegin()+idx+1,
                                        mExzTicksY.cbegin()+idx,
                                        mExyTicksZ.cbegin()+idx);
            case Field::Ey:
                return selectAxis(axis, mEyzTicksX.cbegin()+idx,
                                        mHxzTicksY.cbegin()+idx+1,
                                        mExyTicksZ.cbegin()+idx);
            case Field::Ez:
                return selectAxis(axis, mEyzTicksX.cbegin()+idx,
                                        mExzTicksY.cbegin()+idx,
                                        mHxyTicksZ.cbegin()+idx+1);
            case Field::Hx:
                return selectAxis(axis, mEyzTicksX.cbegin()+idx,
                                        mHxzTicksY.cbegin()+idx+1,
                                        mHxyTicksZ.cbegin()+idx+1);
            case Field::Hy:
                return selectAxis(axis, mHyzTicksX.cbegin()+idx+1,
                                        mExzTicksY.cbegin()+idx,
                                        mHxyTicksZ.cbegin()+idx+1);
            case Field::Hz:
                return selectAxis(axis, mHyzTicksX.cbegin()+idx+1,
                                        mHxzTicksY.cbegin()+idx+1,
                                        mExyTicksZ.cbegin()+idx);

            default: throw std::invalid_argument(
                "Bad field component: must be one of Ex, Ey, Ez or Hx, Hy, Hz");
        }
    }

    Iterator getDeltaIterator(Field field, Axis axis, IndexType idx) const {

        // TODO: Eliminate that terrible copy & paste.
        switch (field) {
            case Field::Ex:
                return selectAxis(axis, mHyzDeltasX.cbegin()+idx+1,
                                  mExzDeltasY.cbegin()+idx,
                                  mExyDeltasZ.cbegin()+idx);
            case Field::Ey:
                return selectAxis(axis, mEyzDeltasX.cbegin()+idx,
                                  mHxzDeltasY.cbegin()+idx+1,
                                  mExyDeltasZ.cbegin()+idx);
            case Field::Ez:
                return selectAxis(axis, mEyzDeltasX.cbegin()+idx,
                                  mExzDeltasY.cbegin()+idx,
                                  mHxyDeltasZ.cbegin()+idx+1);
            case Field::Hx:
                return selectAxis(axis, mEyzDeltasX.cbegin()+idx,
                                  mHxzDeltasY.cbegin()+idx+1,
                                  mHxyDeltasZ.cbegin()+idx+1);
            case Field::Hy:
                return selectAxis(axis, mHyzDeltasX.cbegin()+idx+1,
                                  mExzDeltasY.cbegin()+idx,
                                  mHxyDeltasZ.cbegin()+idx+1);
            case Field::Hz:
                return selectAxis(axis, mHyzDeltasX.cbegin()+idx+1,
                                  mHxzDeltasY.cbegin()+idx+1,
                                  mExyDeltasZ.cbegin()+idx);

            default: throw std::invalid_argument(
                "Bad field component: must be one of Ex, Ey, Ez or Hx, Hy, Hz");
        }
    }

private:

    Triple<IndexType> mDimensions;

    std::vector<T> mExyTicksZ;
    std::vector<T> mExzTicksY;
    std::vector<T> mEyzTicksX;
    std::vector<T> mHxyTicksZ;
    std::vector<T> mHxzTicksY;
    std::vector<T> mHyzTicksX;

    std::vector<T> mExyDeltasZ;
    std::vector<T> mExzDeltasY;
    std::vector<T> mEyzDeltasX;
    std::vector<T> mHxyDeltasZ;
    std::vector<T> mHxzDeltasY;
    std::vector<T> mHyzDeltasX;
};

}
}
