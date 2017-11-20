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
#ifndef AVERSIVE_CONTAINER_ARRAY_HPP
#define AVERSIVE_CONTAINER_ARRAY_HPP

namespace Aversive {
namespace Container {

template<typename _TypeTraits, typename _Index>
class Array {
public:
  using BaseArray = Array;

public:
  using ElementRef = typename _TypeTraits::ElementRef;
  using ConstElementRef = typename _TypeTraits::ConstElementRef;

  using Index = _Index;

protected:
  inline Array(void) {}

public:
  //! \brief Access to an element's reference via its field's index.
  //! \param i : the index of the element to access.
  //! \return The reference to the element contained at the specified index.
  inline ElementRef operator[](Index i);

  //! \brief Access to an element's constant reference via its field's index.
  //! \param i : the index of the element to access.
  //! \return The constant reference to the element contained at the specified index.
  inline ConstElementRef operator[](Index i) const;
};

}
}

#endif//AVERSIVE_CONTAINER_ARRAY_HPP
