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
#ifndef HDL_AVR_MEGA_XX0_1_TIMER_REGS_HPP
#define HDL_AVR_MEGA_XX0_1_TIMER_REGS_HPP

#include <memory_mapping/memory_mapping.hpp>
#include <base/dummy.hpp>

namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {
      using namespace ::MemoryMapping;

      namespace TIMER {
	
	//! \brief Here are defined TIMER module Registers, this class will be incorporated in the final TIMER Module
	/*!
	 * The registers are splitted into 2 cases : 8-bits and 16-bits
	 */
	template<typename ModuleDefs>
	struct TIMER_ModuleRegisters {
	  using Defs = ModuleDefs;

	  template<u8 BITS, DummyType DUMMY = DUMMY_VALUE> struct _Registers {};

	  //! \brief 8-bits specisalization
	  template<DummyType DUMMY>
	  struct _Registers<8, DUMMY> {
	    static constexpr Register8<typename Defs::Groups::IMSK> IFR  = Defs::IFR;
	    static constexpr Register8<typename Defs::Groups::IMSK> IMSK = Defs::IMSK;
      
	    static constexpr Register8<typename Defs::Groups::CCR_A> CCR_A = Defs::CCR_A;
	    static constexpr Register8<typename Defs::Groups::CCR_B> CCR_B = Defs::CCR_B;
      
	    static constexpr Register8<typename Defs::Groups::CNT> CNT   = Defs::CNT;
	    static constexpr Register8<typename Defs::Groups::CNT> OCR_A = Defs::OCR_A;
	    static constexpr Register8<typename Defs::Groups::CNT> OCR_B = Defs::OCR_B;

	    template<u8 OC_ID, DummyType _DUMMY = DUMMY_VALUE> struct OCR { static_assert(!OC_ID && OC_ID, "Invalid OC_ID"); };

	    template<DummyType _DUMMY> struct OCR<0, _DUMMY> {
	      static constexpr auto& reg = OCR_A;
	    };

	    template<DummyType _DUMMY> struct OCR<1, _DUMMY> {
	      static constexpr auto& reg = OCR_B;
	    };
	  };

	  //! \brief 16-bits specisalization
	  template<DummyType DUMMY>
	  struct _Registers<16, DUMMY> {
	    static constexpr Register8<typename Defs::Groups::IMSK> IFR  = Defs::IFR;
	    static constexpr Register8<typename Defs::Groups::IMSK> IMSK = Defs::IMSK;
      
	    static constexpr Register8<typename Defs::Groups::CCR_A> CCR_A = Defs::CCR_A;
	    static constexpr Register8<typename Defs::Groups::CCR_B> CCR_B = Defs::CCR_B;
	    static constexpr Register8<typename Defs::Groups::CCR_C> CCR_C = Defs::CCR_C;
      
	    static constexpr Register16<typename Defs::Groups::CNT16> CNT   = Defs::CNT;
	    static constexpr Register8<typename Defs::Groups::CNT_L> CNT_L = Defs::CNT_L;
	    static constexpr Register8<typename Defs::Groups::CNT_H> CNT_H = Defs::CNT_H;
      
	    static constexpr Register16<typename Defs::Groups::CNT16> ICR   = Defs::ICR;
	    static constexpr Register8<typename Defs::Groups::CNT_L> ICR_L = Defs::ICR_L;
	    static constexpr Register8<typename Defs::Groups::CNT_H> ICR_H = Defs::ICR_H;
      
	    static constexpr Register16<typename Defs::Groups::CNT16> OCR_A   = Defs::OCR_A;
	    static constexpr Register8<typename Defs::Groups::CNT_L> OCR_A_L = Defs::OCR_A_L;
	    static constexpr Register8<typename Defs::Groups::CNT_H> OCR_A_H = Defs::OCR_A_H;

	    static constexpr Register16<typename Defs::Groups::CNT16> OCR_B   = Defs::OCR_B;
	    static constexpr Register8<typename Defs::Groups::CNT_L> OCR_B_L = Defs::OCR_B_L;
	    static constexpr Register8<typename Defs::Groups::CNT_H> OCR_B_H = Defs::OCR_B_H;
      
	    static constexpr Register16<typename Defs::Groups::CNT16> OCR_C   = Defs::OCR_C;
	    static constexpr Register8<typename Defs::Groups::CNT_L> OCR_C_L = Defs::OCR_C_L;
	    static constexpr Register8<typename Defs::Groups::CNT_H> OCR_C_H = Defs::OCR_C_H;

	    template<u8 OC_ID, DummyType _DUMMY = DUMMY_VALUE> struct OCR { static_assert(!OC_ID && OC_ID, "Invalid OC_ID"); };

	    template<DummyType _DUMMY> struct OCR<0, _DUMMY> {
	      static constexpr auto& reg = OCR_A;
	      static constexpr auto& reg_l = OCR_A_L;
	      static constexpr auto& reg_h = OCR_A_H;
	    };

	    template<DummyType _DUMMY> struct OCR<1, _DUMMY> {
	      static constexpr auto& reg = OCR_B;
	      static constexpr auto& reg_l = OCR_B_L;
	      static constexpr auto& reg_h = OCR_B_H;
	    };

	    template<DummyType _DUMMY> struct OCR<2, _DUMMY> {
	      static constexpr auto& reg = OCR_C;
	      static constexpr auto& reg_l = OCR_C_L;
	      static constexpr auto& reg_h = OCR_C_H;
	    };

	  };
    
	  using Registers = _Registers<Defs::BITS>;
	};
	
      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_TIMER_REGS_HPP
