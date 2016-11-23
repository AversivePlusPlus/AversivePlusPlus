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
#ifndef HAL_ATXMEGA_TRAITS_HPP
#define HAL_ATXMEGA_TRAITS_HPP

#include <avr/io.h>

namespace HAL {

  namespace ATxmega {

    namespace Private {

      enum HAL_Type { PORT, PIN, TIMER, PWM, UART };

      template<HAL_Type type, int ID>
      struct HAL_Identifier {
        constexpr inline operator int() { return ID; }
      };

      template<int ID> using HAL_PORT = HAL_Identifier<PORT, ID>;
      template<int ID> using HAL_PIN = HAL_Identifier<PIN, ID>;
      template<int ID> using HAL_TIMER = HAL_Identifier<TIMER, ID>;
      template<int ID> using HAL_PWM = HAL_Identifier<PWM, ID>;
      template<int ID> using HAL_UART = HAL_Identifier<UART, ID>;

    }

    namespace Private {

      static constexpr inline int pin(int port, int offset) {
        return port * 8 + offset;
      }

      static constexpr inline int port(int pin) {
        return pin / 8;
      }

      static constexpr inline int offset(int pin) {
        return pin % 8;
      }

    }

    static constexpr Private::HAL_PORT<0> A;
    static constexpr Private::HAL_PIN<Private::pin(0, 0)> A0;
    static constexpr Private::HAL_PIN<Private::pin(0, 1)> A1;
    static constexpr Private::HAL_PIN<Private::pin(0, 2)> A2;
    static constexpr Private::HAL_PIN<Private::pin(0, 3)> A3;
    static constexpr Private::HAL_PIN<Private::pin(0, 4)> A4;
    static constexpr Private::HAL_PIN<Private::pin(0, 5)> A5;
    static constexpr Private::HAL_PIN<Private::pin(0, 6)> A6;
    static constexpr Private::HAL_PIN<Private::pin(0, 7)> A7;

    namespace Private {

      static constexpr inline PORT_t& avr_io_port(int port) {
        return
            (port == 0) ? PORTA :
                          (*(PORT_t*)0);
      }

    }

  }

}

#endif//HAL_ATXMEGA_TRAITS_HPP
