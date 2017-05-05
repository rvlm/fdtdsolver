#include <rvlm/fdtd/MemoryMedium.hh>
#include "rvlm/core/Cuboid.hh"
#include "rvlm/fdtd/Domain.hh"
#include "rvlm/fdtd/Block.hh"

int main() {
    using namespace rvlm::fdtd;

    IndexType nx = 128, ny = 128, nz = 128;

    Lattice<> lattice(nx, ny, nz, 0.01);
    lattice.getSublattice(Field::Ex);

    MemoryMedium<> medium(lattice);

    Domain<> domain(&lattice, 1, 1, 1);


    IndicesRange range = {0,0,0, nx, ny, nz};
    Block<> block(range);
    block.getFieldArray(Field::Ex);

    domain.setBlock(0, 0, 0, &block);

    return 0;
}
