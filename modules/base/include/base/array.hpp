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
#include "integer.hpp"
#include "bool_ref.hpp"

namespace Aversive {

namespace Base {

  // WARNING : deprecated !
  using array_t = u16;

  //! \class Array array.hpp <base/array.hpp>
  //! \brief Class representing a native array with operator overloading.
  //! \param _SIZE : the amount of elements in the array.
  //! \param _ElementType : the type of the elements contained within the array.
  //! \note This class is specialized for boolean arrays. See Array<_SIZE, bool> for more information.
  template<typename _ElementType, umax _SIZE, typename _IndexType = u16>
  class Array {
  public:
    using IndexType = _IndexType;
    
    //! \brief The size of the array.
    static const IndexType SIZE = _SIZE;

    //! \brief Element's type.
    using ElementType =  _ElementType;

    //! \brief Element's reference type.
    using ElementRef = ElementType&;

    //! \brief Element's constant reference type.
    using ElementConstRef = const ElementType&;

  private:
    //! \brief The native C-like array containing the datas.
    ElementType _elements[SIZE];

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
      : _elements{(ElementType)args...} {
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
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] = other[i];
        }
      return (*this);
    }

    //! \brief Assign a value to every element in the array.
    //! \param e : the value to assign.
    //! \return A reference to the array that has been written.
    inline Array& operator=(ElementConstRef e) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] = e;
        }
      return (*this);
    }

    //! \brief Access to an element's reference via its field's index.
    //! \param i : the index of the element to access.
    //! \return The reference to the element contained at the specified index.
    inline ElementRef operator[](IndexType i) {
      return _elements[i];
    }

    //! \brief Access to an element's constant reference via its field's index.
    //! \param i : the index of the element to access.
    //! \return The constant reference to the element contained at the specified index.
    inline ElementConstRef operator[](IndexType i) const {
      return _elements[i];
    }

    //! \brief Add to each element of the array the corresponding element from another array.
    //! \param other : the array to get the values to add from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator+=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] += other[i];
        }
      return (*this);
    }

    //! \brief Substract to each element of the array the corresponding element from another array.
    //! \param other : the array to get the values to substract from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator-=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] -= other[i];
        }
      return (*this);
    }

    //! \brief Multiply each element of the array by the corresponding element from another array.
    //! \param other : the array to get the values to multiply with.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator*=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] *= other[i];
        }
      return (*this);
    }

    //! \brief Divide each element of the array by the corresponding element from another array.
    //! \param other : the array to get the divisors from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator/=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] /= other[i];
        }
      return (*this);
    }

    //! \brief Get the modulo of each element of the array by the corresponding element from another array.
    //! \param other : the array to get the divisors from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator%=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] %= other[i];
        }
      return (*this);
    }

    //! \brief Add each element of two arraies together two-by-two.
    //! \param other : the array to get the values to add from.
    //! \return The result array after the additions.
    inline Array operator+(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] + other[i];
        }
      return ret;
    }

    //! \brief Substract each element of two arraies together two-by-two.
    //! \param other : the array to get the values to substract from.
    //! \return The result array after the substractions.
    inline Array operator-(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] - other[i];
        }
      return ret;
    }

    //! \brief Multiply each element of two arraies together two-by-two.
    //! \param other : the array to get the multipliers from.
    //! \return The result array after the multiplications.
    inline Array operator*(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] * other[i];
        }
      return ret;
    }

    //! \brief Divide each element of two arraies together two-by-two.
    //! \param other : the array to get the divisors from.
    //! \return The result array after the divisions.
    inline Array operator/(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] / other[i];
        }
      return ret;
    }

    //! \brief Apply a modulo on each element of two arraies together two-by-two.
    //! \param other : the array to get the divisors from.
    //! \return The result array after the modulo operations.
    inline Array operator%(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] % other[i];
        }
      return ret;
    }

    //! \brief Add to each element of the array another object.
    //! \param o : the object to add.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator+=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] += o;
        }
      return (*this);
    }

    //! \brief Substract to each element of the array another object.
    //! \param o : the object to substract.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator-=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] -= o;
        }
      return (*this);
    }

    //! \brief Multiply each element of the array with another object.
    //! \param o : the multiplier.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator*=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] *= o;
        }
      return (*this);
    }

    //! \brief Divide each element of the array by another object.
    //! \param o : the divisor.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator/=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] /= o;
        }
      return (*this);
    }

    //! \brief Get the modulo of each element of the array by another object.
    //! \param o : the divisor.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator%=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] %= o;
        }
      return (*this);
    }

    //! \brief Add an oject to each element of the array.
    //! \param o : the object to add.
    //! \return The result array after the additions.
    inline Array operator+(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] + o;
        }
      return ret;
    }

    //! \brief Substract an object to each element of the array.
    //! \param o : the object to substract.
    //! \return The result array after the substractions.
    inline Array operator-(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] - o;
        }
      return ret;
    }

    //! \brief Multiply each element of the array by another object.
    //! \param o : the multiplier.
    //! \return The result array after the multiplications.
    inline Array operator*(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] * o;
        }
      return ret;
    }

    //! \brief Divide each element of the array by another object.
    //! \param o : the divisor.
    //! \return The result array after the divisions.
    inline Array operator/(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] / o;
        }
      return ret;
    }

    //! \brief Apply a modulo on each element of the array by another object.
    //! \param o : the divisor.
    //! \return The result array after the modulo operations.
    inline Array operator%(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] % o;
        }
      return ret;
    }
  };

  //! \class Array<_SIZE, bool> array.hpp <base/array.hpp>
  //! \brief Class representing a native array with operator overloading specialised for booleans.
  //! \param _SIZE : the amount of booleans in the array.
  template<umax _SIZE, typename _IndexType>
  class Array<bool, _SIZE, _IndexType> {
  public:
    using IndexType = _IndexType;
    
    //! \brief The size of the array.
    static const IndexType SIZE = _SIZE;

    //! \brief Element's type.
    using ElementType = bool;

    //! \brief Element's reference type.
    using ElementRef = BoolRef;

    //! \brief Element's constant reference type.
    using ElementConstRef = bool;

  private:
    //! \brief The real size of the native C-like array.
    static const IndexType REAL_SIZE = (SIZE / 8) + ((SIZE % 8) ? 1 : 0);

    //! \brief The native C-like array containing the datas.
    u8 _elements[REAL_SIZE];

  private:
    template<typename T1, typename... Targs>
    struct ArgList {
      template<typename Callable>
      static inline void doForeach(Callable func, IndexType i, T1 a1, Targs... args) {
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
      static inline void doForeach(Callable func, IndexType i, T1 a1) {
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
      ArgList<Targs...>::doForeach([this](IndexType i, bool a) {
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
      for(IndexType i = 0; i < REAL_SIZE; i++) {
          // It is faster this way, booleans are copied 8 by 8.
          _elements[i] = other._elements[i];
        }
      return (*this);
    }

    //! \brief Assign a value to every element in the array.
    //! \param e : the value to assign.
    //! \return A reference to the array that has been written.
    inline Array& operator=(ElementConstRef e) {
      // It is faster this way, booleans are written 8 by 8.
      u8 v = ((e) ? ~0 : 0);
      for(IndexType i = 0; i < REAL_SIZE; i++) {
          _elements[i] = v;
        }
      return (*this);
    }

    //! \brief Access to an element's reference via its field's index.
    //! \param i : the index of the element to access.
    //! \return The reference to the element contained at the specified index.
    inline ElementRef operator[](IndexType i) {
      return BoolRef(_elements[i / 8], i % 8);
    }

    //! \brief Access to an element's constant reference via its field's index.
    //! \param i : the index of the element to access.
    //! \return The constant reference to the element contained at the specified index.
    inline ElementConstRef operator[](IndexType i) const {
      return (bool) (_elements[i / 8] & (1 << (i % 8)));
    }

    //! \brief Add to each element of the array the corresponding element from another array.
    //! \param other : the array to get the values to add from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator+=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] += other[i];
        }
      return (*this);
    }

    //! \brief Substract to each element of the array the corresponding element from another array.
    //! \param other : the array to get the values to substract from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator-=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] -= other[i];
        }
      return (*this);
    }

    //! \brief Multiply each element of the array by the corresponding element from another array.
    //! \param other : the array to get the values to multiply with.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator*=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] *= other[i];
        }
      return (*this);
    }

    //! \brief Divide each element of the array by the corresponding element from another array.
    //! \param other : the array to get the divisors from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator/=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] /= other[i];
        }
      return (*this);
    }

    //! \brief Get the modulo of each element of the array by the corresponding element from another array.
    //! \param other : the array to get the divisors from.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator%=(const Array& other) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] %= other[i];
        }
      return (*this);
    }

    //! \brief Add each element of two arraies together two-by-two.
    //! \param other : the array to get the values to add from.
    //! \return The result array after the additions.
    inline Array operator+(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] + other[i];
        }
      return ret;
    }

    //! \brief Substract each element of two arraies together two-by-two.
    //! \param other : the array to get the values to substract from.
    //! \return The result array after the substractions.
    inline Array operator-(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] - other[i];
        }
      return ret;
    }

    //! \brief Multiply each element of two arraies together two-by-two.
    //! \param other : the array to get the multipliers from.
    //! \return The result array after the multiplications.
    inline Array operator*(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] * other[i];
        }
      return ret;
    }

    //! \brief Divide each element of two arraies together two-by-two.
    //! \param other : the array to get the divisors from.
    //! \return The result array after the divisions.
    inline Array operator/(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] / other[i];
        }
      return ret;
    }

    //! \brief Apply a modulo on each element of two arraies together two-by-two.
    //! \param other : the array to get the divisors from.
    //! \return The result array after the modulo operations.
    inline Array operator%(const Array& other) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] % other[i];
        }
      return ret;
    }

    //! \brief Add to each element of the array another object.
    //! \param o : the object to add.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator+=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] += o;
        }
      return (*this);
    }

    //! \brief Substract to each element of the array another object.
    //! \param o : the object to substract.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator-=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] -= o;
        }
      return (*this);
    }

    //! \brief Multiply each element of the array with another object.
    //! \param o : the multiplier.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator*=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] *= o;
        }
      return (*this);
    }

    //! \brief Divide each element of the array by another object.
    //! \param o : the divisor.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator/=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] /= o;
        }
      return (*this);
    }

    //! \brief Get the modulo of each element of the array by another object.
    //! \param o : the divisor.
    //! \return A reference to the array the assignment has been done to.
    inline Array& operator%=(ElementConstRef o) {
      for(IndexType i = 0; i < SIZE; i++) {
          (*this)[i] %= o;
        }
      return (*this);
    }

    //! \brief Add an oject to each element of the array.
    //! \param o : the object to add.
    //! \return The result array after the additions.
    inline Array operator+(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] + o;
        }
      return ret;
    }

    //! \brief Substract an object to each element of the array.
    //! \param o : the object to substract.
    //! \return The result array after the substractions.
    inline Array operator-(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] - o;
        }
      return ret;
    }

    //! \brief Multiply each element of the array by another object.
    //! \param o : the multiplier.
    //! \return The result array after the multiplications.
    inline Array operator*(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] * o;
        }
      return ret;
    }

    //! \brief Divide each element of the array by another object.
    //! \param o : the divisor.
    //! \return The result array after the divisions.
    inline Array operator/(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] / o;
        }
      return ret;
    }

    //! \brief Apply a modulo on each element of the array by another object.
    //! \param o : the divisor.
    //! \return The result array after the modulo operations.
    inline Array operator%(ElementConstRef o) const {
      Array ret;
      for(IndexType i = 0; i < SIZE; i++) {
          ret[i] = (*this)[i] % o;
        }
      return ret;
    }
  };

}

}

#endif//ARRAY_HPP
