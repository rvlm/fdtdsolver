#pragma once

#include <boost/optional.hpp>
#include "rvlm/fdtd/Common.hh"
#include "rvlm/fdtd/Field.hh"

namespace rvlm {
namespace fdtd {

template<typename T=double>
class Medium {
public:

    virtual boost::optional<T> get(Field field, Indices const& position) const {
        return {};
    }

    virtual bool retrieve(Field field, IndicesRange range,
                       ArrayType<T>& destination, Indices const& origin) const {

        return false;
    }
};

}
}
