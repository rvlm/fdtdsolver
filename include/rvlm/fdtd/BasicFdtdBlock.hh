#pragma once
#include <boost/optional.hpp>
#include "rvlm/fdtd/Common.hh"
#include "rvlm/fdtd/Field.hh"
#include "rvlm/fdtd/Lattice.hh"
#include "rvlm/fdtd/Block.hh"

namespace rvlm {
namespace fdtd {

template <typename T=double>
class BasicFdtdBlock: public Block<T> {
public:

    using Const = rvlm::core::Constants<T>;

    BasicFdtdBlock(Lattice<T> const& lattice,
                   Triple<HalfOpenIndexRange> const& presentIndices)
        : Block<T>(presentIndices)
        , mFieldEx(expandRangePlus(presentIndices),  T(0))
        , mFieldEy(expandRangePlus(presentIndices),  T(0))
        , mFieldEz(expandRangePlus(presentIndices),  T(0))
        , mFieldHx(expandRangeMinus(presentIndices), T(0))
        , mFieldHy(expandRangeMinus(presentIndices), T(0))
        , mFieldHz(expandRangeMinus(presentIndices), T(0)) {}

    virtual boost::optional<fdtd::ArrayType<T>&> getFieldArray(Field field) {
        switch (field) {
            case Field::Ex: return mFieldEx;
            case Field::Ey: return mFieldEy;
            case Field::Ez: return mFieldEz;
            case Field::Hx: return mFieldHx;
            case Field::Hy: return mFieldHy;
            case Field::Hz: return mFieldHz;
            default:        return {};
        }
    }

    virtual void startSimulation() override {

    }

    virtual void simulateTimeStep(T const& deltaT) override {

    }

    virtual void stopSimulation() override {

    }

private:

    ArrayType<T> mFieldEx;
    ArrayType<T> mFieldEy;
    ArrayType<T> mFieldEz;
    ArrayType<T> mFieldHx;
    ArrayType<T> mFieldHy;
    ArrayType<T> mFieldHz;
    /*
    ArrayType<T> mCoefficientCaEx;
    ArrayType<T> mCoefficientCaEy;
    ArrayType<T> mCoefficientCaEz;
    ArrayType<T> mCoefficientCbEx;
    ArrayType<T> mCoefficientCbEy;
    ArrayType<T> mCoefficientCbEz;
    ArrayType<T> mCoefficientDaHx;
    ArrayType<T> mCoefficientDaHy;
    ArrayType<T> mCoefficientDaHz;
    ArrayType<T> mCoefficientDbHx;
    ArrayType<T> mCoefficientDbHy;
    ArrayType<T> mCoefficientDbHz;
     */
};

} // namespace fdtd
} // namespace rvlm
