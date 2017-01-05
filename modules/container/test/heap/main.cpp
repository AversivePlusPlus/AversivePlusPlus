#include <iostream>
#include <container/heap.hpp>
#include <base/integer.hpp>
#include "../my_assert.hpp"

using namespace Aversive::Container;

static const heap_t DATA_SIZE = 4;
static const heap_t HEAP_SIZE = 8;
char t[] = { 13, 15, 12, 10 };

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Heap<HEAP_SIZE, s8> h(0, 1, 2, 3, 4, 5, 6, 7);
  
  myAssert(h.isFull(), "Line " S__LINE__": Heap<SIZE, s8>::isFull(void).");
  myAssert(!h.isEmpty(), "Line " S__LINE__": Heap<SIZE, s8>::isEmpty(void).");
  myAssert(h.usedSpace() == HEAP_SIZE, "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
  myAssert(h.freeSpace() == 0, "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  
  for(s16 i = 7; i >= 0; i--) {
    myAssert(h.max() == i, "Line " S__LINE__": Heap<SIZE, s8>::max(void).");
    myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
    myAssert(h.usedSpace() == (heap_t) i, "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
    myAssert(h.freeSpace() == (HEAP_SIZE - (heap_t) i), "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  }
  
  h.flush();
  
  myAssert(h.usedSpace() == 0, "Line " S__LINE__": Heap<SIZE, s8>::flush(void).");
  myAssert(h.freeSpace() == HEAP_SIZE, "Line " S__LINE__": Heap<SIZE, s8>::flush(void).");
  
  for(heap_t i = 0; i < DATA_SIZE; i++) {
    myAssert(h.insert(t[i]), "Line " S__LINE__": Heap<SIZE, s8>::insert(ElementConstRef).");
  }
  
  myAssert(h.usedSpace() == DATA_SIZE, "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
  myAssert(h.freeSpace() == (HEAP_SIZE - DATA_SIZE), "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  
  myAssert(h.max() == 15, "Line " S__LINE__": Heap<SIZE, s8>::max(void).");
  myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  myAssert(h.usedSpace() == (DATA_SIZE - 1), "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
  myAssert(h.freeSpace() == (HEAP_SIZE - DATA_SIZE  +1), "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  
  myAssert(h.max() == 13, "Line " S__LINE__": Heap<SIZE, s8>::max(void).");
  myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  myAssert(h.max() == 12, "Line " S__LINE__": Heap<SIZE, s8>::max(void).");
  myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  myAssert(h.max() == 10, "Line " S__LINE__": Heap<SIZE, s8>::max(void).");
  myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  myAssert(!h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  myAssert(h.isEmpty(), "Line " S__LINE__": Heap<SIZE, s8>::isEmpty(void).");
  myAssert(h.usedSpace() == 0, "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
  myAssert(h.freeSpace() == HEAP_SIZE, "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  
  for(heap_t i = 0; i < HEAP_SIZE; i++) {
    myAssert(h.insert(i), "Line " S__LINE__": Heap<SIZE, s8>::insert(ElementConstRef).");
    myAssert(h.usedSpace() == (i+1), "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
    myAssert(h.freeSpace() == (HEAP_SIZE - i - 1), "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  }
  
  myAssert(h.isFull(), "Line " S__LINE__": Heap<SIZE, s8>::isFull(void).");
  myAssert(!h.isEmpty(), "Line " S__LINE__": Heap<SIZE, s8>::isEmpty(void).");
  
  myAssert(!h.insert(8), "Line " S__LINE__": Heap<SIZE, s8>::insert(ElementConstRef).");
  
  for(s16 i = 7; i >= 0; i--) {
    myAssert(h.max() == i, "Line " S__LINE__": Heap<SIZE, s8>::max(void).");
    myAssert(h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
    myAssert(h.usedSpace() == (heap_t) i, "Line " S__LINE__": Heap<SIZE, s8>::usedSpace(void).");
    myAssert(h.freeSpace() == (HEAP_SIZE - (heap_t) i), "Line " S__LINE__": Heap<SIZE, s8>::freeSpace(void).");
  }
  
  myAssert(!h.pop(), "Line " S__LINE__": Heap<SIZE, s8>::pop(void).");
  
  std::cout << "OK" << std::endl;
  return 0;
}
