#ifndef AVERSIVE_STRING_COMPIL_HPP
#define AVERSIVE_STRING_COMPIL_HPP

#include "string.hpp"
#include <string.h>

namespace Aversive {
namespace String {

template<char... CHARS>
class CompilString : public Interface<String, CompilString<CHARS...>> {
private:
  template<char ARG1, char... ARGS>
  struct Helper {
    static constexpr inline char get(unsigned int i) {
      return (i == 0) ? ARG1 : Helper<ARGS...>::get(i-1);
    }

    static constexpr inline unsigned int len(void) {
      return 1+Helper<ARGS...>::len();
    }
  };

  template<char ARG1>
  struct Helper<ARG1> {
    static constexpr inline char get(unsigned int i) {
      return (i == 0) ? ARG1 : 0;
    }

    static constexpr inline unsigned int len(void) {
      return 1;
    }
  };

public:
  inline CompilString(void) {}

public:
  inline char operator[](unsigned int i) const {
    return Helper<CHARS...>::get(i);
  }

  inline unsigned int len(void) const {
    return Helper<CHARS...>::len();
  }
};

}
}

#endif//AVERSIVE_STRING_COMPIL_HPP
