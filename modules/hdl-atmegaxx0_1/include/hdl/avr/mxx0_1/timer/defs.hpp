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
#ifndef HDL_AVR_MEGA_XX0_1_TIMER_DEFS_HPP
#define HDL_AVR_MEGA_XX0_1_TIMER_DEFS_HPP

namespace HDL {
    
  namespace ATMegaxx0_1 {  
  
    namespace Private {
      using namespace ::HDL::AVR::Private;
      
      namespace SimpleDefs {

	//! \brief TIMER common modules definitions (8-bits case)
	struct TIMER_8bits_ModuleDefs {
	  //! \brief This is used for template specification
	  static constexpr u8 BITS = 8;

	  //! \brief Common groups
	  struct Groups {
	    struct IMSK;

	    struct CCR_A;
	    struct CCR_B;

	    struct CNT;
	  };

	  //! \name IFR Register Bits
	  //! @{
	  static constexpr u8 TOV   = 0;
	  static constexpr u8 OCF_A = 1;
	  static constexpr u8 OCF_B = 2;
	  //! @}

	  //! \name CCR_A Register Fields
	  //! @{
	  static constexpr u8 COM_A     = 0b11000000;
	  static constexpr u8 COM_B     = 0b00110000;
	  static constexpr u8 CCR_A_WGM = 0b00000011;
	  //! @}
    
	  //! \name CCR_B Register Fields
	  //! @{
	  static constexpr u8 CS        = 0b00000111;
	  static constexpr u8 CCR_B_WGM = 0b00001000;
	  //! @}

	  //! \name CCR_B Register Bits
	  //! @{
	  static constexpr u8 FOC_A = 7;
	  static constexpr u8 FOC_B = 6;
	  //! @}

	  //! \name IMSK Register Bits
	  //! @{
	  static constexpr u8 TOIE   = 0;
	  static constexpr u8 OCIE_A = 1;
	  static constexpr u8 OCIE_B = 2;
	  //! @}
	};

	//! \brief TIMER common modules definitions (16-bits case)
	struct TIMER_16bits_ModuleDefs {
	  //! \brief This is used for template specification
	  static constexpr u8 BITS = 16;

	  //! \brief Common groups
	  struct Groups {
	    struct IMSK;

	    struct CCR_A;
	    struct CCR_B;
	    struct CCR_C;

	    struct CNT16;
	    struct CNT_L;
	    struct CNT_H;
	  };

	  //! \name IFR Register Bits
	  //! @{
	  static constexpr u8 TOV   = 0;
	  static constexpr u8 OCF_A = 1;
	  static constexpr u8 OCF_B = 2;
	  static constexpr u8 OCF_C = 3;
	  static constexpr u8 ICF   = 5;
	  //! @}
    
	  //! \name IMSK Register Bits
	  //! @{
	  static constexpr u8 TOIE   = 0;
	  static constexpr u8 OCIE_A = 1;
	  static constexpr u8 OCIE_B = 2;
	  static constexpr u8 OCIE_C = 3;
	  static constexpr u8 ICIE   = 5;
	  //! @}

	  //! \name CCR_A Register Fields
	  //! @{
	  static constexpr u8 COM_A     = 0b11000000;
	  static constexpr u8 COM_B     = 0b00110000;
	  static constexpr u8 COM_C     = 0b00001100;
	  static constexpr u8 CCR_A_WGM = 0b00000011;
	  //! @}
    
	  //! \name CCR_B Register Fields
	  //! @{
	  static constexpr u8 CS        = 0b00000111;
	  static constexpr u8 CCR_B_WGM = 0b00011000;
	  //! @}

	  //! \name CCR_B Register Bits
	  //! @{
	  static constexpr u8 ICNC = 7;
	  static constexpr u8 ICES = 6;
	  //! @}
    
	  //! \name CCR_C Register Bits
	  //! @{
	  static constexpr u8 FOC_A = 7;
	  static constexpr u8 FOC_B = 6;
	  static constexpr u8 FOC_C = 5;
	  //! @}
	};

	//! \brief TIMER 0 (8-bits) module definitions
	struct TIMER_0_ModuleDefs : TIMER_8bits_ModuleDefs {
	  static constexpr usys IFR   = SFR_IO(0x0015);
	  static constexpr usys IMSK  = SFR_MEM(0x006E);

	  static constexpr usys CCR_A = SFR_IO(0x0024);
	  static constexpr usys CCR_B = SFR_IO(0x0025);

	  static constexpr usys CNT   = SFR_IO(0x0026);
	  static constexpr usys OCR_A = SFR_IO(0x0027);
	  static constexpr usys OCR_B = SFR_IO(0x0028);
	};

	//! \brief TIMER 1 (16-bits) module definitions
	struct TIMER_1_ModuleDefs : TIMER_16bits_ModuleDefs {
	  static constexpr usys IFR   = SFR_IO(0x0016);
	  static constexpr usys IMSK  = SFR_MEM(0x006F);

	  static constexpr usys CCR_A = SFR_MEM(0x0080);
	  static constexpr usys CCR_B = SFR_MEM(0x0081);
	  static constexpr usys CCR_C = SFR_MEM(0x0082);

	  static constexpr usys CNT   = SFR_MEM(0x0084);
	  static constexpr usys CNT_L = SFR_MEM(0x0084);
	  static constexpr usys CNT_H = SFR_MEM(0x0085);

	  static constexpr usys ICR   = SFR_MEM(0x0086);
	  static constexpr usys ICR_L = SFR_MEM(0x0086);
	  static constexpr usys ICR_H = SFR_MEM(0x0087);
    
	  static constexpr usys OCR_A   = SFR_MEM(0x0088);
	  static constexpr usys OCR_A_L = SFR_MEM(0x0088);
	  static constexpr usys OCR_A_H = SFR_MEM(0x0089);
    
	  static constexpr usys OCR_B   = SFR_MEM(0x008A);
	  static constexpr usys OCR_B_L = SFR_MEM(0x008A);
	  static constexpr usys OCR_B_H = SFR_MEM(0x008B);
    
	  static constexpr usys OCR_C   = SFR_MEM(0x008C);
	  static constexpr usys OCR_C_L = SFR_MEM(0x008C);
	  static constexpr usys OCR_C_H = SFR_MEM(0x008D);
	};
  
	//! \brief TIMER 2 (8-bits) module definitions
	struct TIMER_2_ModuleDefs : TIMER_8bits_ModuleDefs {
	  static constexpr usys IFR   = SFR_IO(0x0017);
	  static constexpr usys IMSK  = SFR_MEM(0x0070);

	  static constexpr usys CCR_A = SFR_MEM(0x00B0);
	  static constexpr usys CCR_B = SFR_MEM(0x00B1);

	  static constexpr usys CNT   = SFR_MEM(0x00B2);
	  static constexpr usys OCR_A = SFR_MEM(0x00B3);
	  static constexpr usys OCR_B = SFR_MEM(0x00B4);
	};
  
	//! \brief TIMER 3 (16-bits) module definitions
	struct TIMER_3_ModuleDefs : TIMER_16bits_ModuleDefs {
	  static constexpr usys IFR   = SFR_IO(0x0018);
	  static constexpr usys IMSK  = SFR_MEM(0x0071);

	  static constexpr usys CCR_A = SFR_MEM(0x0090);
	  static constexpr usys CCR_B = SFR_MEM(0x0091);
	  static constexpr usys CCR_C = SFR_MEM(0x0092);

	  static constexpr usys CNT   = SFR_MEM(0x0094);
	  static constexpr usys CNT_L = SFR_MEM(0x0094);
	  static constexpr usys CNT_H = SFR_MEM(0x0095);

	  static constexpr usys ICR   = SFR_MEM(0x0096);
	  static constexpr usys ICR_L = SFR_MEM(0x0096);
	  static constexpr usys ICR_H = SFR_MEM(0x0097);
    
	  static constexpr usys OCR_A   = SFR_MEM(0x0098);
	  static constexpr usys OCR_A_L = SFR_MEM(0x0098);
	  static constexpr usys OCR_A_H = SFR_MEM(0x0099);
    
	  static constexpr usys OCR_B   = SFR_MEM(0x009A);
	  static constexpr usys OCR_B_L = SFR_MEM(0x009A);
	  static constexpr usys OCR_B_H = SFR_MEM(0x009B);
    
	  static constexpr usys OCR_C   = SFR_MEM(0x009C);
	  static constexpr usys OCR_C_L = SFR_MEM(0x009C);
	  static constexpr usys OCR_C_H = SFR_MEM(0x009D);
	};
  
	//! \brief TIMER 4 (16-bits) module definitions
	struct TIMER_4_ModuleDefs : TIMER_16bits_ModuleDefs {
	  static constexpr usys IFR   = SFR_IO(0x0019);
	  static constexpr usys IMSK  = SFR_MEM(0x0072);

	  static constexpr usys CCR_A = SFR_MEM(0x00A0);
	  static constexpr usys CCR_B = SFR_MEM(0x00A1);
	  static constexpr usys CCR_C = SFR_MEM(0x00A2);

	  static constexpr usys CNT   = SFR_MEM(0x00A4);
	  static constexpr usys CNT_L = SFR_MEM(0x00A4);
	  static constexpr usys CNT_H = SFR_MEM(0x00A5);

	  static constexpr usys ICR   = SFR_MEM(0x00A6);
	  static constexpr usys ICR_L = SFR_MEM(0x00A6);
	  static constexpr usys ICR_H = SFR_MEM(0x00A7);
    
	  static constexpr usys OCR_A   = SFR_MEM(0x00A8);
	  static constexpr usys OCR_A_L = SFR_MEM(0x00A8);
	  static constexpr usys OCR_A_H = SFR_MEM(0x00A9);
    
	  static constexpr usys OCR_B   = SFR_MEM(0x00AA);
	  static constexpr usys OCR_B_L = SFR_MEM(0x00AA);
	  static constexpr usys OCR_B_H = SFR_MEM(0x00AB);
    
	  static constexpr usys OCR_C   = SFR_MEM(0x00AC);
	  static constexpr usys OCR_C_L = SFR_MEM(0x00AC);
	  static constexpr usys OCR_C_H = SFR_MEM(0x00AD);
	};
  
	//! \brief TIMER 5 (16-bits) module definitions
	struct TIMER_5_ModuleDefs : TIMER_16bits_ModuleDefs {
	  static constexpr usys IFR   = SFR_IO(0x001A);
	  static constexpr usys IMSK  = SFR_MEM(0x0073);

	  static constexpr usys CCR_A = SFR_MEM(0x0120);
	  static constexpr usys CCR_B = SFR_MEM(0x0121);
	  static constexpr usys CCR_C = SFR_MEM(0x0122);

	  static constexpr usys CNT   = SFR_MEM(0x0124);
	  static constexpr usys CNT_L = SFR_MEM(0x0124);
	  static constexpr usys CNT_H = SFR_MEM(0x0125);

	  static constexpr usys ICR   = SFR_MEM(0x0126);
	  static constexpr usys ICR_L = SFR_MEM(0x0126);
	  static constexpr usys ICR_H = SFR_MEM(0x0127);
    
	  static constexpr usys OCR_A   = SFR_MEM(0x0128);
	  static constexpr usys OCR_A_L = SFR_MEM(0x0128);
	  static constexpr usys OCR_A_H = SFR_MEM(0x0129);
    
	  static constexpr usys OCR_B   = SFR_MEM(0x012A);
	  static constexpr usys OCR_B_L = SFR_MEM(0x012A);
	  static constexpr usys OCR_B_H = SFR_MEM(0x012B);
    
	  static constexpr usys OCR_C   = SFR_MEM(0x012C);
	  static constexpr usys OCR_C_L = SFR_MEM(0x012C);
	  static constexpr usys OCR_C_H = SFR_MEM(0x012D);
	};
  
      }
    }
  }
}


namespace HDL {
    
  namespace ATMegaxx0_1 {  

    namespace Private {

      namespace TIMER {
	//! \brief This class associate a TIMER module definitions to a number
	template<u8 ID> struct _TIMER_Defs { static_assert(!ID && ID, "Invalid TIMER"); };
	template<> struct _TIMER_Defs<0> : TIMER_0_ModuleDefs {};
	template<> struct _TIMER_Defs<1> : TIMER_1_ModuleDefs {};
	template<> struct _TIMER_Defs<2> : TIMER_2_ModuleDefs {};
	template<> struct _TIMER_Defs<3> : TIMER_3_ModuleDefs {};
	template<> struct _TIMER_Defs<4> : TIMER_4_ModuleDefs {};
	template<> struct _TIMER_Defs<5> : TIMER_5_ModuleDefs {};
	
      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_TIMER_DEFS_HPP
