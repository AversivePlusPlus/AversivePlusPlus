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
#ifndef HDL_AVR_MEGA_XX0_1_TIMER_MODULES_HPP
#define HDL_AVR_MEGA_XX0_1_TIMER_MODULES_HPP

#include "regs.hpp"
#include "fields.hpp"
#include "defs.hpp"


namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {

      namespace TIMER {

	//! \brief This is the final TIMER module structure, which implements the HDL structure specification
	template<typename Defs>
	struct _TIMER : TIMER_ModuleRegisters<Defs>::Registers {
	  struct Fields : TIMER_ModuleFields<Defs>::Fields {};
	};

      }
    }

    //! \brief This is the final TIMER module structure, associated with an ID
    template<u8 ID> struct TIMER : Private::TIMER::_TIMER<Private::TIMER::_TIMER_Defs<ID>> {};

    using TIMER_0 = TIMER<0>;
    using TIMER_1 = TIMER<1>;
    using TIMER_2 = TIMER<2>;
    using TIMER_3 = TIMER<3>;
    using TIMER_4 = TIMER<4>;
    using TIMER_5 = TIMER<5>;

  }
}

#endif//HDL_AVR_MEGA_XX0_1_TIMER_MODULES_HPP
