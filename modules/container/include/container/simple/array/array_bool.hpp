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
#ifndef ARRAY_BOOL_HPP
#define ARRAY_BOOL_HPP

#include "../array.hpp"

namespace Aversive {
namespace Container {
namespace Simple {

//! \class Array<_SIZE, bool> array.hpp <base/array.hpp>
//! \brief Class representing a native array with operator overloading specialised for booleans.
//! \param _SIZE : the amount of booleans in the array.
template<umax _SIZE, typename _Index>
class Array<bool, _SIZE, _Index> :
    public Container<Traits::Custom<bool, BoolRef, const bool>, _Index>,
    public ::Aversive::Container::Array<Traits::Custom<bool, BoolRef, const bool>, _Index>,
    public Limited<Traits::Custom<bool, BoolRef, const bool>, _Index> {
public:
  using Index = _Index;

  //! \brief The size of the array.
  static const Index SIZE = _SIZE;

  //! \brief Element's type.
  using ElementType = bool;

  //! \brief Element's reference type.
  using ElementRef = BoolRef;

  //! \brief Element's constant reference type.
  using ConstElementRef = const bool;

private:
  //! \brief The real size of the native C-like array.
  static const Index REAL_SIZE = (SIZE / 8) + ((SIZE % 8) ? 1 : 0);

  //! \brief The native C-like array containing the datas.
  u8 _elements[REAL_SIZE];

private:
  template<typename T1, typename... Targs>
  struct ArgList {
    template<typename Callable>
    static inline void doForeach(Callable func, Index i, T1 a1, Targs... args) {
      func(i, a1);
      ArgList<Targs...>::doForeach(func, i+1, args...);
    }

    template<typename Callable>
    static inline void doForeach(Callable func, T1 a1, Targs... args) {
      func(0, a1);
      ArgList<Targs...>::doForeach(func, 1, args...);
    }
  };

  template<typename T1>
  struct ArgList<T1> {
    template<typename Callable>
    static inline void doForeach(Callable func, Index i, T1 a1) {
      func(i, a1);
    }

    template<typename Callable>
    static inline void doForeach(Callable func, T1 a1) {
      func(0, a1);
    }
  };

public:
  //! \brief Default constructor.
  //! \attention The elements within the array are not set to any value.
  inline Array(void) {}

  //! \brief Variadic constructor to insert multiple elements.
  //! \param args : the value list to insert in the array.
  //! \note If there are less elements given than the size of the array, the last element is written at all the remaining indexes.
  template<typename... Targs>
  inline Array(const Targs&... args) {
    ArgList<Targs...>::doForeach([this](Index i, bool a) {
      (*this)[i] = a;
    }, args...);
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
    for(Index i = 0; i < REAL_SIZE; i++) {
      // It is faster this way, booleans are copied 8 by 8.
      _elements[i] = other._elements[i];
    }
    return (*this);
  }

  //! \brief Assign a value to every element in the array.
  //! \param e : the value to assign.
  //! \return A reference to the array that has been written.
  inline Array& operator=(ConstElementRef e) {
    // It is faster this way, booleans are written 8 by 8.
    u8 v = ((e) ? ~0 : 0);
    for(Index i = 0; i < REAL_SIZE; i++) {
        _elements[i] = v;
      }
    return (*this);
  }

  //! \brief Access to an element's reference via its field's index.
  //! \param i : the index of the element to access.
  //! \return The reference to the element contained at the specified index.
  inline ElementRef operator[](Index i) {
    return BoolRef(_elements[i / 8], i % 8);
  }

  //! \brief Access to an element's constant reference via its field's index.
  //! \param i : the index of the element to access.
  //! \return The constant reference to the element contained at the specified index.
  inline ConstElementRef operator[](Index i) const {
    return (bool) (_elements[i / 8] & (1 << (i % 8)));
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
};

}
}
}

#endif//ARRAY_BOOL_HPP
