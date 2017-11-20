#include <container/simple/stack.hpp>
#include <container/utils/test.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Container::Simple;
using namespace Aversive::Container::Test;

static const unsigned int SIZE = 10;

int main(int, char**) {
  static_assert(test_interface<Aversive::Container::Container, Stack<u8, SIZE>>(), "ERROR : Class don't follow the Container interface");
  static_assert(test_interface<Aversive::Container::Flushable, Stack<u8, SIZE>>(), "ERROR : Class don't follow the Flushable interface");
  static_assert(test_interface<Aversive::Container::Headed, Stack<u8, SIZE>>(), "ERROR : Class don't follow the Headed interface");
  static_assert(test_interface<Aversive::Container::Stack, Stack<u8, SIZE>>(), "ERROR : Class don't follow the Stack interface");
  static_assert(test_interface<Aversive::Container::Limited, Stack<u8, SIZE>>(), "ERROR : Class don't follow the Limited interface");
  
  Stack<u8, SIZE> s(10, 5, 8, 20);
  
  myAssert(s.head() == 20, "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
  myAssert(s.size() == 4, "Line " S__LINE__": Stack<SIZE, u8>::size(void).");
  myAssert(s.limit() == SIZE, "Line " S__LINE__": Stack<SIZE, u8>::limit(void).");
  //myAssert(s.push(12), "Line " S__LINE__": Stack<SIZE, u8>::push(u8).");
  s.push(12);
  myAssert(s.size() == 5, "Line " S__LINE__": Stack<SIZE, u8>::size(void).");
  //myAssert(s.push(2), "Line " S__LINE__": Stack<SIZE, u8>::push(u8).");
  s.push(2);
  myAssert(s.head() == 2, "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
  //myAssert(s.pop(), "Line " S__LINE__": Stack<SIZE, u8>::pop(void).");
  s.pop();
  myAssert(s.head() == 12, "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
  myAssert(!s.full(), "Line " S__LINE__": Stack<SIZE, u8>::full(void).");
  myAssert(!s.empty(), "Line " S__LINE__": Stack<SIZE, u8>::empty(void).");
  
  s.flush();
  
  myAssert(s.size() == 0, "Line " S__LINE__": Stack<SIZE, u8>::flush(void).");
  for(Stack<u8, SIZE>::Index i = 0; i < 5; i++) {
    //myAssert(s.push(10 + i), "Line " S__LINE__": Stack<SIZE, u8>::push(u8).");
    s.push(10 + i);
  }
  
  myAssert(s.size() == 5, "Line " S__LINE__": Stack<SIZE, u8>::size(void).");
  for(int i = 4; i >= 0; i--) {
    myAssert(s.head() == (10 + i), "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
    //myAssert(s.pop(), "Line " S__LINE__": Stack<SIZE, u8>::pop(void).");
    s.pop();
    myAssert(s.size() == (Stack<u8, SIZE>::Index) i, "Line " S__LINE__": Stack<SIZE, u8>::size(void).");
  }
  
  std::cout << "OK" << std::endl;
  return 0;
}
