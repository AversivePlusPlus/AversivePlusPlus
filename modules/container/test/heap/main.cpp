#include <container/simple/heap.hpp>
#include <container/utils/test.hpp>
#include <iostream>
#include <base/integer.hpp>
#include "../my_assert.hpp"

using namespace Aversive::Container::Simple;
using namespace Aversive::Container::Test;

static const unsigned int DATA_SIZE = 4;
static const unsigned int SIZE = 8;
char t[] = { 13, 15, 12, 10 };

int main(int, char**) {
  static_assert(test_interface<Aversive::Container::Container, Heap<u8, SIZE>>(), "ERROR : Class don't follow the Container interface");
  static_assert(test_interface<Aversive::Container::Flushable, Heap<u8, SIZE>>(), "ERROR : Class don't follow the Flushable interface");
  static_assert(test_interface<Aversive::Container::Headed, Heap<u8, SIZE>>(), "ERROR : Class don't follow the Headed interface");
  static_assert(test_interface<Aversive::Container::Stack, Heap<u8, SIZE>>(), "ERROR : Class don't follow the Stack interface");
  static_assert(test_interface<Aversive::Container::Limited, Heap<u8, SIZE>>(), "ERROR : Class don't follow the Limited interface");
  
  Heap<s8, SIZE> h(0, 1, 2, 3, 4, 5, 6, 7);
  
  myAssert(h.full(), "Line " S__LINE__": Heap<SIZE, s8>::full(void).");
  myAssert(!h.empty(), "Line " S__LINE__": Heap<SIZE, s8>::empty(void).");
  myAssert(h.size() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
  myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  
  for(s8 i = 7; i >= 0; i--) {
    myAssert(h.head() == i, "Line " S__LINE__": Heap<SIZE, s8>::head(void).");
    //myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
    h.pop();
    myAssert(h.size() == i, "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
    myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  }
  
  h.flush();
  
  myAssert(h.size() == 0, "Line " S__LINE__": Heap<SIZE, s8>::flush(void).");
  myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::flush(void).");
  
  for(Heap<s8, SIZE>::Index i = 0; i < DATA_SIZE; i++) {
    //myAssert(h.push(t[i]), "Line " S__LINE__": Heap<SIZE, s8>::push(ElementType).");
    h.push(t[i]);
  }
  
  myAssert(h.size() == DATA_SIZE, "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
  myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  
  myAssert(h.head() == 15, "Line " S__LINE__": Heap<SIZE, s8>::head(void).");
  //myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  h.pop();
  
  myAssert(h.size() == (DATA_SIZE - 1), "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
  myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  
  myAssert(h.head() == 13, "Line " S__LINE__": Heap<SIZE, s8>::head(void).");
  //myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  h.pop();
  
  myAssert(h.head() == 12, "Line " S__LINE__": Heap<SIZE, s8>::head(void).");
  //myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  h.pop();
  
  myAssert(h.head() == 10, "Line " S__LINE__": Heap<SIZE, s8>::head(void).");
  //myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  h.pop();
  
  //myAssert(!h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  myAssert(h.empty(), "Line " S__LINE__": Heap<SIZE, s8>::empty(void).");
  myAssert(h.size() == 0, "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
  myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  
  for(s8 i = 0; i < SIZE; i++) {
    //myAssert(h.push(i), "Line " S__LINE__": Heap<SIZE, s8>::push(ElementType).");
    h.push(i);
    myAssert(h.size() == (i+1), "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
    myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  }
  
  myAssert(h.full(), "Line " S__LINE__": Heap<SIZE, s8>::full(void).");
  myAssert(!h.empty(), "Line " S__LINE__": Heap<SIZE, s8>::empty(void).");
  
  //myAssert(!h.push(8), "Line " S__LINE__": Heap<SIZE, s8>::push(ElementType).");
  
  for(s8 i = 7; i >= 0; i--) {
    myAssert(h.head() == i, "Line " S__LINE__": Heap<SIZE, s8>::head(void).");
    //myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
    h.pop();
    myAssert(h.size() == i, "Line " S__LINE__": Heap<SIZE, s8>::size(void).");
    myAssert(h.limit() == SIZE, "Line " S__LINE__": Heap<SIZE, s8>::limit(void).");
  }

  myAssert(!h.full(), "Line " S__LINE__": Heap<SIZE, s8>::full(void).");
  myAssert(h.empty(), "Line " S__LINE__": Heap<SIZE, s8>::empty(void).");

  //myAssert(!h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  std::cout << "OK" << std::endl;
  return 0;
}
