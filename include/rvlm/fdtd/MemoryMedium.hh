#pragma once
#include "rvlm/fdtd/Medium.hh"
#include "rvlm/fdtd/Lattice.hh"

namespace rvlm {
namespace fdtd {

template<typename T=double>
class MemoryMedium {
public:

    MemoryMedium(Lattice<T> const& lattice)
        : mMaterialEpsEx  (lattice.getSublatticeDimensions(Field::Ex).get())
        , mMaterialEpsEy  (lattice.getSublatticeDimensions(Field::Ey).get())
        , mMaterialEpsEz  (lattice.getSublatticeDimensions(Field::Ez).get())
        , mMaterialMuHx   (lattice.getSublatticeDimensions(Field::Hx).get())
        , mMaterialMuHy   (lattice.getSublatticeDimensions(Field::Hy).get())
        , mMaterialMuHz   (lattice.getSublatticeDimensions(Field::Hz).get())
        , mMaterialSigmaEx(lattice.getSublatticeDimensions(Field::Ex).get())
        , mMaterialSigmaEy(lattice.getSublatticeDimensions(Field::Ey).get())
        , mMaterialSigmaEz(lattice.getSublatticeDimensions(Field::Ez).get())
        , mMaterialSigmaHx(lattice.getSublatticeDimensions(Field::Hx).get())
        , mMaterialSigmaHy(lattice.getSublatticeDimensions(Field::Hy).get())
        , mMaterialSigmaHz(lattice.getSublatticeDimensions(Field::Hz).get())
        {}

    virtual boost::optional<T> get(Field field, Indices const& position) const {
        auto array = getArray(field);
        if (!array)
            return {};

        return array.get().at(position.getX(), position.getY(), position.getZ());
    }

    virtual bool retrieve(Field field, IndicesRange range,
                       ArrayType<T>& destination, Indices const& origin) const {

        return false;
    }

private:

    boost::optional<ArrayType<T> const&> getArray(Field field) const {
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
