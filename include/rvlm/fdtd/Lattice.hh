#pragma once
#include <vector>
#include <stdexcept>
#include <tuple>
#include <boost/optional.hpp>
#include "rvlm/fdtd/Common.hh"
#include "rvlm/fdtd/Field.hh"

namespace rvlm {
namespace fdtd {

template <typename T=double>
class Lattice {
public:

    Lattice(IndexType nx, IndexType ny, IndexType nz,
            T const& deltaX, T const& deltaY, T const& deltaZ) {

        if (nx < 0 || ny < 0 || nz < 0)
            throw std::runtime_error("Bad lattice dimensions");

        auto unx = static_cast<std::size_t>(nx);
        auto uny = static_cast<std::size_t>(ny);
        auto unz = static_cast<std::size_t>(nz);

        mPositionX.resize(unx);
        mPositionY.resize(uny);
        mPositionZ.resize(unz);
        mPositionXprime.resize(unx - 1);
        mPositionYprime.resize(uny - 1);
        mPositionZprime.resize(unz - 1);

        mDeltaX.resize(unx - 1, deltaX);
        mDeltaY.resize(uny - 1, deltaY);
        mDeltaZ.resize(unz - 1, deltaZ);
        mDeltaXprime.resize(unx - 2, deltaX);
        mDeltaYprime.resize(uny - 2, deltaY);
        mDeltaZprime.resize(unz - 2, deltaZ);

        for (std::size_t uix = 0; uix < unx; ++uix)
            mPositionX[uix] = deltaX * uix;

        for (std::size_t uiy = 0; uiy < uny; ++uiy)
            mPositionY[uiy] = deltaY * uiy;

        for (std::size_t uiz = 0; uiz < unz; ++uiz)
            mPositionZ[uiz] = deltaZ * uiz;

        for (std::size_t uix = 0; uix < nx-1; ++uix)
            mPositionXprime[uix] = (2*uix+1)*deltaX/2;

        for (std::size_t uiy = 0; uiy < ny-1; ++uiy)
            mPositionYprime[uiy] = (2*uiy+1)*deltaY/2;

        for (std::size_t uiz = 0; uiz < nz-1; ++uiz)
            mPositionZprime[uiz] = (2*uiz+1)*deltaZ/2;
    }

    Lattice(IndexType nx, IndexType ny, IndexType nz, T const& delta)
        : Lattice(nx, ny, nz, delta, delta, delta) {}

    typedef std::vector<T> const& VectorRef;

    boost::optional<rvlm::fdtd::Triple<VectorRef>> getSublattice(Field field) const {
        auto tuple = [](VectorRef a, VectorRef b, VectorRef c) {
            return std::tuple<VectorRef, VectorRef, VectorRef>(a, b, c);
        };

        switch (field) {
            case Field::Ex:
                return tuple(mPositionXprime, mPositionY, mPositionZ);
            case Field::Ey:
                return tuple(mPositionX, mPositionYprime, mPositionZ);
            case Field::Ez:
                return tuple(mPositionX, mPositionY, mPositionZprime);
            case Field::Hx:
                return tuple(mPositionY, mPositionYprime, mPositionZprime);
            case Field::Hy:
                return tuple(mPositionY, mPositionYprime, mPositionZprime);
            case Field::Hz:
                return tuple(mPositionYprime, mPositionYprime, mPositionZ);
        }

        return {};
    }

    boost::optional<rvlm::fdtd::Triple<IndexType>> getSublatticeDims(
            Field field) const {
        auto sublattice = getSublattice(field);
        if (!sublattice)
            return {};

        IndexType nx = std::get<0>(*sublattice).size();
        IndexType ny = std::get<1>(*sublattice).size();
        IndexType nz = std::get<2>(*sublattice).size();
        return std::make_tuple(nx, ny, nz);
    }

private:
    std::vector<T> mPositionX;
    std::vector<T> mPositionY;
    std::vector<T> mPositionZ;
    std::vector<T> mPositionXprime;
    std::vector<T> mPositionYprime;
    std::vector<T> mPositionZprime;

    std::vector<T> mDeltaX;
    std::vector<T> mDeltaY;
    std::vector<T> mDeltaZ;
    std::vector<T> mDeltaXprime;
    std::vector<T> mDeltaYprime;
    std::vector<T> mDeltaZprime;
};

}
}
