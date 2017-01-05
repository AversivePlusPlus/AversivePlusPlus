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
#ifndef HDL_AVR_MEGA_XX0_1_UART_MODULES_HPP
#define HDL_AVR_MEGA_XX0_1_UART_MODULES_HPP

#include "regs.hpp"
#include "fields.hpp"
#include "defs.hpp"

namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {

      namespace UART {

	//! \brief This is the final UART module structure, which implements the HDL structure specification
	template<typename Defs>
	struct _UART : UART_ModuleRegisters<Defs> {
	  struct Fields : UART_ModuleFields<Defs> {};
	};
      }
    }

    //! \brief This is the final UART module structure, associated with an ID
    template<u8 ID> struct UART : Private::UART::_UART<Private::UART::_UART_Defs<ID>> {};

    using UART_0 = UART<0>;
    using UART_1 = UART<1>;
    using UART_2 = UART<2>;
    
#if defined(__ATmegaxx0__)
    using UART_3 = UART<3>;
#endif   //(__ATmegaxx0__)
  }
}

#endif//HDL_AVR_MEGA_XX0_1_UART_MODULES_HPP
