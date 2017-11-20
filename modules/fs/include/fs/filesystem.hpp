#ifndef AVERSIVE_FS_FILESYSTEM_HPP
#define AVERSIVE_FS_FILESYSTEM_HPP

#include "flags.hpp"
#include "file.hpp"

namespace Aversive {
namespace fs {

class FileSystem {
protected:
  inline FileSystem(void) {}

public:
  inline File open(const char* path);
};

}
}

#endif//AVERSIVE_FS_FILESYSTEM_HPP
