#include <base/bool_ref.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Base;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  bool b1 = true;
  BoolRef r1(b1);
  
  myAssert(r1, "Line " S__LINE__ ": Construction to reference a bool, r1 should be true.");
  
  r1 = false;
  
  myAssert(!r1 && !b1, "Line " S__LINE__ ": Reference problem, r1 and b1 should be false.");
  
  BoolRef r2(r1);
  
  myAssert(!r1 && !r2 && !b1, "Line " S__LINE__ ": Copy construction, r1, r2 and b1 should be false.");
  
  r2 = true;
  
  myAssert(r1 && r2 && b1, "Line " S__LINE__ ": Reference problem, r1, r2 and b1 should be true.");
  
  u8 b2 = 0xF0;
  
  for(int i = 0; i < 4; i++) {
    BoolRef r(b2, i);
    myAssert(!r, "Line " S__LINE__ ": Construction to reference a bit within a byte, r should be false.");
    r = !r;
  }
  
  for(int i = 4; i < 8; i++) {
    BoolRef r(b2, i);
    myAssert(r, "Line " S__LINE__ ": Construction to reference a bit within a byte, r should be true.");
    r = !r;
  }
  
  myAssert(b2 == 0x0F, "Line " S__LINE__ ": Reference to a bit within a byte problem, b2 must be equal to 0x0F.");
  
  r1 = true;
  r1 += true;
  myAssert(r1 == (bool) (true + true), "Line " S__LINE__ ": += operator problem.");
  
  r1 = true;
  r1 -= true;
  myAssert(r1 == (bool) (true - true), "Line " S__LINE__ ": -= operator problem.");
  
  r1 = true;
  r1 *= false;
  myAssert(r1 == (bool) (true * false), "Line " S__LINE__ ": *= operator problem.");
  
  r1 = true;
  r1 /= true;
  myAssert(r1 == (bool) (true / true), "Line " S__LINE__ ": /= operator problem.");
  
  r1 = true;
  r1 %= true;
  myAssert(r1 == (bool) (true % true), "Line " S__LINE__ ": %= operator problem.");
  
  std::cout << "OK" << std::endl;
  return 0;
}
