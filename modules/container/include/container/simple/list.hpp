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
#ifndef SIMPLE_LIST_HPP
#define SIMPLE_LIST_HPP

#include "config.hpp"

#include <container/container.hpp>
#include <container/flushable.hpp>
#include <container/list.hpp>
#include <container/iterable.hpp>
#include <container/limited.hpp>

namespace Aversive {
namespace Container {
namespace Simple {

//! \class List list.hpp <container/list.hpp>
//! \brief Class reprensenting a list of elements.
//! \param _SIZE : the number of elements the list can handle at any given time.
//! \param _ElementType : type of the elements within the list.
template<typename _Element, umax _SIZE, typename _Index = unsigned int>
class List :
    public Container<Traits::Default<_Element>, _Index>,
    public Flushable<Traits::Default<_Element>, _Index>,
    public Iterable<Traits::Default<_Element>, _Index>,
    public ::Aversive::Container::List<Traits::Default<_Element>, _Index>,
    public Limited<Traits::Default<_Element>, _Index> {
public:
  using Index = _Index;
  using Element = _Element;

  //! \brief Number of elements the list can handle.
  static const Index SIZE = _SIZE;

private:
  //! \brief The array containing the datas.
  Array<Element, SIZE> _data;

  //! \brief The current size of the list.
  Index _size;

public:
  //! \brief Default Constructor.
  inline List(void)
    : _data(), _size(0) {
  }

  //! \brief Variadic constructor to insert multiple elements.
  //! \param args : the value list to insert in the list.
  template<typename... Targs>
  inline List(const Targs&... args)
    : _data(args...), _size(argc(args...)) {
  }

  //! \brief Copy constructor.
  //! \param other : the list to copy.
  inline List(const List& other) {
    *this = other;
  }

  //! \brief Copy operator.
  //! \param other : the list to copy.
  //! \return A reference to the list that has been written.
  inline List& operator=(const List& other) {
    _data = other._data;
    _size = other._size;
    return *this;
  }

  //! \brief Test if the list is empty.
  //! \return A boolean telling whether the list is empty or not.
  inline bool empty(void) const {
    return _size == 0;
  }

  //! \brief Give the space currently in use in the list.
  //! \return The amount of elements currently listed.
  inline Index size(void) const {
    return _size;
  }

  //! \brief Test if the list is full.
  //! \return A boolean telling whether the list is full or not.
  inline bool full(void) const {
    return _size == SIZE;
  }

  //! \brief Give the space currently free to use in the list.
  //! \return The amount of elements that can currently be listed.
  inline Index limit(void) const {
    return SIZE;
  }

  //! \brief Completely empty the list.
  inline void flush(void) {
    _size = 0;
  }

  inline Element* begin(void) {
    return (Element*)&_data;
  }

  inline Element* end(void) {
    return ((Element*)&_data)+_size;
  }

  inline const Element* begin(void) const {
    return (const Element*)&_data;
  }

  inline const Element* end(void) const {
    return ((const Element*)&_data)+_size;
  }

  inline void insert(Index index, const Element& element) {
    while(full());
    if(index < _size) {
      for(Index i = _size; index < i; i--) {
        _data[i] = _data[i - 1];
      }
      _data[index] = element;
      _size++;
    }
    else {
      _data[_size++] = element;
    }
  }

  inline void remove(Index index) {
    while(empty());
    for(Index i = index + 1; i < _size; i++) {
      _data[i - 1] = _data[i];
    }
    _size--;
  }
};

}
}
}

#endif//SIMPLE_LIST_HPP
