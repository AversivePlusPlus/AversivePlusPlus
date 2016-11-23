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
#ifndef BITFIELD_HPP
#define BITFIELD_HPP

#include "memory_mapping.hpp"

namespace MemoryMapping {

  namespace Private {

    template<int OFFSET, typename T, bool POSITIVE = false>
    struct RelativeOffsetHelper {
      static inline constexpr T run(T val) {
        return val >> -OFFSET;
      }
    };

    template<int OFFSET, typename T>
    struct RelativeOffsetHelper<OFFSET, T, true> {
      static inline constexpr T run(T val) {
        return val << OFFSET;
      }
    };

    template<int OFFSET, typename T>
    static inline constexpr T relative_offset(T val) {
      return RelativeOffsetHelper<OFFSET, T, (OFFSET >= 0)>::run(val);
    }

  }

  //! \brief This class is a part of a Register limited to one Bit
  //! \param RegType : the register integer type
  //! \param Group : the register group
  //! \param BITNUM : the bit number in the register
  /*!
   * A BitField is a part of a register, that can be manipulated as a boolean variable (with less possibilities, however).
   */
  template<typename RegType, typename Group, int BITNUM, usys ADDRESS>
  struct BitField {
  public:
    //! \brief The Register which this BitField belongs to
    constexpr Register<RegType, Group> reg(void) {
      return Register<RegType, Group>(ADDRESS);
    }

  public:
    //! \brief Cast operator
    operator bool(void) const {
      return reg() & (1 << BITNUM);
    }

    // Assignment

    //! \brief Assignment operator for a Config object.
    const BitField& operator=(const Config<RegType, Group, (1<<BITNUM)>& cfg) const {
      reg() = (reg() & ~(1 << BITNUM)) | cfg.VALUE;
      return *this;
    }

    //! \brief Assignment operator for an other BitField.
    /*!
     * This is a simplified version for the case where the bitfields have the same BITNUM.
     */
    template<usys BF_ADDRESS>
    const BitField& operator=(const BitField<RegType, Group, BITNUM, BF_ADDRESS>& bf) const {
      reg() = (reg() & ~(1 << BITNUM)) | (bf.reg() & (1 << BITNUM));
      return *this;
    }

    //! \brief Assignment operator for an other BitField.
    /*!
     * Unlike the other classes, BitFields can be used with any other BitField,
     * because a boolean is a boolean !
     */
    template<typename OtherRegType, typename OtherGroup, int OTHER_BITNUM, usys OTHER_ADDRESS>
    const BitField& operator=(const BitField<OtherRegType, OtherGroup, OTHER_BITNUM, OTHER_ADDRESS>& bf) const {
      reg() = (reg() & ~(1 << BITNUM)) | Private::relative_offset<(BITNUM - OTHER_BITNUM)>(bf.reg() & (1 << OTHER_BITNUM));
      return *this;
    }

    //! \brief Assignment operator for a bool value.
    const BitField& operator=(const bool val) const {
      if(val) {
        reg() |= (1 << BITNUM);
      }
      else {
        reg() &= (RegType)(~(1 << BITNUM));
      }
      return *this;
    }

    // Logic
#define MACRO_DEFINE_LOGIC(op)						\
    inline bool operator op(const Config<RegType, Group, (1<<BITNUM)>& cfg) const { \
      return ((bool)*this) op cfg;					\
    }									\
    template<typename OtherRegType, typename OtherGroup, int OTHER_BITNUM, usys OTHER_ADDRESS> \
    inline bool operator op(const BitField<OtherRegType, OtherGroup, OTHER_BITNUM, OTHER_ADDRESS>& bf) const { \
      return ((bool)*this) op ((bool)bf);				\
    }									\
    inline bool operator op(const bool val) const {			\
      return ((bool)*this) op val;					\
    }

    MACRO_DEFINE_LOGIC(&&);
    MACRO_DEFINE_LOGIC(||);

#undef MACRO_DEFINE_LOGIC

#define MACRO_DEFINE_COMPAR(op)						\
    template<RegType MASK>						\
    bool operator op(const Config<RegType, Group, MASK>& cfg) const {	\
      static_assert(MASK==1<<BITNUM,					\
                    "Invalid Config and BitField comparison");		\
      return (VAL(reg()) & MASK) op (VAL(cfg) & MASK);		\
    }									\
    bool operator op(const bool val) const {				\
      return val op *this;						\
    }									\

    MACRO_DEFINE_COMPAR(==);
    MACRO_DEFINE_COMPAR(!=);

#undef MACRO_DEFINE_COMPAR

  };

}

#endif//BITFIELD_HPP
