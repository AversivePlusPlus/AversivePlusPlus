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
#ifndef FIELD_HPP
#define FIELD_HPP

#include "memory_mapping.hpp"

namespace MemoryMapping {

  template<typename RegType, typename Group, RegType FIELD_MASK>
  constexpr inline RegType MASK(const Field<RegType, Group, FIELD_MASK>&) {
    return FIELD_MASK;
  }

  template<typename RegType, typename Group, RegType FIELD_MASK>
  constexpr inline Register<RegType, Group> REG(const Field<RegType, Group, FIELD_MASK>& field) {
    return field.REGISTER;
  }

  //! \brief This class represents a part of a Register
  //! \param RegType : the register integer type
  //! \param Group : the register group
  //! \param MASK : the mask that determines the bits of the Field
  /*!
   * A Field is a part of a Register, that can be manipulated as a variable (with less possibilities, however).
   */
  template<typename RegType, typename Group, RegType MASK>
  struct Field {
  public:
    //! \brief The Register which this Field belongs to
    const Register<RegType, Group>& REGISTER;

  public:
    //! \brief Constructor
    //! \param reg : The Register which this Field belongs to
    constexpr Field(const Register<RegType, Group>& reg)
      : REGISTER(reg) {
    }

    //! \brief Assignment operator for an incompatible Config.
    template<typename OtherRegType, typename OtherGroup, OtherRegType OTHER_MASK>
    const Field& operator=(const Config<OtherRegType, OtherGroup, OTHER_MASK>& cfg) const {
      static_assert(!sizeof(RegType) && sizeof(RegType), "Incompatible Field and Config");
      return *this;
    }

    //! \brief Assignment operator for a Config object.
    const Field& operator=(const Config<RegType, Group, MASK>& cfg) const {
      REGISTER = (REGISTER & (RegType)(~MASK)) | cfg.VALUE;
      return *this;
    }

    //! \brief Assignment operator for an incompatible Field.
    template<typename OtherRegType, typename OtherGroup, OtherRegType OTHER_MASK>
    const Field& operator=(const Field<OtherRegType, OtherGroup, OTHER_MASK>& field) const {
      static_assert(!sizeof(RegType) && sizeof(RegType), "Incompatible Fields");
      return *this;
    }

    //! \brief Assignment operator for an other Field.
    const Field& operator=(const Field<RegType, Group, MASK>& field) const {
      REGISTER = (REGISTER & (RegType)(~MASK)) | (field.REGISTER & MASK);
      return *this;
    }

    //! \brief Assignment operator for an integer value.
    //! \param val : An integer value (with some restrictions, see below)
    //! \warning The value is a value for the Field, not the Register.
    /*!
     * For example :
     *
     *         If the Field's MASK is 0b01011000 (the Register is on 1 Byte).
     *         It means that the Field can have values on 3 Bits
     *         So, a correct value of this field is between 0 and 0b111 (which is equal to 7).
     *
     *         Then, if the Field is assigned 0b101, the Register's value will be : 0bx1x01xxx
     *         (where "x" stands for the previous value of the Register's corresponding Bit)
     */
    const Field& operator=(const RegType val) const {
      (*this) = make_config(*this, val);
      return *this;
    }

#define MACRO_DEFINE_COMPAR(op)						\
    bool operator op(const Field& other) const {			\
      return (REGISTER & MASK) op (other.REGISTER & MASK);		\
    }									\
    bool operator op(const Config<RegType, Group, MASK>& cfg) const {	\
      return (REGISTER & MASK) op (cfg & MASK);				\
    }									\
    bool operator op(const RegType val) const {				\
      return *this op make_config(*this, val);				\
    }									\

    MACRO_DEFINE_COMPAR(==);
    MACRO_DEFINE_COMPAR(!=);

#undef MACRO_DEFINE_COMPAR
  };

}

#endif//FIELD_HPP
