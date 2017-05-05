#pragma once

#include <vector>
#include "rvlm/core/SolidArray3d.hh"
#include "rvlm/fdtd/Block.hh"
#include "rvlm/fdtd/Common.hh"
#include "rvlm/fdtd/Lattice.hh"
#include "rvlm/fdtd/Probe.hh"
#include "rvlm/fdtd/Source.hh"

namespace rvlm {
namespace fdtd {

template <typename T>
class Block;
template <typename T>
class Probe;

template <typename T=double>
class Domain {
public:

    Domain(Lattice<T> const* lattice, IndexType nx, IndexType ny, IndexType nz)
        : mBlocks(nx, ny, nz, nullptr) {
    }

    Block<T>* getBlock(IndexType ix, IndexType iy, IndexType iz) const {
        return mBlocks.at(ix, iy, iz);
    }

    void setBlock(IndexType ix, IndexType iy, IndexType iz, Block<T>* block) {
        mBlocks.at(ix, iy, iz) = block;
        block->setDomain(this);
    }

    Lattice<T> const* getLattice() const { return mLattice; }

    void setLattice(Lattice<T> const* lattice) {
        mLattice = lattice;
    }

private:
    Lattice<T> const* mLattice;

    rvlm::core::SolidArray3d<Block<T>*, IndexType> mBlocks;
    std::vector<Probe<T>*>  mProbes;
    std::vector<Source<T>*> mSources;
};

}
}