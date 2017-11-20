#ifndef MY_ASSERT_HPP
#define MY_ASSERT_HPP

#include <cstdlib>
#include <iostream>

#define S(x) #x
#define S_(x) S(x)
#define S__LINE__ S_(__LINE__)

inline void myAssert(bool test, const char* msg) {
  if(!test) {
    std::cout << msg << std::endl;
    exit(1);
  }
}   

#endif//MY_ASSERT_HPP
