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
#ifndef HDL_AVR_MEGA_XX0_1_EXT_REGS_HPP
#define HDL_AVR_MEGA_XX0_1_EXT_REGS_HPP

#include <memory_mapping/memory_mapping.hpp>
#include <base/dummy.hpp>
#include "defs.hpp"

namespace HDL {
    
  namespace ATMegaxx0_1 {
    
    namespace Private {
      using namespace ::MemoryMapping;
      
      namespace EXT {
	
	template<DummyType DUMMY = DUMMY_VALUE>
	struct EXT_ModuleRegisters {
	  using Defs = SimpleDefs::EXT_ModuleDefs;

	  static constexpr Register8<typename Defs::Groups::PCIFR> PCIFR = Defs::PCIFR;
	  static constexpr Register8<typename Defs::Groups::EIMSK> EIFR = Defs::EIFR;
	  static constexpr Register8<typename Defs::Groups::EIMSK> EIMSK = Defs::EIMSK;
	  
	  static constexpr Register8<typename Defs::Groups::PCICR> PCICR = Defs::PCICR;
	  static constexpr Register8<typename Defs::Groups::EICR_A > EICR_A  = Defs::EICR_A ;
	  static constexpr Register8<typename Defs::Groups::EICR_B > EICR_B  = Defs::EICR_B ;

	  static constexpr Register8<typename Defs::Groups::PCMSK_0 > PCMSK_0  = Defs::PCMSK_0 ;
	  static constexpr Register8<typename Defs::Groups::PCMSK_1 > PCMSK_1  = Defs::PCMSK_1 ;
#if defined(__ATmegaxx0__)
	  static constexpr Register8<typename Defs::Groups::PCMSK_2 > PCMSK_2  = Defs::PCMSK_2 ;
#endif /* __ATmegaxx0__ */
	};
	
      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_EXT_REGS_HPP
