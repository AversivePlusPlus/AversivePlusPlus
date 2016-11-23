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
#ifndef HDL_AVR_MEGA_XX0_1_UART_FIELDS_HPP
#define HDL_AVR_MEGA_XX0_1_UART_FIELDS_HPP

#include "regs.hpp"
#include <memory_mapping/memory_mapping.hpp>
#include <base/dummy.hpp>

namespace HDL {

  namespace ATMegaxx0_1 {

    namespace Private {

      namespace UART {

	//! \brief Here are defined UART module Fields, this class will be incorporated in the final UART Module
	template<typename ModuleDefs>
	struct UART_ModuleFields {
	  using Defs = ModuleDefs;
	  using Registers = UART_ModuleRegisters<Defs>;

	  //! \name CSR_A Register Bits
	  //! @{
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::RXC, Registers::CSR_A.ADDRESS>  RXC {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::TXC, Registers::CSR_A.ADDRESS>  TXC {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::DRE, Registers::CSR_A.ADDRESS>  DRE {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::FE, Registers::CSR_A.ADDRESS>   FE  {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::DOR, Registers::CSR_A.ADDRESS>  DOR {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::PE, Registers::CSR_A.ADDRESS>   PE  {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::U2X, Registers::CSR_A.ADDRESS>  U2X {};
	  static constexpr BitField8<typename Defs::Groups::CSR_A, Defs::MPCM, Registers::CSR_A.ADDRESS> MPCM{};
	  //! @}

	  //! \name CSR_B Register Bits
	  //! @{
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::RXCIE, Registers::CSR_B.ADDRESS> RXCIE{};
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::TXCIE, Registers::CSR_B.ADDRESS> TXCIE{};
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::DRIE, Registers::CSR_B.ADDRESS>  DRIE {};
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::RXEN, Registers::CSR_B.ADDRESS>  RXEN {};
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::TXEN, Registers::CSR_B.ADDRESS>  TXEN {};
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::RXB8, Registers::CSR_B.ADDRESS>  RXB8 {};
	  static constexpr BitField8<typename Defs::Groups::CSR_B, Defs::TXB8, Registers::CSR_B.ADDRESS>  TXB8 {};
	  //! @}

	  //! \name CSR_C Register Bits
	  //! @{
	  static constexpr BitField8<typename Defs::Groups::CSR_C, Defs::SBS, Registers::CSR_C.ADDRESS>  SBS {};
	  static constexpr BitField8<typename Defs::Groups::CSR_C, Defs::CPOL, Registers::CSR_C.ADDRESS> CPOL{};
	  //! @}

	  //! \name CSR_C Register Fields
	  //! @{
	  static constexpr Field8<typename Defs::Groups::CSR_C, Defs::MSEL> MSEL = Registers::CSR_C;
	  static constexpr Field8<typename Defs::Groups::CSR_C, Defs::PM>   PM   = Registers::CSR_C;
	  //! @}

	  //! \name CSR_B_C Register Fields
	  //! @{
	  static constexpr Field8<typename Defs::Groups::CSR_B, Defs::CSZ_2>   CSZ_2   = Registers::CSR_B;
	  static constexpr Field8<typename Defs::Groups::CSR_C, Defs::CSZ_0_1> CSZ_0_1 = Registers::CSR_C;
	  static constexpr auto CSZ = make_virtual_field(CSZ_2, CSZ_0_1);
	  //! @}
	};

      }
    }
  }
}

#endif//HDL_AVR_MEGA_XX0_1_UART_FIELDS_HPP
