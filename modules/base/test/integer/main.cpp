#include <base/integer.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Base;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  myAssert(sizeof(u8)  == 1, "Line " S__LINE__ ": sizeof(u8) != 1.");
  myAssert(sizeof(s8)  == 1, "Line " S__LINE__ ": sizeof(s8) != 1.");
  myAssert(sizeof(u16) == 2, "Line " S__LINE__ ": sizeof(u16) != 2.");
  myAssert(sizeof(s16) == 2, "Line " S__LINE__ ": sizeof(s16) != 2.");
  myAssert(sizeof(u32) == 4, "Line " S__LINE__ ": sizeof(u32) != 4.");
  myAssert(sizeof(s32) == 4, "Line " S__LINE__ ": sizeof(s32) != 4.");
  myAssert(sizeof(u64) == 8, "Line " S__LINE__ ": sizeof(u64) != 8.");
  myAssert(sizeof(s64) == 8, "Line " S__LINE__ ": sizeof(s64) != 8.");
  myAssert(sizeof(ssys) == sizeof(usys), "Line " S__LINE__ ": sizeof(ssys) != sizeof(usys).");
  myAssert(sizeof(usys) == sizeof(void*), "Line " S__LINE__ ": sizeof(usys) != sizeof(void*).");
  
  std::cout << "OK" << std::endl;
  return 0;
}
