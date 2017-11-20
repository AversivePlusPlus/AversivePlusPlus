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
#ifndef HDL_AVR_MEGA_XX0_1_UART_REGS_HPP
#define HDL_AVR_MEGA_XX0_1_UART_REGS_HPP

#include <memory_mapping/memory_mapping.hpp>
#include <base/dummy.hpp>


namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {
      using namespace ::MemoryMapping;
      
      namespace UART {

	//! \brief Here are defined UART module Registers, this class will be incorporated in the final UART Module
	template<typename ModuleDefs>
	struct UART_ModuleRegisters {
	  using Defs = ModuleDefs;

	  static constexpr Register8<typename Defs::Groups::CSR_A> CSR_A = Defs::CSR_A;
	  static constexpr Register8<typename Defs::Groups::CSR_B> CSR_B = Defs::CSR_B;
	  static constexpr Register8<typename Defs::Groups::CSR_C> CSR_C = Defs::CSR_C;

	  static constexpr Register8<typename Defs::Groups::BRR> BRR = Defs::BRR;
	  static constexpr Register8<typename Defs::Groups::BRR_L> BRR_L = Defs::BRR_L;
	  static constexpr Register8<typename Defs::Groups::BRR_H> BRR_H = Defs::BRR_H;

	  static constexpr Register8<typename Defs::Groups::DR> DR = Defs::DR;
	};

      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_UART_REGS_HPP
