#include <base/array.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Base;

using index_t = Array<u8, 0>::IndexType;
static const index_t SIZE = 5;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Array<u8, SIZE> a1(42);
  myAssert(a1[0] == 42, "Line " S__LINE__ ": Variadic Array construction.");
  for(index_t i = 1; i < a1.SIZE; i++) {
    myAssert(a1[i] == 0, "Line " S__LINE__ ": Variadic Array construction.");
  }
  
  Array<u8, SIZE> a2(1, 2);
  myAssert(a2[0] == 1 && a2[1] == 2, "Line " S__LINE__ ": Variadic Array construction.");
  
  for(index_t i = 3; i < a2.SIZE; i++) {
    myAssert(a2[i] == 0, "Line " S__LINE__ ": Variadic Array construction.");
  }
  
  a1 = 0;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 0, "Line " S__LINE__ ": Array value assignment.");
  }
  
  a1 += 2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 2, "Line " S__LINE__ ": Array<u8, SIZE>::operator+=(u8).");
  }
  
  a1 -= 1;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 1, "Line " S__LINE__ ": Array<u8, SIZE>::operator-=(u8).");
  }
  
  a1 *= 5;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 5, "Line " S__LINE__ ": Array<u8, SIZE>::operator*=(u8).");
  }
  
  a1 /= 2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 2, "Line " S__LINE__ ": Array<u8, SIZE>::operator/=(u8).");
  }
  
  a1 %= 2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 0, "Line " S__LINE__ ": Array<u8, SIZE>::operator%=(u8).");
  }
  
  a1 = 1;
  a2 = 1;
  a1 = a1 + a2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 2, "Line " S__LINE__ ": Array<u8, SIZE>::operator+(Array).");
  }
  
  a2 = 2;
  a1 = a1 - a2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 0, "Line " S__LINE__ ": Array<u8, SIZE>::operator-(Array).");
  }
  
  a1 = 1;
  a2 = 5;
  a1 = a1 * a2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 5, "Line " S__LINE__ ": Array<u8, SIZE>::operator*(Array).");
  }
  
  a2 = 2;
  a1 = a1 / a2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 2, "Line " S__LINE__ ": Array<u8, SIZE>::operator/(Array).");
  }
  
  a1 = a1 % a2;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a1[i] == 0, "Line " S__LINE__ ": Array<u8, SIZE>::operator%(Array).");
  }
  
  myAssert(!(sizeof(Array<bool, SIZE>) >= sizeof(Array<u8, SIZE>)),
           "Line " S__LINE__ ": A boolean Array is not lighter than a byte Array even though it should have a bool specialisation.");
  
  Array<bool, SIZE> a3(true, true, false, true, false);
  
  myAssert(!(a3[0] != true || a3[1] != true || a3[2] != false || a3[3] != true || a3[4] != false),
           "Line " S__LINE__ ": Boolean Array construction then element access.");
  
  a3 = false;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a3[i] == false, "Line " S__LINE__ ": Boolean Array value assignment.");
  }
  
  a3 += true;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a3[i] == (bool) (false + true), "Line " S__LINE__ ": Array<bool, SIZE>::operator+=(bool).");
  }
  
  a3 = true;
  a3 -= false;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a3[i] == (bool) (true - false), "Line " S__LINE__ ": Array<bool, SIZE>::operator-=(bool).");
  }
  
  a3 = false;
  a3 /= true;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a3[i] == (bool) (false / true), "Line " S__LINE__ ": Array<bool, SIZE>::operator/=(bool).");
  }
  
  a3 = true;
  a3 *= false;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a3[i] == (bool) (true * false), "Line " S__LINE__ ": Array<bool, SIZE>::operator*=(bool).");
  }
  
  a3 = true;
  a3 %= true;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a3[i] == (bool) (true % true), "Line " S__LINE__ ": Array<bool, SIZE>::operator%=(bool).");
  }
  
  Array<bool, SIZE> a4;
  a3 = true;
  a4 = false;
  a4 = a3 + a4;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a4[i] == (bool) (true + false), "Line " S__LINE__ ": Array<bool, SIZE>::operator+(Array).");
  }
  
  a4 = a3 - false;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a4[i] == (bool) (true - false), "Line " S__LINE__ ": Array<bool, SIZE>::operator-(Array).");
  }
  
  a4 = a3 * false;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a4[i] == (bool) (true * false), "Line " S__LINE__ ": Array<bool, SIZE>::operator*(Array).");
  }
  
  a4 = a3 / true;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a4[i] == (bool) (true / true), "Line " S__LINE__ ": Array<bool, SIZE>::operator/(Array).");
  }
  
  a4 = a3 % true;
  for(index_t i = 0; i < SIZE; i++) {
    myAssert(a4[i] == (bool) (true % true), "Line " S__LINE__ ": Array<bool, SIZE>::operator%(Array).");
  }
  
  std::cout << "OK" << std::endl;
  return 0;
}
