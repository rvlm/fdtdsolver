#pragma once
#include "rvlm/fdtd/Block.hh"

namespace rvlm {
namespace fdtd {

template <typename T = double>
class BasicFdtdBlock: public Block {
public:

    explicit BasicFdtdBlock(IndicesRange const& presentIndices)
            : Block(presentIndices) {}

    virtual boost::optional<ArrayType<T>&> getFieldArray(Field field) {

    }

private:

    ArrayType<T> mFieldEx;
    ArrayType<T> mFieldEy;
    ArrayType<T> mFieldEz;
    ArrayType<T> mFieldHx;
    ArrayType<T> mFieldHy;
    ArrayType<T> mFieldHz;
    ArrayType<T> mCoefficientCaEx;
    ArrayType<T> mCoefficientCaEy;
    ArrayType<T> mCoefficientCaEz;
    ArrayType<T> mCoefficientCbEx;
    ArrayType<T> mCoefficientCbEy;
    ArrayType<T> mCoefficientCbEz;
    ArrayType<T> mCoefficientDaHx;
    ArrayType<T> mCoefficientDaHy;
    ArrayType<T> mCoefficientDaHz;
    ArrayType<T> mCoefficientDbHx;
    ArrayType<T> mCoefficientDbHy;
    ArrayType<T> mCoefficientDbHz;
};

} // namespace fdtd
} // namespace rvlm
