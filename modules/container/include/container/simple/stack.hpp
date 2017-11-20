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
#ifndef SIMPLE_STACK_HPP
#define SIMPLE_STACK_HPP

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

//! \class Stack stack.hpp <container/stack.hpp>
//! \brief Class representing a stack (lifo)
//! \param _SIZE : the maximum number of elements the stack can handle at any given time.
//! \param _ElementType : the type of the elements within the stack.
template <typename _Element, umax _SIZE, typename _Index = unsigned int>
class Stack :
    public Container<Traits::Default<_Element>, _Index>,
    public Flushable<Traits::Default<_Element>, _Index>,
    public Headed<Traits::Default<_Element>, _Index>,
    public ::Aversive::Container::Stack<Traits::Default<_Element>, _Index>,
    public Limited<Traits::Default<_Element>, _Index> {
public:
  using Index = _Index;
  using Element = _Element;

  //! \brief Number of elements the stack can handle.
  static const Index SIZE = _SIZE;

private:
  //! \brief The array containing the datas.
  Array<Element, SIZE> _data;

  //! \brief The current size of the stack.
  Index _size;

public:
  //! \brief Default constructor.
  inline Stack(void)
    : _data(), _size(0) {
  }

  //! \brief Copy constructor.
  //! \param other : the stack to copy.
  inline Stack(const Stack& other)
    : _data(other._data), _size(other._size) {
  }

  //! \brief Variadic constructor to insert multiple elements.
  //! \param args : the value list to insert in the stack.
  template<typename... Targs>
  inline Stack(const Targs&... args)
    : Stack() {
    List<Element, SIZE, Index> l = {args...};
    for(auto it = l.begin() ; it != l.end() ; it++) {
      push(*it);
    }
  }

  //! \brief Copy operator.
  //! \param other : the stack to copy.
  //! \return A reference to the stack that has been written.
  inline Stack& operator=(const Stack& other) {
    _data = other._data;
    _size = other._size;
    return (*this);
  }

  //! \brief Remove the head of the stack.
  //! \return A boolean telling whether the removal was successful or not.
  inline void pop(void) {
    while(empty());
    _size--;
  }

  //! \brief Pile up an element on top of the stack.
  //! \param element : the element to add to the stack.
  //! \return A boolean telling whether the addition was successful or not.
  inline void push(const Element& element) {
    while(full());
    _data[_size++] = element;
  }

  //! \brief Completely empty the stack.
  inline void flush(void) {
    _size = 0;
  }

  //! \brief Access to the most recently added element of the stack.
  //! \return A constant reference to the element at the top of the stack.
  //! \warning If the stack is actually empty, this causes an undefined behavior.
  inline Element& head(void) {
    while(empty());
    return _data[_size - 1];
  }

  //! \brief Access to the most recently added element of the stack.
  //! \return A constant reference to the element at the top of the stack.
  //! \warning If the stack is actually empty, this causes an undefined behavior.
  inline const Element& head(void) const {
    while(empty());
    return _data[_size - 1];
  }

  //! \brief Test if the stack is empty.
  //! \return A boolean telling whether the stack is empty or not.
  inline bool empty(void) const {
    return _size == 0;
  }

  //! \brief Test if the stack is full.
  //! \return A boolean telling whether the stack is full or not.
  inline bool full(void) const {
    return _size == SIZE;
  }

  //! \brief Give the space currently in use in the stack.
  //! \return The amount of elements currently stacked.
  inline Index size(void) const {
    return _size;
  }

  //! \brief Give the space currently free to use in the stack.
  //! \return The amount of elements that can currently be stacked.
  inline Index limit(void) const {
    return SIZE;
  }
};

}
}
}

#endif//SIMPLE_STACK_HPP
