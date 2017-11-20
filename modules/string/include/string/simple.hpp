#ifndef AVERSIVE_STRING_SIMPLE_HPP
#define AVERSIVE_STRING_SIMPLE_HPP

#include "string.hpp"
#include <string.h>

namespace Aversive {
namespace String {

class SimpleString : public Interface<String, SimpleString> {
private:
  const char* _data;

public:
  inline SimpleString(const char* data)
    : _data(data) {
  }

public:
  inline char operator[](unsigned int i) const {
    return _data[i];
  }

  inline unsigned int len(void) const {
    return strlen(_data);
  }
};

}
}

#endif//AVERSIVE_STRING_SIMPLE_HPP
