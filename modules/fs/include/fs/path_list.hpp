#ifndef AVERSIVE_FS_PATH_LIST_HPP
#define AVERSIVE_FS_PATH_LIST_HPP

#include "path.hpp"

namespace Aversive {
namespace fs {

template<class Entry>
class PathList {
public:
  unsigned int size(void) {
    return 0;
  }

  Path<Entry> operator[](unsigned int index) {
    return Path<Entry>(*(Entry*)this, index);
  }
};

}
}

#endif//AVERSIVE_FS_PATH_LIST_HPP
