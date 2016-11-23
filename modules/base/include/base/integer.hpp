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
#ifndef HDL_COMMON_INTEGER_HPP
#define HDL_COMMON_INTEGER_HPP

#include <stdint.h>

namespace Base {

  //! \class IntegerInfo integer.hpp <base/integer.hpp>
  //! \brief Boundary infos of integer type with a specified size.
  //! \param _SIZE : size of integers in bits.
  template<uint8_t _SIZE>
  struct IntegerInfo {
    //! \brief The size in bits of the integers the infos in this class refer to.
    static constexpr uint8_t SIZE = _SIZE;

    //! \brief Maximum value for an unsigned integer of SIZE bits.
    static constexpr uint64_t UNSIGNED_MAX = (static_cast<uint64_t>(1) << SIZE) - 1;

    //! \brief Maximum value for a signed integer of SIZE bits.
    static constexpr int64_t SIGNED_MAX = (static_cast<uint64_t>(1) << (SIZE - 1)) - 1;

    //! \brief Minimum value for a signed integer of SIZE bits.
    static constexpr int64_t SIGNED_MIN = -(static_cast<uint64_t>(1) << (SIZE - 1));
  };

  //! \class Integer integer.hpp <base/integer.hpp>
  //! \brief Integer type definitions with a specified size.
  //! \param _SIZE : size of integer type in bits.
  //! \param _FAST : whether it is "fast" type or not.
  /*!
  This templated-class is specialised for 8, 16, 32 and 64 bits integer, wheter fast type or not.
  This class will cause an assertion at compile-time if you use it with a size different than 8, 16, 32 or 64 bits.
  You can easily use this class to do metaprogramming.
  Short type names are also provided for classic usages: u8 (unsigned 8 bits), s8 (signed 8 bits), uf8 (fast unsigned 8 bits), sf8 (fast signed 8 bits) and so on for 16, 32 and 64 bits integers.
  Short type names for pointer-sized unsigned and signed integers are also provided: usys (unsigned pointer-sized) and ssys (signed pointer-sized). You can retrieve these types' information easily with IntegerInfo<sizeof(usys) * 8>.
*/
  template<uint8_t _SIZE, bool _FAST = false>
  struct Integer {
    static_assert(true, "Integers of 8, 16, 32 or 64 bits only are supported.");

    //! \brief The size in bits of the integers represented by this class.
    static constexpr uint8_t SIZE = _SIZE;

    //! \brief Whether the integers represented by this class are "fast" or not.
    static constexpr bool FAST = _FAST;

    //! \brief Signed type for integer of SIZE bits.
    using Signed = void;

    //! \brief Unsigned type for integer of SIZE bits.
    using Unsigned = void;

    //! \brief Informations for integer of SIZE bits.
    using Info = IntegerInfo<SIZE>;
  };

  // Defs
#define MACRO_INTEGER(s) \
  template<> struct Integer<s, false> { static constexpr uint8_t SIZE = s; static constexpr bool FAST = false; using Signed = int##s##_t; using Unsigned = uint##s##_t; using Info = IntegerInfo<s>; }; \
  template<> struct Integer<s, true> { static constexpr uint8_t SIZE = s; static constexpr bool FAST = true; using Signed = int_fast##s##_t; using Unsigned = uint_fast##s##_t; using Info = IntegerInfo<s>; };

  MACRO_INTEGER(8)
  MACRO_INTEGER(16)
  MACRO_INTEGER(32)
  MACRO_INTEGER(64)

#undef MACRO_INTEGER

  // Short names
#define MACRO_SHORT_NAME(size)					\
  using s##size  = Integer<size, false>::Signed;		\
  using u##size  = Integer<size, false>::Unsigned;		\
  using sf##size = Integer<size, true>::Signed;			\
  using uf##size = Integer<size, true>::Unsigned;

  MACRO_SHORT_NAME(8)
  MACRO_SHORT_NAME(16)
  MACRO_SHORT_NAME(32)
  MACRO_SHORT_NAME(64)

#undef MACRO_SHORT_NAME

  using usys = uintptr_t;
  using ssys = intptr_t;

}

#ifndef AVERSIVE_DISABLE_BASE_DEFAULT
using namespace Base;
#endif//AVERSIVE_DISABLE_BASE_DEFAULT

#endif//HDL_COMMON_INTEGER_HPP
