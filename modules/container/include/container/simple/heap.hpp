/*
Copyright (c) 2015, Xenomorphales
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Aversive++ nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#ifndef HEAP_HPP
#define HEAP_HPP

#include "config.hpp"

#include <container/simple/list.hpp>

#include <container/container.hpp>
#include <container/flushable.hpp>
#include <container/headed.hpp>
#include <container/stack.hpp>
#include <container/limited.hpp>

namespace Aversive {
namespace Container {
namespace Simple {

//! \class Heap heap.hpp <container/heap.hpp>
//! \brief Class representing a heap that allows to easily extract the maximum element of a given set.
//! \param _SIZE : the number of elements the heap can handle at any given time.
//! \param _ElementType : type of the elements within the heap.
/*!
  The heap allows to easily extract the maximum value of a given set.
  Once the element is inserted, it is compared to others to order it.
  The only element accessible and deletable is the maximum. The
  maximum is the element for which the comparison operator returns
  true foreach comparision with others element in the heap.
*/
template<typename _Element, umax _SIZE, typename _Index = unsigned int>
class Heap :
    public Container<Traits::Default<_Element>, _Index>,
    public Flushable<Traits::Default<_Element>, _Index>,
    public Headed<Traits::Default<_Element>, _Index>,
    public Stack<Traits::Default<_Element>, _Index>,
    public Limited<Traits::Default<_Element>, _Index> {
public:
  using Index = _Index;
  using Element = _Element;

  //! \brief Number of elements the heap can handle.
  static const Index SIZE = _SIZE;

private:
  //! \brief The array containing the datas.
  Array<Element, SIZE> _data;

  //! \brief The current size of the heap.
  Index _size;

private:
  inline static constexpr Index parent(Index index) {
    return (index-1)/2;
  }

  inline static constexpr Index firstChild(Index index) {
    return (index*2)+1;
  }

  inline static constexpr Index secondChild(Index index) {
    return (index*2)+2;
  }

  inline static constexpr bool hasParent(Index index) {
    return index > 0;
  }

  inline bool valid(Index index) const {
    return index < _size;
  }

  inline bool hasFirstChild(Index index) const {
    return valid(firstChild(index));
  }

  inline bool hasSecondChild(Index index) const {
    return valid(secondChild(index));
  }

  void switchElements(Index i1, Index i2) {
    const Element tmp = _data[i1];
    _data[i1] = _data[i2];
    _data[i2] = tmp;
  }

  //! \brief Place correctly an element which has to be moved upward.
  //! \param index : the index in the data array of the element to move upward.
  void percolateUp(Index index) {
    Index cur = index;
    while(hasParent(cur) && _data[parent(cur)] < _data[cur]) {
      switchElements(cur, parent(cur));
      cur = parent(cur);
    }
  }

  //! \brief Place correctly an element which has to be moved downward.
  //! \param index : the index in the data array of the element to move downward.
  void percolateDown(Index index) {
    Index cur = index;
    // While there is one child greater than current
    while((hasFirstChild(cur) && _data[cur] < _data[firstChild(cur)]) ||
          (hasSecondChild(cur) && _data[cur] < _data[secondChild(cur)])) {
      // If there is only one child
      // The first child must be filled first !
      if(!hasFirstChild(cur)) {
        switchElements(cur, secondChild(cur));
        cur = secondChild(cur);
      }
      else if(!hasSecondChild(cur)) {
        switchElements(cur, firstChild(cur));
        cur = firstChild(cur);
      }
      // If there is two children
      else {
        // Switch with the max
        if(_data[firstChild(cur)] < _data[secondChild(cur)]) {
          switchElements(cur, secondChild(cur));
          cur = secondChild(cur);
        }
        else {
          switchElements(cur, firstChild(cur));
          cur = firstChild(cur);
        }
      }
    }
  }

public:
  //! \brief Default Constructor
  inline Heap(void)
    : _size(0) {
  }

  //! \brief Variadic constructor to insert multiple elements.
  //! \param args : the value list to insert in the list.
  template<typename... Targs>
  inline Heap(const Targs&... args)
    : Heap() {
    List<Element, SIZE, Index> l = {args...};
    for(auto it = l.begin() ; it != l.end() ; it++) {
      push(*it);
    }
  }

  //! \brief Copy Constructor
  //! \param other : the heap to copy.
  inline Heap(const Heap& other) {
    (*this) = other;
  }

  //! \brief Copy Operator.
  //! \param other : the heap to copy.
  //! \return A reference to the heap that has been written.
  inline Heap& operator=(const Heap& other) {
    _size = other._size;
    _data = other._data;
    return *this;
  }

  //! \brief Insert an element in the Heap
  //! \param e : the element to add within the heap.
  //! \return A boolean telling whether the element has been successfully inserted or not.
  inline void push(const Element& e) {
    while(full());
    _data[_size] = e;
    percolateUp(_size++);
  }

  //! \brief Delete the maximal element
  //! \return A boolean telling whether an element has been removed from the heap or not.
  inline void pop(void) {
    while(empty());
    _data[0] = _data[_size - 1];
    _size--;
    percolateDown(0);
  }

  //! \brief Completely empty the heap.
  inline void flush(void) {
    _size = 0;
  }

  //! \brief Access to the maximal element.
  //! \return A reference to the maximal element.
  //! \warning If the heap is actually empty, this causes an undefined behavior.
  inline Element& head(void) {
    while(empty());
    return _data[0];
  }

  //! \brief Access to the maximal element.
  //! \return A reference to the maximal element.
  //! \warning If the heap is actually empty, this causes an undefined behavior.
  inline const Element& head(void) const {
    while(empty());
    return _data[0];
  }

  //! \brief Test if the heap is empty.
  //! \return A boolean telling whether the heap is empty or not.
  inline bool empty(void) const {
    return _size == 0;
  }

  //! \brief Test if the heap is full.
  //! \return A boolean telling whether the heap is full or not.
  inline bool full(void) const {
    return _size == SIZE;
  }

  //! \brief Give the space currently free to use in the heap.
  //! \return The amount of elements that can currently be added to the heap.
  inline Index limit(void) const {
    return SIZE;
  }

  //! \brief Give the space currently in use in the heap.
  //! \return The amount of elements currently in the heap.
  inline Index size(void) const {
    return _size;
  }
};

}
}
}

#endif//HEAP_HPP
