#include <container/stack.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Container;
using my_stack_t = Aversive::Container::stack_t;

static const my_stack_t SIZE = 10;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Stack<SIZE, u8> s(10, 5, 8, 20);
  
  myAssert(s.head() == 20, "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
  myAssert(s.usedSpace() == 4, "Line " S__LINE__": Stack<SIZE, u8>::usedSpace(void).");
  myAssert(s.freeSpace() == (SIZE - s.usedSpace()), "Line " S__LINE__": Stack<SIZE, u8>::freeSpace(void).");
  myAssert(s.push(12), "Line " S__LINE__": Stack<SIZE, u8>::push(u8).");
  myAssert(s.usedSpace() == 5, "Line " S__LINE__": Stack<SIZE, u8>::usedSpace(void).");
  myAssert(s.push(2), "Line " S__LINE__": Stack<SIZE, u8>::push(u8).");
  myAssert(s.head() == 2, "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
  myAssert(s.pop(), "Line " S__LINE__": Stack<SIZE, u8>::pop(void).");
  myAssert(s.head() == 12, "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
  myAssert(!s.isFull(), "Line " S__LINE__": Stack<SIZE, u8>::isFull(void).");
  myAssert(!s.isEmpty(), "Line " S__LINE__": Stack<SIZE, u8>::isEmpty(void).");
  
  s.flush();
  
  myAssert(s.usedSpace() == 0, "Line " S__LINE__": Stack<SIZE, u8>::flush(void).");
  for(my_stack_t i = 0; i < 5; i++) {
    myAssert(s.push(10 + i), "Line " S__LINE__": Stack<SIZE, u8>::push(u8).");
  }
  
  myAssert(s.usedSpace() == 5, "Line " S__LINE__": Stack<SIZE, u8>::usedSpace(void).");
  for(int i = 4; i >= 0; i--) {
    myAssert(s.head() == (10 + i), "Line " S__LINE__": Stack<SIZE, u8>::head(void).");
    myAssert(s.pop(), "Line " S__LINE__": Stack<SIZE, u8>::pop(void).");
    myAssert(s.usedSpace() == (my_stack_t) i, "Line " S__LINE__": Stack<SIZE, u8>::usedSpace(void).");
  }
  
  std::cout << "OK" << std::endl;
  return 0;
}
