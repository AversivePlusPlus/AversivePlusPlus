#ifndef AVERSIVE_STRING_STRING_HPP
#define AVERSIVE_STRING_STRING_HPP

namespace Aversive {
namespace String {

template<class Base, class Derived>
class Interface {};

class String {
protected:
  inline String(void) {}

public:
  inline char operator[](unsigned int i) const;
  inline unsigned int len(void) const;
};

template<class Derived>
class Interface<String, Derived> : public String {
protected:
  inline Interface(void) {}

public:
  inline char operator[](unsigned int i) const {
    return (*(Derived*)this)[i];
  }

  inline unsigned int len(void) const {
    return (*(Derived*)this).len();
  }
};

}
}

#endif//AVERSIVE_STRING_STRING_HPP
