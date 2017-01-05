#include <container/queue.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Container;

static const queue_t SIZE = 10;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Queue<SIZE, u8> q(10, 5, 8, 20);
  
  myAssert(q.head() == 10, "Line " S__LINE__": Queue<SIZE, u8>::head(void).");
  myAssert(q.usedSpace() == 4, "Line " S__LINE__": Queue<SIZE, u8>::usedSpace(void).");
  myAssert(q.freeSpace() == (SIZE - q.usedSpace()), "Line " S__LINE__": Queue<SIZE, u8>::freeSpace(void).");
  myAssert(q.enqueue(12), "Line " S__LINE__": Queue<SIZE, u8>::enqueue(u8).");
  myAssert(q.usedSpace() == 5, "Line " S__LINE__": Queue<SIZE, u8>::usedSpace(void).");
  myAssert(q.enqueue(2), "Line " S__LINE__": Queue<SIZE, u8>::enqueue(u8).");
  myAssert(q.head() == 10, "Line " S__LINE__": Queue<SIZE, u8>::head(void).");
  myAssert(q.dequeue(), "Line " S__LINE__": Queue<SIZE, u8>::dequeue(void).");
  myAssert(q.head() == 5, "Line " S__LINE__": Queue<SIZE, u8>::head(void).");
  myAssert(!q.isFull(), "Line " S__LINE__": Queue<SIZE, u8>::isFull(void).");
  myAssert(!q.isEmpty(), "Line " S__LINE__": Queue<SIZE, u8>::isEmpty(void).");
  
  q.flush();
  
  myAssert(q.usedSpace() == 0, "Line " S__LINE__": Queue<SIZE, u8>::flush(void).");
  for(queue_t i = 0; i < 5; i++) {
    myAssert(q.enqueue(10 + i), "Line " S__LINE__": Queue<SIZE, u8>::enqueue(u8).");
  }
  
  myAssert(q.usedSpace() == 5, "Line " S__LINE__": Queue<SIZE, u8>::usedSpace(void).");
  for(queue_t i = 0; i < 5; i++) {
    myAssert(q.head() == (10 + i), "Line " S__LINE__": Queue<SIZE, u8>::head(void).");
    myAssert(q.dequeue(), "Line " S__LINE__": Queue<SIZE, u8>::dequeue(void).");
    myAssert(q.usedSpace() == (4 - i), "Line " S__LINE__": Queue<SIZE, u8>::usedSpace(void).");
  }
  
  std::cout << "OK" << std::endl;
  return 0;
}
