#pragma once
#include <stdexcept>

namespace rvlm {
namespace fdtd {

enum class Field {
    Ex,
    Ey,
    Ez,
    Hx,
    Hy,
    Hz,
    EpsEx,
    EpsEy,
    EpsEz,
    MuHx,
    MuHy,
    MuHz,
    SigmaEx,
    SigmaEy,
    SigmaEz,
    SigmaHx,
    SigmaHy,
    SigmaHz,
};

enum class Axis {
    X,
    Y,
    Z,
};

template <typename TTriple>
auto selectAxis(Axis axis, TTriple const& triple) noexcept
            -> typename std::add_rvalue_reference<decltype(std::get<2>(triple))>::type {

    return selectAxis(axis, std::get<0>(triple),
                            std::get<1>(triple),
                            std::get<2>(triple));
}

template <typename TRef>
TRef const& selectAxis(Axis axis, TRef const& ifX, TRef const& ifY, TRef const& ifZ) noexcept {
    switch (axis) {
        case Axis::X: return ifX;
        case Axis::Y: return ifY;
        case Axis::Z: return ifZ;
    }

    // The above 'switch' has no default branch to let the compiler issue
    // a warning if, suddenly, not every enum constant is covered.
}

}
}
