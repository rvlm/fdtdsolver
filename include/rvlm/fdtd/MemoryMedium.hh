#pragma once
#include "rvlm/core/Constants.hh"
#include "rvlm/fdtd/Medium.hh"
#include "rvlm/fdtd/Lattice.hh"

namespace rvlm {
namespace fdtd {

#if 0
template<typename T=double>
class MemoryMedium {
public:

    using Const = rvlm::core::Constants<T>;

    MemoryMedium(Lattice<T> const& lattice)
        : mMaterialEpsEx  (lattice.getSublatticeDims(Field::Ex).get(), Const::EPS_0())
        , mMaterialEpsEy  (lattice.getSublatticeDims(Field::Ey).get(), Const::EPS_0())
        , mMaterialEpsEz  (lattice.getSublatticeDims(Field::Ez).get(), Const::EPS_0())
        , mMaterialMuHx   (lattice.getSublatticeDims(Field::Hx).get(), Const::MU_0())
        , mMaterialMuHy   (lattice.getSublatticeDims(Field::Hy).get(), Const::MU_0())
        , mMaterialMuHz   (lattice.getSublatticeDims(Field::Hz).get(), Const::MU_0())
        , mMaterialSigmaEx(lattice.getSublatticeDims(Field::Ex).get())
        , mMaterialSigmaEy(lattice.getSublatticeDims(Field::Ey).get())
        , mMaterialSigmaEz(lattice.getSublatticeDims(Field::Ez).get())
        , mMaterialSigmaHx(lattice.getSublatticeDims(Field::Hx).get())
        , mMaterialSigmaHy(lattice.getSublatticeDims(Field::Hy).get())
        , mMaterialSigmaHz(lattice.getSublatticeDims(Field::Hz).get())
        {}

    virtual boost::optional<T> get(Field field, Indices const& position) const {
        auto array = getArray(field);
        if (!array)
            return {};

        // TODO: Check index bounds.
        return array.get().at(position.getX(), position.getY(), position.getZ());
    }

    virtual bool retrieve(Field field, IndicesRange range,
                       ArrayType<T>& destination, Indices const& origin) const {

        auto array = getArray(field);
        if (!array)
            return false;

        // TODO: Make these for loops not so ugly.
        // TODO: Check index bounds.
        for (IndexType ixSrc=range.getX1(), ixDst=origin.getX(); ixSrc<range.getX2(); ++ixSrc, ++ixDst)
        for (IndexType iySrc=range.getY1(), iyDst=origin.getY(); iySrc<range.getY2(); ++iySrc, ++iyDst)
        for (IndexType izSrc=range.getZ1(), izDst=origin.getZ(); izSrc<range.getZ2(); ++izSrc, ++izDst)
            destination.at(ixDst, iyDst, izDst) = array->at(ixSrc, iySrc, izSrc);

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
#endif

}
}
