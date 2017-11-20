#include <container/simple/list.hpp>
#include <container/utils/test.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Container::Simple;
using namespace Aversive::Container::Test;

static const unsigned int SIZE = 10;

int main(int, char**) {
  static_assert(test_interface<Aversive::Container::Container, List<u8, SIZE>>(), "ERROR : Class don't follow the Container interface");
  static_assert(test_interface<Aversive::Container::Flushable, List<u8, SIZE>>(), "ERROR : Class don't follow the Flushable interface");
  static_assert(test_interface<Aversive::Container::Iterable, List<u8, SIZE>>(), "ERROR : Class don't follow the Iterable interface");
  static_assert(test_interface<Aversive::Container::List, List<u8, SIZE>>(), "ERROR : Class don't follow the List interface");
  static_assert(test_interface<Aversive::Container::Limited, List<u8, SIZE>>(), "ERROR : Class don't follow the Limited interface");

  List<u8, SIZE> l(10, 5, 8, 20);
  
  myAssert(*(l.begin()+0) == 10, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(*(l.begin()+1) == 5, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(*(l.begin()+3) == 20, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.size() == 4, "Line " S__LINE__": List<SIZE, u8>::size(void).");
  myAssert(l.limit() == SIZE, "Line " S__LINE__": List<SIZE, u8>::freeSpace(void).");
  //myAssert(l.insert(0, 12), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
  l.insert(l.size(), 12);
  myAssert(*(l.begin()+4) == 12, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.size() == 5, "Line " S__LINE__": List<SIZE, u8>::size(void).");
  //myAssert(l.insert(l.size(), 2), "Line " S__LINE__": List<SIZE, u8>::prepend(u8).");
  l.insert(0, 2);
  myAssert(*(l.begin()+0) == 2, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(*(l.begin()+5) == 12, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(!l.full(), "Line " S__LINE__": List<SIZE, u8>::isFull(void).");
  myAssert(!l.empty(), "Line " S__LINE__": List<SIZE, u8>::isEmpty(void).");
  myAssert(l.size() == 6, "Line " S__LINE__": List<SIZE, u8>::size(void).");
  myAssert(*(l.begin()+1) == 10, "Line " S__LINE__": List<SIZE, u8>::indexOf(u8).");
  //myAssert(l.contains(20), "Line " S__LINE__": List<SIZE, u8>::contains(u8).");
  //myAssert(!l.contains(100), "Line " S__LINE__": List<SIZE, u8>::contains(u8).");
  
  l.flush();
  
  myAssert(l.size() == 0, "Line " S__LINE__": List<SIZE, u8>::flush(void).");
  for(List<u8, SIZE>::Index i = 0; i < 5; i++) {
    //myAssert(l.insert(l.size(), 10), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
    l.insert(l.size(), 10);
  }
  
  myAssert(l.size() == 5, "Line " S__LINE__": List<SIZE, u8>::size(void).");
  for(List<u8, SIZE>::Index i = 0; i < 5; i++) {
    myAssert(*(l.begin()+i) == 10, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  }
  
  //myAssert(l.contains(10), "Line " S__LINE__": List<SIZE, u8>::contains(u8).");
  //myAssert(l.insert(l.size(), 13), "Line " S__LINE__": List<SIZE, u8>::prepend(u8).");
  l.insert(0, 13);
  myAssert(*(l.begin()+0) == 13, "Line " S__LINE__": List<SIZE, u8>::indexOf(u8).");
  //myAssert(l.insert(0, 16), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
  l.insert(l.size(), 16);
  myAssert(*(l.begin()+6) == 16, "Line " S__LINE__": List<SIZE, u8>::indexOf(u8).");
  //myAssert(l.remove(1), "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  for(List<u8, SIZE>::Index i = 0; i < 5; i++) {
    //myAssert(l.insert(l.size(), 10), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
    l.remove(1);
  }
  myAssert(l.size() == 2, "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  myAssert(*(l.begin()+0) == 13, "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  myAssert(*(l.begin()+1) == 16, "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  //myAssert(l.remove(0), "Line " S__LINE__": List<SIZE, u8>::removeAt(list_t).");
  l.remove(0);
  myAssert(l.size() == 1, "Line " S__LINE__": List<SIZE, u8>::removeAt(list_t).");
  myAssert(*(l.begin()+0) == 16, "Line " S__LINE__": List<SIZE, u8>::removeAt(list_t).");
  
  std::cout << "OK" << std::endl;
  return 0;
}
