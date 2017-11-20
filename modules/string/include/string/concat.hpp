#ifndef AVERSIVE_STRING_CONCAT_HPP
#define AVERSIVE_STRING_CONCAT_HPP

#include "string.hpp"
#include <string.h>

namespace Aversive {
namespace String {

template<class String1, class String2>
class ConcatString : public Interface<String, ConcatString<String1, String2>> {
private:
  const String1& _first;
  const String2& _second;

public:
  inline ConcatString(const String1& first, const String2& second)
    : _first(first), _second(second) {
  }

public:
  inline char operator[](unsigned int i) const {
    const unsigned int first_len = _first.len();
    if(i < first_len) {
      return _first[i];
    }
    else {
      return _second[i-first_len];
    }
  }

  inline unsigned int len(void) const {
    return _first.len() + _second.len();
  }
};

template<class String1, class String2>
ConcatString<String1, String2> concat(const String1& s1, const String2& s2) {
  return ConcatString<String1, String2>(s1,s2);
}

}
}

#endif//AVERSIVE_STRING_CONCAT_HPP
