#include "rvlm/fdtd/Domain.hh"
#include "rvlm/fdtd/Block.hh"

int main() {
    using namespace rvlm::fdtd;
    Domain<> domain(1, 1, 1);
    Block<> block();
    return 0;
}
