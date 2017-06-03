#include <boost/tuple/tuple.hpp>
#include <rvlm/fdtd/MemoryMedium.hh>
#include "rvlm/core/Cuboid.hh"
#include "rvlm/fdtd/Domain.hh"
#include "rvlm/fdtd/BasicFdtdBlock.hh"

int main() {

    using namespace rvlm::fdtd;

    IndexType nx = 128, ny = 128, nz = 128;

    Lattice<> lattice(std::make_tuple(nx, ny, nz), std::make_tuple(0.1, 0.1, 0.1));

    MemoryMedium<> medium(lattice);

    Domain<> domain(&lattice, 1, 1, 1);


    auto range = std::make_tuple(HalfOpenIndexRange(0, nx),
                                 HalfOpenIndexRange(0, ny),
                                 HalfOpenIndexRange(0, nz));
    BasicFdtdBlock<> block(lattice, range);
    block.getFieldArray(Field::Ex);

    domain.setBlock(0, 0, 0, &block);

    return 0;
}
