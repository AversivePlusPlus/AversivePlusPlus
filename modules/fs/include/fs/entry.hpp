#ifndef AVERSIVE_FS_ENTRY_HPP
#define AVERSIVE_FS_ENTRY_HPP

#include "file.hpp"

#include <string.h>

namespace Aversive {
namespace fs {

class Entry {
protected:
  const char* _name;

protected:
  Entry(const char* name)
    : _name(name) {
  }

public:
  inline const char* name(void) {
    return _name;
  }
};

}
}

#endif//AVERSIVE_FS_ENTRY_HPP
