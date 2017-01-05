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
#ifndef HAL_ATMEGAXX0_1_TRAITS_HPP
#define HAL_ATMEGAXX0_1_TRAITS_HPP

//#include <avr/io.h>

namespace HAL {

  namespace ATMegaxx0_1 {

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

#define AVERSIVE_DEFINE_PORT(letter, num) \
    static constexpr Private::HAL_PORT<num> letter; \
    static constexpr Private::HAL_PIN<Private::pin(num, 0)> letter##0; \
    static constexpr Private::HAL_PIN<Private::pin(num, 1)> letter##1; \
    static constexpr Private::HAL_PIN<Private::pin(num, 2)> letter##2; \
    static constexpr Private::HAL_PIN<Private::pin(num, 3)> letter##3; \
    static constexpr Private::HAL_PIN<Private::pin(num, 4)> letter##4; \
    static constexpr Private::HAL_PIN<Private::pin(num, 5)> letter##5; \
    static constexpr Private::HAL_PIN<Private::pin(num, 6)> letter##6; \
    static constexpr Private::HAL_PIN<Private::pin(num, 7)> letter##7; \

    AVERSIVE_DEFINE_PORT(A,0);
    AVERSIVE_DEFINE_PORT(B,1);
    AVERSIVE_DEFINE_PORT(C,2);
    AVERSIVE_DEFINE_PORT(D,3);
    AVERSIVE_DEFINE_PORT(E,4);
    AVERSIVE_DEFINE_PORT(F,5);
    AVERSIVE_DEFINE_PORT(G,6);
    AVERSIVE_DEFINE_PORT(H,7);
    AVERSIVE_DEFINE_PORT(I,8);
    AVERSIVE_DEFINE_PORT(J,9);
    AVERSIVE_DEFINE_PORT(K,10);
    AVERSIVE_DEFINE_PORT(L,11);

#undef AVERSIVE_DEFINE_PORT

    static constexpr Private::HAL_UART<0> UART0;
    static constexpr Private::HAL_UART<1> UART1;
    static constexpr Private::HAL_UART<2> UART2;
    static constexpr Private::HAL_UART<3> UART3;

  }

}

#endif//HAL_ATMEGAXX0_1_TRAITS_HPP
