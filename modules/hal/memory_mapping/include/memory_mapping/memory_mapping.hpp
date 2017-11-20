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
#ifndef MEMORY_MAPPING_HPP
#define MEMORY_MAPPING_HPP

#include <base/integer.hpp>

using namespace Aversive::Base;

namespace MemoryMapping {

  template<typename RegType, typename Group> struct Register;
  template<typename RegType, typename Group, int BITNUM, usys ADDRESS> struct BitField;
  template<typename RegType, typename Group, RegType MASK> struct Field;
  template<typename RegType, typename Group, RegType MASK> struct Config;

  template<typename Field, typename ... Next> struct VirtualField;
  template<typename Config, typename ... Next> struct VirtualConfig;

  // Aliases
  //// Register
  template<typename Group> using Register8  = Register<u8 , Group>;
  template<typename Group> using Register16 = Register<u16, Group>;
  template<typename Group> using Register32 = Register<u32, Group>;
  template<typename Group> using Register64 = Register<u64, Group>;

  //// Config
  template<typename Group, u8  MASK> using Config8  = Config<u8 , Group, MASK>;
  template<typename Group, u16 MASK> using Config16 = Config<u16, Group, MASK>;
  template<typename Group, u32 MASK> using Config32 = Config<u32, Group, MASK>;
  template<typename Group, u64 MASK> using Config64 = Config<u64, Group, MASK>;

  //// Field
  template<typename Group, u8  MASK> using Field8  = Field<u8 , Group, MASK>;
  template<typename Group, u16 MASK> using Field16 = Field<u16, Group, MASK>;
  template<typename Group, u32 MASK> using Field32 = Field<u32, Group, MASK>;
  template<typename Group, u64 MASK> using Field64 = Field<u64, Group, MASK>;

  //// BitField
  template<typename Group, int BITNUM, usys ADDRESS> using BitField8  = BitField<u8 , Group, BITNUM, ADDRESS>;
  template<typename Group, int BITNUM, usys ADDRESS> using BitField16 = BitField<u16, Group, BITNUM, ADDRESS>;
  template<typename Group, int BITNUM, usys ADDRESS> using BitField32 = BitField<u32, Group, BITNUM, ADDRESS>;
  template<typename Group, int BITNUM, usys ADDRESS> using BitField64 = BitField<u64, Group, BITNUM, ADDRESS>;


  //! \brief Everithing inside this namespace should not be used ouside of the MemoryMapping namespace
  namespace Private {
    //! \brief This is a recursive function that computes a Register value from a Field MASK and an integer value
    template<typename RegType>
    inline constexpr RegType  field_value(const RegType mask, const RegType value, const RegType res = 0, const int offset = 0) {
      return (mask)?field_value(mask>>1, (mask&1)?value>>1:value, res | ((value & mask & 1)<<offset), offset+1):res;
    }
  }

  template<typename T>
  static inline constexpr T UNSIGNED_INTEGER_MAX(void) {
    return (T)((unsigned long)sizeof(T)<<8) - 1;
  }

}

#include "register.hpp"
#include "config.hpp"
#include "field.hpp"
#include "bitfield.hpp"
#include "virtual_field.hpp"
#include "virtual_config.hpp"

#endif//MEMORY_MAPPING_HPP
