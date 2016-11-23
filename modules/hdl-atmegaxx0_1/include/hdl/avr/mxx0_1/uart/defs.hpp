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
#ifndef HDL_AVR_MEGA_XX0_1_UART_DEFS_HPP
#define HDL_AVR_MEGA_XX0_1_UART_DEFS_HPP


namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {
      using namespace ::HDL::AVR::Private;

      namespace SimpleDefs {

	//! \brief UART common modules definitions
	struct UART_Common_ModuleDefs {
	  //! \brief Common groups
	  struct Groups {
	    struct CSR_A;
	    struct CSR_B;
	    struct CSR_C;
	
	    struct BRR;
	    struct BRR_L;
	    struct BRR_H;

	    struct DR;
	  };
      
	  //! \name CSR_A Register Bits
	  //! @{
	  static constexpr u8 RXC  = 7;
	  static constexpr u8 TXC  = 6;
	  static constexpr u8 DRE  = 5;
	  static constexpr u8 FE   = 4;
	  static constexpr u8 DOR  = 3;
	  static constexpr u8 PE   = 2;
	  static constexpr u8 U2X  = 1;
	  static constexpr u8 MPCM = 0;
	  //! @}
      
	  //! \name CSR_B Register Bits
	  //! @{
	  static constexpr u8 RXCIE = 7;
	  static constexpr u8 TXCIE = 6;
	  static constexpr u8 DRIE  = 5;
	  static constexpr u8 RXEN  = 4;
	  static constexpr u8 TXEN  = 3;
	  static constexpr u8 RXB8  = 1;
	  static constexpr u8 TXB8  = 0;
	  //! @}

	  //! \name CSR_B Register Fields
	  //! @{
	  static constexpr u8 CSZ_2 = 0b00000100;
      	  //! @}

	  //! \name CSR_C Register Bits
	  //! @{
	  static constexpr u8 SBS  = 3;
	  static constexpr u8 CPOL = 0;
	  //! @}

	  //! \name CSR_C Register Fields
	  //! @{
	  static constexpr u8 MSEL    = 0b11000000;
	  static constexpr u8 PM      = 0b00110000;
	  static constexpr u8 CSZ_0_1 = 0b00000110;
	  //! @}
	};
    
	//! \brief UART 0 module definitions
	struct UART_0_ModuleDefs : UART_Common_ModuleDefs {
	  static constexpr usys CSR_A = SFR_MEM(0x00C0);
	  static constexpr usys CSR_B = SFR_MEM(0x00C1);
	  static constexpr usys CSR_C = SFR_MEM(0x00C2);

	  static constexpr usys BRR   = SFR_MEM(0x00C4);
	  static constexpr usys BRR_L = SFR_MEM(0x00C4);
	  static constexpr usys BRR_H = SFR_MEM(0x00C5);

	  static constexpr usys DR    = SFR_MEM(0x00C6);
	};

	//! \brief UART 1 module definitions
	struct UART_1_ModuleDefs : UART_Common_ModuleDefs {
	  static constexpr usys CSR_A = SFR_MEM(0x00C8);
	  static constexpr usys CSR_B = SFR_MEM(0x00C9);
	  static constexpr usys CSR_C = SFR_MEM(0x00CA);

	  static constexpr usys BRR   = SFR_MEM(0x00CC);
	  static constexpr usys BRR_L = SFR_MEM(0x00CC);
	  static constexpr usys BRR_H = SFR_MEM(0x00CD);

	  static constexpr usys DR    = SFR_MEM(0x00CE);
	};

#if defined(__ATmegaxx0__)
    
	//! \brief UART 2 module definitions
	struct UART_2_ModuleDefs : UART_Common_ModuleDefs {
	  static constexpr usys CSR_A = SFR_MEM(0x00D0);
	  static constexpr usys CSR_B = SFR_MEM(0x00D1);
	  static constexpr usys CSR_C = SFR_MEM(0x00D2);

	  static constexpr usys BRR   = SFR_MEM(0x00D4);
	  static constexpr usys BRR_L = SFR_MEM(0x00D4);
	  static constexpr usys BRR_H = SFR_MEM(0x00D5);

	  static constexpr usys DR    = SFR_MEM(0x00D6);
	};

	//! \brief UART 3 module definitions
	struct UART_3_ModuleDefs : UART_Common_ModuleDefs {
	  static constexpr usys CSR_A = SFR_MEM(0x0130);
	  static constexpr usys CSR_B = SFR_MEM(0x0131);
	  static constexpr usys CSR_C = SFR_MEM(0x0132);

	  static constexpr usys BRR   = SFR_MEM(0x0134);
	  static constexpr usys BRR_L = SFR_MEM(0x0134);
	  static constexpr usys BRR_H = SFR_MEM(0x0135);

	  static constexpr usys DR    = SFR_MEM(0x0136);
	};

#endif   //(__ATmegaxx0__)

      }
    }
  }
}


namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {

      namespace UART {
	//! \brief This class associate a UART module definitions to a number
	template<u8 ID> struct _UART_Defs { static_assert(!ID && ID, "Invalid UART"); };
	template<> struct _UART_Defs<0> : UART_0_ModuleDefs {};
	template<> struct _UART_Defs<1> : UART_1_ModuleDefs {};
	
#if defined(__ATmegaxx0__)
	template<> struct _UART_Defs<2> : UART_2_ModuleDefs {};
	template<> struct _UART_Defs<3> : UART_3_ModuleDefs {};
#endif   //(__ATmegaxx0__)
      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_UART_DEFS_HPP
