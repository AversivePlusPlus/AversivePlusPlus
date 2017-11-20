#include <container/simple/buffer.hpp>
#include <container/utils/test.hpp>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <ctime>
#include <cstdlib>
#include "../my_assert.hpp"

using namespace Aversive::Container::Simple;
using namespace Aversive::Container::Test;

static const unsigned int SIZE = 8;
Buffer<u8, SIZE>* buffer;
const u8* str;
static const int n = 1024;

void* provider(void* arg) {
  (void) arg;
  for(int i = 0; i < n; i++) {
    while(buffer->full()) {
      sched_yield();
    }
    //myAssert(buffer->enqueue(str[i]), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
    buffer->enqueue(str[i]);
  }
  return NULL;
}

void* consumer(void* arg) {
  (void) arg;
  for(int i = 0; i < n; i++) {
    while(buffer->empty()) {
      sched_yield();
    }
    myAssert(buffer->head() == str[i], "Line " S__LINE__ ": The head of the buffer has not the expected value.");
    //myAssert(buffer->dequeue(), "Line " S__LINE__ ": An element should have been dequeued successfully since the buffer is not empty.");
    buffer->dequeue();
  }
  return NULL;
}

int main(int, char**) {
  static_assert(test_interface<Aversive::Container::Container, Buffer<u8, SIZE>>(), "ERROR : Class don't follow the Container interface");
  static_assert(test_interface<Aversive::Container::Flushable, Buffer<u8, SIZE>>(), "ERROR : Class don't follow the Flushable interface");
  static_assert(test_interface<Aversive::Container::Headed, Buffer<u8, SIZE>>(), "ERROR : Class don't follow the Headed interface");
  static_assert(test_interface<Aversive::Container::Queue, Buffer<u8, SIZE>>(), "ERROR : Class don't follow the Queue interface");
  static_assert(test_interface<Aversive::Container::Limited, Buffer<u8, SIZE>>(), "ERROR : Class don't follow the Limited interface");

  Buffer<u8, SIZE> b(10,5,8,20);
  
  myAssert(b.head() == 10, "Line " S__LINE__ ": The head of the buffer has not the expected value.");
  myAssert(b.size() == 4, "Line " S__LINE__ ": Buffer<SIZE, u8>::size(void).");
  myAssert(b.limit() == (SIZE), "Line " S__LINE__ ": Buffer<SIZE, u8>::limit(void).");
  //myAssert(b.enqueue(12), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
  b.enqueue(12);
  myAssert(b.size() == 5, "Line " S__LINE__ ": Buffer<SIZE, u8>::size(void).");
  //myAssert(b.enqueue(2), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
  b.enqueue(2);
  myAssert(b.head() == 10, "Line " S__LINE__ ": The head of the buffer has not the expected value.");
  //myAssert(b.dequeue(), "Line " S__LINE__ ": An element should have been dequeued successfully since the buffer is not empty.");
  b.dequeue();
  myAssert(b.head() == 5, "Line " S__LINE__ ": The head of the buffer has not the expected value.");
  myAssert(!b.full(), "Line " S__LINE__ ": Buffer<SIZE, u8>::full(void).");
  myAssert(!b.empty(), "Line " S__LINE__ ": Buffer<SIZE, u8>::empty(void).");
  
  b.flush();
  
  myAssert(b.size() == 0, "Line " S__LINE__ ": Buffer<SIZE, u8>::flush(void).");
  for(Buffer<u8, SIZE>::Index i = 0; i < 5; i++) {
    //myAssert(b.enqueue(10+i), "Line " S__LINE__ ": The given element should have been enqueued successfully since the buffer is not full.");
    b.enqueue(10+i);
  }
  
  myAssert(b.size() == 5, "Line " S__LINE__ ": Buffer<SIZE, u8>::size(void).");
  for(Buffer<u8, SIZE>::Index i = 0; i < 5; i++) {
    myAssert(b.head() == (10+i), "Line " S__LINE__ ": The head of the buffer has not the expected value.");
    //myAssert(b.dequeue(), "Line " S__LINE__ ": An element should have been dequeued successfully since the buffer is not empty.");
    b.dequeue();
    myAssert(b.size() == (4-i), "Line " S__LINE__ ": Buffer<SIZE, u8>::size(void).");
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
  
  myAssert(b.empty(), "Line " S__LINE__ ": Buffer<SIZE, u8>::empty(void).");
  myAssert(b.size() == 0, "Line " S__LINE__ ": Buffer<SIZE, u8>::size(void).");
  myAssert(b.limit() == SIZE, "Line " S__LINE__ ": Buffer<SIZE, u8>::limit(void).");
  std::cout << "OK" << std::endl;
  return 0;
}
