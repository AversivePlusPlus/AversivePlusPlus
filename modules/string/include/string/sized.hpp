#ifndef AVERSIVE_STRING_SIZED_HPP
#define AVERSIVE_STRING_SIZED_HPP

#include "string.hpp"
#include <string.h>

namespace Aversive {
namespace String {

class SizedString : public Interface<String, SizedString> {
private:
  const char* _data;
  unsigned int _size;

public:
  inline SizedString(const char* data, unsigned int size)
    : _data(data), _size(size) {
  }

public:
  inline char operator[](unsigned int i) const {
    return _data[i];
  }

  inline unsigned int len(void) const {
    return strnlen(_data, _size);
  }
};

}
}

#endif//AVERSIVE_STRING_SIZED_HPP
