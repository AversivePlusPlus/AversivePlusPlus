#ifndef AVERSIVE_FS_FLAGS_HPP
#define AVERSIVE_FS_FLAGS_HPP

namespace Aversive {
namespace fs {

template<unsigned int FLAGS>
struct FlagsType {
  operator unsigned int (void) {
    return FLAGS;
  }
};

static constexpr FlagsType<0x01> READ   = {};
static constexpr FlagsType<0x02> WRITE  = {};
static constexpr FlagsType<0x04> CREATE = {};

}
}

#endif//AVERSIVE_FS_FLAGS_HPP
