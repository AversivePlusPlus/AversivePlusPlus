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
#ifndef HDL_AVR_MEGA_XX0_1_EXT_DEFS_HPP
#define HDL_AVR_MEGA_XX0_1_EXT_DEFS_HPP

namespace HDL {
  
  namespace ATMegaxx0_1 {
      
    namespace Private {
      using namespace ::HDL::AVR::Private;
      
      namespace SimpleDefs {

	struct EXT_ModuleDefs {
	  //! \brief External interrupts groups
	  struct Groups {
	    struct EICR_A;
	    struct EICR_B;
	    struct EIMSK;
	    struct PCICR;
	    struct PCIFR;
	    struct PCMSK_0;
	    struct PCMSK_1;
#if defined(__ATmegaxx0__)
	    struct PCMSK_2;
#endif /* __ATmegaxx0__ */
	  };

	  //! \name Registers
	  //! @{
	  static constexpr usys PCIFR = SFR_IO(0x1B);
	  static constexpr usys EIFR  = SFR_IO(0x1C);
	  static constexpr usys EIMSK = SFR_IO(0x1D);
	  
	  static constexpr usys PCICR  = SFR_MEM(0x68);
	  static constexpr usys EICR_A = SFR_MEM(0x69);
	  static constexpr usys EICR_B = SFR_MEM(0x6A);

	  static constexpr usys PCMSK_0 = SFR_MEM(0x6B);
	  static constexpr usys PCMSK_1 = SFR_MEM(0x6C);
#if defined(__ATmegaxx0__)
	  static constexpr usys PCMSK_2 = SFR_MEM(0x6D);
#endif /* __ATmegaxx0__ */
	  //! @}

	  //! \name PCIFR Register Bits
	  //! @{
#if defined(__ATmegaxx0__)
	  static constexpr u8 PCIF_2 = 2;
#endif /* __ATmegaxx0__ */
	  static constexpr u8 PCIF_1 = 1;
	  static constexpr u8 PCIF_0 = 0;
	  //! @}

	  //! \name EIFR Register Bits
	  //! @{
	  static constexpr u8 INTF_7 = 7;
	  static constexpr u8 INTF_6 = 6;
	  static constexpr u8 INTF_5 = 5;
	  static constexpr u8 INTF_4 = 4;
	  static constexpr u8 INTF_3 = 3;
	  static constexpr u8 INTF_2 = 2;
	  static constexpr u8 INTF_1 = 1;
	  static constexpr u8 INTF_0 = 0;
	  //! @}

	  //! \name EIMSK Register Bits
	  //! @{
	  static constexpr u8 INT_7 = 7;
	  static constexpr u8 INT_6 = 6;
	  static constexpr u8 INT_5 = 5;
	  static constexpr u8 INT_4 = 4;
	  static constexpr u8 INT_3 = 3;
	  static constexpr u8 INT_2 = 2;
	  static constexpr u8 INT_1 = 1; 
	  static constexpr u8 INT_0 = 0;
	  //! @}

	  //! \name PCICR Register Bits
	  //! @{
#if defined(__ATmegaxx0__)
	  static constexpr u8 PCIE_2 = 2;
#endif /* __ATmegaxx0__ */
	  static constexpr u8 PCIE_1 = 1;
	  static constexpr u8 PCIE_0 = 0;
	  //! @}

	  //! \name EICRA Register Bits
	  //! @{
	  static constexpr u8 ISC_3 = 0b11000000; // 7 | 6
	  static constexpr u8 ISC_2 = 0b00110000; // 5 | 4
	  static constexpr u8 ISC_1 = 0b00001100; // 3 | 2
	  static constexpr u8 ISC_0 = 0b00000011; // 1 | 0
	  //! @}

	  //! \name EICRB Register Bits
	  //! @{
	  static constexpr u8 ISC_7 = 0b11000000; // 7 | 6
	  static constexpr u8 ISC_6 = 0b00110000; // 5 | 4
	  static constexpr u8 ISC_5 = 0b00001100; // 3 | 2
	  static constexpr u8 ISC_4 = 0b00000011; // 1 | 0
	  //! @}

	  //! \name PCMSK0 Register Bits
	  //! @{
	  static constexpr u8 PCINT_7 = 7;
	  static constexpr u8 PCINT_6 = 6;
	  static constexpr u8 PCINT_5 = 5;
	  static constexpr u8 PCINT_4 = 4;
	  static constexpr u8 PCINT_3 = 3;
	  static constexpr u8 PCINT_2 = 2;
	  static constexpr u8 PCINT_1 = 1;
	  static constexpr u8 PCINT_0 = 0;
	  //! @}

	  //! \name PCMSK1 Register Bits
	  //! @{
	  static constexpr u8 PCINT_15 = 7;
	  static constexpr u8 PCINT_14 = 6;
	  static constexpr u8 PCINT_13 = 5;
	  static constexpr u8 PCINT_12 = 4;
	  static constexpr u8 PCINT_11 = 3;
	  static constexpr u8 PCINT_10 = 2;
	  static constexpr u8 PCINT_9 = 1;
	  static constexpr u8 PCINT_8 = 0;
	  //! @}

#if defined(__ATmegaxx0__) 
	  //! \name PCMSK2 Register Bits
	  //! @{
	  static constexpr u8 PCINT_23 = 7;
	  static constexpr u8 PCINT_22 = 6;
	  static constexpr u8 PCINT_21 = 5;
	  static constexpr u8 PCINT_20 = 4;
	  static constexpr u8 PCINT_19 = 3;
	  static constexpr u8 PCINT_18 = 2;
	  static constexpr u8 PCINT_17 = 1;
	  static constexpr u8 PCINT_16 = 0;
#endif /* __ATmegaxx0__ */
	  //! @}
	  
	};
	
      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_EXT_DEFS_HPP
