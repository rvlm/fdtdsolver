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

    explicit Block(IndicesRange const& presentIndices)
        : mPresentIndices(presentIndices) {}

    virtual ~Block() {}

    Domain<T>* getDomain() const { return mDomain; }

    rvlm::core::Cuboid<T> getPresentIndices() const { return mPresentIndices; }

    virtual boost::optional<ArrayType<T>&> getFieldArray(Field field) {
        return {};
    }

private:

    void setDomain(Domain<T>* value) { mDomain = value; }

    Domain<T>* mDomain;
    rvlm::core::Cuboid<IndexType> mPresentIndices;

    friend class Domain<T>;
};

} // namespace fdtd
} // namespace rvlm
