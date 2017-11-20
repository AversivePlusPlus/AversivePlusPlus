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
#ifndef ARRAY_OP_ELEM_HPP
#define ARRAY_OP_ELEM_HPP

#include "../array.hpp"

namespace Aversive {
namespace Container {
namespace Simple {

//! \brief Add to each element of the array another object.
//! \param o : the object to add.
//! \return A reference to the array the assignment has been done to.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index>& operator+=(Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  for(Index i = 0; i < SIZE; i++) {
    array[i] += o;
  }
  return array;
}

//! \brief Substract to each element of the array another object.
//! \param o : the object to substract.
//! \return A reference to the array the assignment has been done to.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index>& operator-=(Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  for(Index i = 0; i < SIZE; i++) {
    array[i] -= o;
  }
  return array;
}

//! \brief Multiply each element of the array with another object.
//! \param o : the multiplier.
//! \return A reference to the array the assignment has been done to.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index>& operator*=(Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  for(Index i = 0; i < SIZE; i++) {
    array[i] *= o;
  }
  return array;
}

//! \brief Divide each element of the array by another object.
//! \param o : the divisor.
//! \return A reference to the array the assignment has been done to.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index>& operator/=(Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  for(Index i = 0; i < SIZE; i++) {
    array[i] /= o;
  }
  return array;
}

//! \brief Get the modulo of each element of the array by another object.
//! \param o : the divisor.
//! \return A reference to the array the assignment has been done to.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index>& operator%=(Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  for(Index i = 0; i < SIZE; i++) {
    array[i] %= o;
  }
  return array;
}

//! \brief Add an oject to each element of the array.
//! \param o : the object to add.
//! \return The result array after the additions.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index> operator+(const Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  Array<ElementType, SIZE, Index> ret;
  for(Index i = 0; i < SIZE; i++) {
    ret[i] = array[i] + o;
  }
  return ret;
}

//! \brief Substract an object to each element of the array.
//! \param o : the object to substract.
//! \return The result array after the substractions.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index> operator-(const Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  Array<ElementType, SIZE, Index> ret;
  for(Index i = 0; i < SIZE; i++) {
    ret[i] = array[i] - o;
  }
  return ret;
}

//! \brief Multiply each element of the array by another object.
//! \param o : the multiplier.
//! \return The result array after the multiplications.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index> operator*(const Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  Array<ElementType, SIZE, Index> ret;
  for(Index i = 0; i < SIZE; i++) {
    ret[i] = array[i] * o;
  }
  return ret;
}

//! \brief Divide each element of the array by another object.
//! \param o : the divisor.
//! \return The result array after the divisions.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index> operator/(const Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  Array<ElementType, SIZE, Index> ret;
  for(Index i = 0; i < SIZE; i++) {
    ret[i] = array[i] / o;
  }
  return ret;
}

//! \brief Apply a modulo on each element of the array by another object.
//! \param o : the divisor.
//! \return The result array after the modulo operations.
template<typename ElementType, umax SIZE, typename Index>
inline Array<ElementType, SIZE, Index> operator%(const Array<ElementType, SIZE, Index>& array, typename Array<ElementType, SIZE, Index>::ConstElementRef o) {
  Array<ElementType, SIZE, Index> ret;
  for(Index i = 0; i < SIZE; i++) {
    ret[i] = array[i] % o;
  }
  return ret;
}

}
}
}

#endif//ARRAY_OP_ELEM_HPP
