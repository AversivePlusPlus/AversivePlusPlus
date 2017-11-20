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
#ifndef AVERSIVE_HAL_SWITCH_UART_HPP
#define AVERSIVE_HAL_SWITCH_UART_HPP

#ifdef  AVERSIVE_TOOLCHAIN_ATXMEGA
#include <hal/atxmega/uart.hpp>
namespace HAL { using namespace HAL::ATxmega; }
#endif//AVERSIVE_TOOLCHAIN_ATXMEGA


#ifdef  AVERSIVE_TOOLCHAIN_ATMEGAXX0_1
#include <hal/atmegaxx0_1/uart.hpp>
namespace HAL { using namespace HAL::ATMegaxx0_1; }
#endif//AVERSIVE_TOOLCHAIN_ATMEGAXX0_1


#ifdef  AVERSIVE_TOOLCHAIN_STM32F4
#include <hal/stm32cubef4/uart.hpp>
namespace HAL { using namespace HAL::STM32CubeF4; }
#endif//AVERSIVE_TOOLCHAIN_STM32F4

#endif//AVERSIVE_HAL_SWITCH_UART_HPP
