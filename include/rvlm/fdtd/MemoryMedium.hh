#pragma once
#include "rvlm/core/Constants.hh"
#include "rvlm/fdtd/Medium.hh"
#include "rvlm/fdtd/Lattice.hh"

namespace rvlm {
namespace fdtd {

template<typename T=double>
class MemoryMedium: public Medium<T> {
public:

    using Const = rvlm::core::Constants<T>;

    MemoryMedium(Lattice<T> const& lattice)
        : mMaterialEpsEx  (lattice.getDimensions(), Const::EPS_0())
        , mMaterialEpsEy  (lattice.getDimensions(), Const::EPS_0())
        , mMaterialEpsEz  (lattice.getDimensions(), Const::EPS_0())
        , mMaterialMuHx   (lattice.getDimensions(), Const::MU_0())
        , mMaterialMuHy   (lattice.getDimensions(), Const::MU_0())
        , mMaterialMuHz   (lattice.getDimensions(), Const::MU_0())
        , mMaterialSigmaEx(lattice.getDimensions(), T(0))
        , mMaterialSigmaEy(lattice.getDimensions(), T(0))
        , mMaterialSigmaEz(lattice.getDimensions(), T(0))
        , mMaterialSigmaHx(lattice.getDimensions(), T(0))
        , mMaterialSigmaHy(lattice.getDimensions(), T(0))
        , mMaterialSigmaHz(lattice.getDimensions(), T(0))
        {}

    virtual
    boost::optional<T> get(Field field, Indices const& position) const override{
        auto array = getArray(field);
        if (!array)
            return {};

        auto ix = std::get<0>(position);
        auto iy = std::get<1>(position);
        auto iz = std::get<2>(position);

        // TODO: Check index bounds.
        return array.get().at(ix, iy, iz);
    }

    virtual
    bool retrieve(Field field, IndicesRange const& range,
              ArrayType<T>& destination, Indices const& origin) const override {

        auto array = getArray(field);
        if (!array)
            return false;

        auto rangeX = std::get<0>(range);
        auto rangeY = std::get<1>(range);
        auto rangeZ = std::get<2>(range);

        // TODO: Check index bounds.
        for (auto ix: rangeX)
        for (auto iy: rangeY)
        for (auto iz: rangeZ)
            destination.at(ix, iy, iz) = array->at(ix, iy, iz);

        return true;
    }


    T& at(Field field, IndexType ix, IndexType iy, IndexType iz) {
        // TODO: Check 'field' and index bounds.
        return getArray(field).get().at(ix, iy, iz);
    }

private:

    boost::optional<ArrayType<T>&> getArray(Field field) {
        switch (field) {
            case Field::EpsEx:   return mMaterialEpsEx;
            case Field::EpsEy:   return mMaterialEpsEy;
            case Field::EpsEz:   return mMaterialEpsEz;
            case Field::MuHx:    return mMaterialMuHx;
            case Field::MuHy:    return mMaterialMuHy;
            case Field::MuHz:    return mMaterialMuHz;
            case Field::SigmaEx: return mMaterialSigmaEx;
            case Field::SigmaEy: return mMaterialSigmaEy;
            case Field::SigmaEz: return mMaterialSigmaEz;
            case Field::SigmaHx: return mMaterialSigmaHx;
            case Field::SigmaHy: return mMaterialSigmaHy;
            case Field::SigmaHz: return mMaterialSigmaHz;
            default:             return {};
        }
    }

    boost::optional<ArrayType<T> const&> getArray(Field field) const {
        auto array = getArray(field);
        if (!array)
            return {};

        // Single const_cast is a nice alternative to repeating the whole
        // switch statement from the above function.
        return const_cast<ArrayType<T> const&>(array.get());
    }

    ArrayType<T> mMaterialEpsEx;
    ArrayType<T> mMaterialEpsEy;
    ArrayType<T> mMaterialEpsEz;
    ArrayType<T> mMaterialMuHx;
    ArrayType<T> mMaterialMuHy;
    ArrayType<T> mMaterialMuHz;
    ArrayType<T> mMaterialSigmaEx;
    ArrayType<T> mMaterialSigmaEy;
    ArrayType<T> mMaterialSigmaEz;
    ArrayType<T> mMaterialSigmaHx;
    ArrayType<T> mMaterialSigmaHy;
    ArrayType<T> mMaterialSigmaHz;
};

}
}
