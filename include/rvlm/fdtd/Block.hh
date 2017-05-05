#pragma once
#include "rvlm/core/Cuboid.hh"
#include "rvlm/core/NonAssignable.hh"
#include "rvlm/core/SolidArray3d.hh"
#include "rvlm/fdtd/Common.hh"
#include "rvlm/fdtd/Domain.hh"

namespace rvlm {
namespace fdtd {

template <typename T>
class Domain;

template <typename T = double>
class Block: public rvlm::core::NonAssignable {
public:

    explicit Block(IndexType nx, IndexType ny, IndexType nz)
        : mFieldEx(nx, ny, nz)
        , mFieldEy(nx, ny, nz)
        , mFieldEz(nx, ny, nz)
        , mFieldHx(nx, ny, nz)
        , mFieldHy(nx, ny, nz)
        , mFieldHz(nx, ny, nz)
        {}

    typedef rvlm::core::SolidArray3d<T> ArrayType;

    Domain<T>* getDomain() const { return mDomain; }

    rvlm::core::Cuboid<T> getBounds() const { return mBounds; }

    ArrayType& getFieldEx() const { return mFieldEx; }

/* construction: */

    void setDomain(Domain<T>* value) { mDomain = value; }
    void setBounds(core::Cuboid<T> const& value) { mBounds = value; }

private:

    Domain<T>* mDomain;

    rvlm::core::Cuboid<T> mBounds;

    ArrayType mFieldEx;
    ArrayType mFieldEy;
    ArrayType mFieldEz;
    ArrayType mFieldHx;
    ArrayType mFieldHy;
    ArrayType mFieldHz;
    // ArrayType mMaterialEpsEx;
    // ArrayType mMaterialEpsEy;
    // ArrayType mMaterialEpsEz;
    // ArrayType mMaterialMuHx;
    // ArrayType mMaterialMuHy;
    // ArrayType mMaterialMuHz;
    // ArrayType mMaterialSigmaEx;
    // ArrayType mMaterialSigmaEy;
    // ArrayType mMaterialSigmaEz;
    // ArrayType mMaterialSigmaHx;
    // ArrayType mMaterialSigmaHy;
    // ArrayType mMaterialSigmaHz;
};

} // namespace fdtd
} // namespace rvlm
