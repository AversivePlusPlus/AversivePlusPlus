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
#ifndef HDL_AVR_MEGA_XX0_1_GPIO_FIELDS_HPP
#define HDL_AVR_MEGA_XX0_1_GPIO_FIELDS_HPP

#include "regs.hpp"
#include <memory_mapping/memory_mapping.hpp>
#include <base/dummy.hpp>


namespace HDL {

  namespace ATMegaxx0_1 {

    namespace Private {

      namespace GPIO {

	//! \brief Here are defined GPIO module Templated Fields, this class will be incorporated in the final GPIO Module
	template<typename ModuleDefs>
	struct GPIO_ModuleFields {
	  using Defs = ModuleDefs;
	  using Registers = GPIO_ModuleRegisters<Defs>;

	  template<u8 PIN_NUM> struct Check {
	    static_assert(Defs::PIN_MASK & (1 << PIN_NUM), "Invalid PIN_NUM");
	  };

	  template<u8 PIN_NUM>
	  struct PIN : Check<PIN_NUM> {
	    static constexpr BitField8<typename Defs::Groups::PIN, PIN_NUM, Registers::PIN.ADDRESS> field{};
	  };

	  template<u8 PIN_NUM>
	  struct DDR : Check<PIN_NUM> {
	    static constexpr BitField8<typename Defs::Groups::DDR, PIN_NUM, Registers::DDR.ADDRESS> field{};
	  };

	  template<u8 PIN_NUM>
	  struct PORT : Check<PIN_NUM> {
	    static constexpr BitField8<typename Defs::Groups::PORT, PIN_NUM, Registers::PORT.ADDRESS> field{};
	  };
	};

	//! \brief Here are defined GPIO module Aliases for Templated Fields, this class will be incorporated in the final GPIO Module as a Field collection
	/*!
	 * The Aliases are splitted into 3 sub-structures, that will be fusioned in the final GPIO Module
	 */
	template<typename ModuleDefs>
	struct GPIO_ModuleAliases {
	  using Defs = ModuleDefs;
	  using Fields = GPIO_ModuleFields<Defs>;

	  template<u8 MASK = Defs::PIN_MASK, DummyType DUMMY = DUMMY_VALUE> struct _PIN_Fields {};
	  template<u8 MASK = Defs::PIN_MASK, DummyType DUMMY = DUMMY_VALUE> struct _DDR_Fields {};
	  template<u8 MASK = Defs::PIN_MASK, DummyType DUMMY = DUMMY_VALUE> struct _PORT_Fields {};

	  //! \brief PIN Fields Definitions (6 pins case)
	  template<DummyType DUMMY>
	  struct _PIN_Fields<0b00111111, DUMMY> {
	    static constexpr auto& PIN_0 = Fields::template PIN<0>::field;
	    static constexpr auto& PIN_1 = Fields::template PIN<1>::field;
	    static constexpr auto& PIN_2 = Fields::template PIN<2>::field;
	    static constexpr auto& PIN_3 = Fields::template PIN<3>::field;
	    static constexpr auto& PIN_4 = Fields::template PIN<4>::field;
	    static constexpr auto& PIN_5 = Fields::template PIN<5>::field;
	  };

	  //! \brief PIN Fields Definitions (8 pins case)
	  template<DummyType DUMMY>
	  struct _PIN_Fields<0b11111111, DUMMY> : _PIN_Fields<0b00111111, DUMMY> {
	    static constexpr auto& PIN_6 = Fields::template PIN<6>::field;
	    static constexpr auto& PIN_7 = Fields::template PIN<7>::field;
	  };

	  //! \brief DDR Fields Definitions (6 pins case)
	  template<DummyType DUMMY>
	  struct _DDR_Fields<0b00111111, DUMMY> {
	    static constexpr auto& DDR_0 = Fields::template DDR<0>::field;
	    static constexpr auto& DDR_1 = Fields::template DDR<1>::field;
	    static constexpr auto& DDR_2 = Fields::template DDR<2>::field;
	    static constexpr auto& DDR_3 = Fields::template DDR<3>::field;
	    static constexpr auto& DDR_4 = Fields::template DDR<4>::field;
	    static constexpr auto& DDR_5 = Fields::template DDR<5>::field;
	  };

	  //! \brief DDR Fields Definitions (8 pins case)
	  template<DummyType DUMMY>
	  struct _DDR_Fields<0b11111111, DUMMY> : _DDR_Fields<0b00111111, DUMMY> {
	    static constexpr auto& DDR_6 = Fields::template DDR<6>::field;
	    static constexpr auto& DDR_7 = Fields::template DDR<7>::field;
	  };

	  //! \brief PORT Fields Definitions (6 pins case)
	  template<DummyType DUMMY>
	  struct _PORT_Fields<0b00111111, DUMMY> {
	    static constexpr auto& PORT_0 = Fields::template PORT<0>::field;
	    static constexpr auto& PORT_1 = Fields::template PORT<1>::field;
	    static constexpr auto& PORT_2 = Fields::template PORT<2>::field;
	    static constexpr auto& PORT_3 = Fields::template PORT<3>::field;
	    static constexpr auto& PORT_4 = Fields::template PORT<4>::field;
	    static constexpr auto& PORT_5 = Fields::template PORT<5>::field;
	  };

	  //! \brief PORT Fields Definitions (8 pins case)
	  template<DummyType DUMMY>
	  struct _PORT_Fields<0b11111111, DUMMY> : _PORT_Fields<0b00111111, DUMMY> {
	    static constexpr auto& PORT_6 = Fields::template PORT<6>::field;
	    static constexpr auto& PORT_7 = Fields::template PORT<7>::field;
	  };

	  using PIN_Fields = _PIN_Fields<Defs::PIN_MASK>;
	  using DDR_Fields = _DDR_Fields<Defs::PIN_MASK>;
	  using PORT_Fields = _PORT_Fields<Defs::PIN_MASK>;
	};
      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_GPIO_FIELDS_HPP
