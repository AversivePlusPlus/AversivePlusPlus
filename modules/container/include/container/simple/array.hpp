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
#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "config.hpp"

#include <base/bool_ref.hpp>

#include <container/container.hpp>
#include <container/iterable.hpp>
#include <container/limited.hpp>
#include <container/array.hpp>

namespace Aversive {
namespace Container {
namespace Simple {

//! \brief The native C-like array type alias.
template<typename T, umax SIZE> using array = T[SIZE];

//! \class Array array.hpp <base/array.hpp>
//! \brief Class representing a native array with operator overloading.
//! \param _SIZE : the amount of elements in the array.
//! \param _ElementType : the type of the elements contained within the array.
//! \note This class is specialized for boolean arrays. See Array<_SIZE, bool> for more information.
template<typename _Element, umax _SIZE, typename _Index = unsigned int>
class Array :
    public Container<Traits::Default<_Element>, _Index>,
    public Iterable<Traits::Default<_Element>, _Index>,
    public ::Aversive::Container::Array<Traits::Default<_Element>, _Index>,
    public Limited<Traits::Default<_Element>, _Index> {
public:
  using Index = _Index;

  //! \brief The size of the array.
  static const Index SIZE = _SIZE;

  //! \brief Element's type.
  using Element =  _Element;

  //! \brief Element's reference type.
  using ElementRef = Element&;

  //! \brief Element's constant reference type.
  using ConstElementRef = const Element&;

  using Iterator = Element*;
  using ConstIterator = const Element*;

protected:
  //! \brief The native C-like array containing the datas.
  array<Element, SIZE> _elements;

public:
  //! \brief Default constructor.
  //! \attention The elements within the array are not set to any value.
  inline Array(void) {
  }

  //! \brief Variadic constructor to insert multiple elements.
  //! \param args : the value list to insert in the array.
  //! \note If there are less elements given than the size of the array, the last element is written at all the remaining indexes.
  template<typename... Targs>
  inline Array(const Targs&... args)
    : _elements{(ElementRef)args...} {
  }

  //! \brief Copy constructor.
  //! \param other : the array to copy.
  inline Array(const Array& other) {
    (*this) = other;
  }

  //! \brief Copy operator.
  //! \param other : the array to copy.
  //! \return A reference to the array that has been written.
  inline Array& operator=(const Array& other) {
    for(Index i = 0; i < SIZE; i++) {
      (*this)[i] = other[i];
    }
    return (*this);
  }

  //! \brief Assign a value to every element in the array.
  //! \param e : the value to assign.
  //! \return A reference to the array that has been written.
  inline Array& operator=(ConstElementRef e) {
    for(Index i = 0; i < SIZE; i++) {
      (*this)[i] = e;
    }
    return (*this);
  }

  //! \brief Access to an element's reference via its field's index.
  //! \param i : the index of the element to access.
  //! \return The reference to the element contained at the specified index.
  inline ElementRef operator[](Index i) {
    return _elements[i];
  }

  //! \brief Access to an element's constant reference via its field's index.
  //! \param i : the index of the element to access.
  //! \return The constant reference to the element contained at the specified index.
  inline ConstElementRef operator[](Index i) const {
    return _elements[i];
  }

  inline bool empty(void) const {
    return false;
  }

  inline Index size(void) const {
    return SIZE;
  }

  inline bool full(void) const {
    return true;
  }

  inline Index limit(void) const {
    return SIZE;
  }

  inline Iterator begin(void) {
    return (Iterator)&_elements;
  }

  inline ConstIterator begin(void) const {
    return (ConstIterator)&_elements;
  }

  inline Iterator end(void) {
    return ((Iterator)&_elements)+SIZE;
  }

  inline ConstIterator end(void) const {
    return ((ConstIterator)&_elements)+SIZE;
  }
};

}
}
}

#include "array/array_bool.hpp"
#include "array/array_op.hpp"
#include "array/array_op_elem.hpp"

#endif//ARRAY_HPP
