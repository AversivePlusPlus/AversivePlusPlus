#include <container/list.hpp>
#include <iostream>
#include "../my_assert.hpp"

using namespace Aversive::Container;

static const list_t SIZE = 10;

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  List<SIZE, u8> l(10, 5, 8, 20);
  
  myAssert(l.get(0) == 10, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.get(1) == 5, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.get(3) == 20, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.usedSpace() == 4, "Line " S__LINE__": List<SIZE, u8>::usedSpace(void).");
  myAssert(l.freeSpace() == (SIZE - l.usedSpace()), "Line " S__LINE__": List<SIZE, u8>::freeSpace(void).");
  myAssert(l.append(12), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
  myAssert(l.get(4) == 12, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.usedSpace() == 5, "Line " S__LINE__": List<SIZE, u8>::usedSpace(void).");
  myAssert(l.prepend(2), "Line " S__LINE__": List<SIZE, u8>::prepend(u8).");
  myAssert(l.get(0) == 2, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(l.get(5) == 12, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  myAssert(!l.isFull(), "Line " S__LINE__": List<SIZE, u8>::isFull(void).");
  myAssert(!l.isEmpty(), "Line " S__LINE__": List<SIZE, u8>::isEmpty(void).");
  myAssert(l.usedSpace() == 6, "Line " S__LINE__": List<SIZE, u8>::usedSpace(void).");
  myAssert(l.indexOf(10) == 1, "Line " S__LINE__": List<SIZE, u8>::indexOf(u8).");
  myAssert(l.contains(20), "Line " S__LINE__": List<SIZE, u8>::contains(u8).");
  myAssert(!l.contains(100), "Line " S__LINE__": List<SIZE, u8>::contains(u8).");
  
  l.flush();
  
  myAssert(l.usedSpace() == 0, "Line " S__LINE__": List<SIZE, u8>::flush(void).");
  for(list_t i = 0; i < 5; i++) {
    myAssert(l.append(10), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
  }
  
  myAssert(l.usedSpace() == 5, "Line " S__LINE__": List<SIZE, u8>::usedSpace(void).");
  for(list_t i = 0; i < 5; i++) {
    myAssert(l.get(i) == 10, "Line " S__LINE__": List<SIZE, u8>::get(list_t).");
  }
  
  myAssert(l.contains(10), "Line " S__LINE__": List<SIZE, u8>::contains(u8).");
  myAssert(l.prepend(13), "Line " S__LINE__": List<SIZE, u8>::prepend(u8).");
  myAssert(l.indexOf(13) == 0, "Line " S__LINE__": List<SIZE, u8>::indexOf(u8).");
  myAssert(l.append(16), "Line " S__LINE__": List<SIZE, u8>::append(u8).");
  myAssert(l.indexOf(16) == 6, "Line " S__LINE__": List<SIZE, u8>::indexOf(u8).");
  myAssert(l.remove(10), "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  myAssert(l.usedSpace() == 2, "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  myAssert(l.indexOf(13) == 0, "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  myAssert(l.indexOf(16) == 1, "Line " S__LINE__": List<SIZE, u8>::remove(u8).");
  myAssert(l.removeAt(0), "Line " S__LINE__": List<SIZE, u8>::removeAt(list_t).");
  myAssert(l.usedSpace() == 1, "Line " S__LINE__": List<SIZE, u8>::removeAt(list_t).");
  myAssert(l.indexOf(16) == 0, "Line " S__LINE__": List<SIZE, u8>::removeAt(list_t).");
  
  std::cout << "OK" << std::endl;
  return 0;
}
