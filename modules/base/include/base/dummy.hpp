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
#ifndef HDL_UTIL_DUMMY_HPP
#define HDL_UTIL_DUMMY_HPP

#include <base/integer.hpp>

namespace Base {

  //! \brief This is a utility type for templates
  /*!
 * Due to C++ current (october 2015) specifications,
 * templates cannot be specialised in the class where
 * it has been declared.
 * But partial specialisations are allowed.
 * So this type is used when the developper
 * wants to specialise a template in the same class
 * as it has been declared.
 */
  using DummyType = u8;

  //! \brief This value should be used with DummyType
  /*!
 * It should even be the only acceptable value of DummyType.
 */
  constexpr u8 DUMMY_VALUE = 0;

}

#ifndef AVERSIVE_DISABLE_BASE_DEFAULT
using namespace Base;
#endif//AVERSIVE_DISABLE_BASE_DEFAULT

#endif//HDL_UTIL_DUMMY_HPP
