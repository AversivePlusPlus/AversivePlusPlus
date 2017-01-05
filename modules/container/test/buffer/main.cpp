#include <container/buffer.hpp>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <ctime>
#include <cstdlib>
#include "../my_assert.hpp"

using namespace Aversive::Container;

static const buffer_t SIZE = 8;
Buffer<SIZE, u8>* buffer;
const u8* str;
static const int n = 1024;

void* provider(void* arg) {
  (void) arg;
  for(int i = 0; i < n; i++) {
    while(buffer->isFull()) {
      sched_yield();
    }
    myAssert(buffer->enqueue(str[i]), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
  }
  return NULL;
}

void* consumer(void* arg) {
  (void) arg;
  for(int i = 0; i < n; i++) {
    while(buffer->isEmpty()) {
      sched_yield();
    }
    myAssert(buffer->head() == str[i], "Line " S__LINE__ ": The head of the buffer has not the expected value.");
    myAssert(buffer->dequeue(), "Line " S__LINE__ ": An element should have been dequeued successfully since the buffer is not empty.");
  }
  return NULL;
}

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  Buffer<SIZE, u8> b(10,5,8,20);
  
  myAssert(b.head() == 10, "Line " S__LINE__ ": The head of the buffer has not the expected value.");
  myAssert(b.usedSpace() == 4, "Line " S__LINE__ ": Buffer<SIZE, u8>::usedSpace(void).");
  myAssert(b.freeSpace() == (SIZE) - b.usedSpace(), "Line " S__LINE__ ": Buffer<SIZE, u8>::freeSpace(void).");
  myAssert(b.enqueue(12), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
  myAssert(b.usedSpace() == 5, "Line " S__LINE__ ": Buffer<SIZE, u8>::usedSpace(void).");
  myAssert(b.enqueue(2), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
  myAssert(b.head() == 10, "Line " S__LINE__ ": The head of the buffer has not the expected value.");
  myAssert(b.dequeue(), "Line " S__LINE__ ": An element should have been dequeued successfully since the buffer is not empty.");
  myAssert(b.head() == 5, "Line " S__LINE__ ": The head of the buffer has not the expected value.");
  myAssert(!b.isFull(), "Line " S__LINE__ ": Buffer<SIZE, u8>::isFull(void).");
  myAssert(!b.isEmpty(), "Line " S__LINE__ ": Buffer<SIZE, u8>::isEmpty(void).");
  
  b.flush();
  
  myAssert(b.usedSpace() == 0, "Line " S__LINE__ ": Buffer<SIZE, u8>::flush(void).");
  for(buffer_t i = 0; i < 5; i++) {
    myAssert(b.enqueue(10+i), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
  }
  
  myAssert(b.usedSpace() == 5, "Line " S__LINE__ ": Buffer<SIZE, u8>::usedSpace(void).");
  for(buffer_t i = 0; i < 5; i++) {
    myAssert(b.head() == (10+i), "Line " S__LINE__ ": The head of the buffer has not the expected value.");
    myAssert(b.dequeue(), "Line " S__LINE__ ": An element should have been dequeued successfully since the buffer is not empty.");
    myAssert(b.usedSpace() == (4-i), "Line " S__LINE__ ": Buffer<SIZE, u8>::usedSpace(void).");
  }
  
  pthread_t threads[2];
  buffer = &b;
  u8* data = (u8*) malloc(sizeof(u8) * n);
  str = data;
  srand(time(NULL));
  for(int i = 0; i < n; i++) {
    data[i] = (u8) (rand() % 256);
  }
  
  pthread_create(threads, NULL, provider, NULL);
  pthread_create(threads + 1, NULL, consumer, NULL);
  
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  
  myAssert(b.isEmpty(), "Line " S__LINE__ ": Buffer<SIZE, u8>::isEmpty(void).");
  myAssert(b.usedSpace() == 0, "Line " S__LINE__ ": Buffer<SIZE, u8>::usedSpace(void).");
  myAssert(b.freeSpace() == SIZE, "Line " S__LINE__ ": Buffer<SIZE, u8>::freeSpace(void).");
  std::cout << "OK" << std::endl;
  return 0;
}
