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
#ifndef HAL_STM32CUBEF4_TRAITS_HPP
#define HAL_STM32CUBEF4_TRAITS_HPP

#include <base/integer.hpp>
#include <base/compil.hpp>

#include <hal/gpio_interface.hpp>
#include <hal/encoder_interface.hpp>
#include <hal/uart_interface.hpp>

#include <stm32f4xx_hal.h>

#include <hal/stm32cubef4/traits_stm32f407xx.hpp>
#include <hal/stm32cubef4/traits_generated.hpp>


namespace HAL {
  namespace STM32CubeF4 {
    namespace Private {
      typedef void(*Func)(void);
    }
  }
}

namespace HAL {
  namespace STM32CubeF4 {
    namespace Private {
      static constexpr inline uint32_t cube_gpio_timer_af(int timer) {
        return
#ifdef GPIO_AF1_TIM1
          (timer == 1) ? GPIO_AF1_TIM1 :
#endif
#ifdef GPIO_AF1_TIM2
          (timer == 2) ? GPIO_AF1_TIM2 :
#endif
#ifdef GPIO_AF2_TIM3
          (timer == 3) ? GPIO_AF2_TIM3 :
#endif
#ifdef GPIO_AF2_TIM4
          (timer == 4) ? GPIO_AF2_TIM4 :
#endif
#ifdef GPIO_AF2_TIM5
          (timer == 5) ? GPIO_AF2_TIM5 :
#endif
#ifdef GPIO_AF3_TIM8
          (timer == 8) ? GPIO_AF3_TIM8 :
#endif
#ifdef GPIO_AF3_TIM9
          (timer == 9) ? GPIO_AF3_TIM9 :
#endif
#ifdef GPIO_AF3_TIM10
          (timer == 10) ? GPIO_AF3_TIM10 :
#endif
#ifdef GPIO_AF3_TIM11
          (timer == 11) ? GPIO_AF3_TIM11 :
#endif
#ifdef GPIO_AF9_TIM12
          (timer == 12) ? GPIO_AF9_TIM12 :
#endif
#ifdef GPIO_AF9_TIM13
          (timer == 13) ? GPIO_AF9_TIM13 :
#endif
#ifdef GPIO_AF9_TIM14
          (timer == 14) ? GPIO_AF9_TIM14 :
#endif
          -1;
      }
    }
  }
}

namespace HAL {

  namespace STM32CubeF4 {

    ////////////////////////////////////////////////////////////////
    // GPIO

    //// Define

    namespace Private {

      enum class GPIO_HAL_Class { PIN, PORT };

      template<GPIO_HAL_Class CLASS, int ID>
      struct GPIO_HAL_Type {
        using ValueType = u32;
        constexpr inline operator u32() { return ID; }
      };

      template<int ID> using PORT_Type = GPIO_HAL_Type<GPIO_HAL_Class::PORT, ID>;
      template<int ID> using PIN_Type  = GPIO_HAL_Type<GPIO_HAL_Class::PIN, ID>;

      template<int ID>
      static inline constexpr PORT_Type<ID/16> port(const PIN_Type<ID>&) {
        return PORT_Type<ID/16>();
      }

      template<int ID>
      static inline constexpr int offset(const PIN_Type<ID>&) {
        return ID % 16;
      }

      template<int PORT_ID, int OFFSET>
      static inline constexpr PIN_Type<PORT_ID*16+OFFSET> pin(const PORT_Type<PORT_ID>&, const Compil<int, OFFSET>) {
        return PIN_Type<PORT_ID*16+OFFSET>();
      }

    }

#define AVERSIVE_DEFINE_PIN(num, letter, ...) \
  static constexpr auto letter##num  = pin(letter, num##_c);

#define AVERSIVE_DEFINE_PORT(letter,num, ...)          \
  AVERSIVE_HAL_STM32CUBEF4_GPIO##letter##_EXISTS(      \
  static constexpr Private::PORT_Type<num> letter; \
  AVERSIVE_APPLY_PINS(AVERSIVE_DEFINE_PIN, letter)     \
  ,)

    AVERSIVE_APPLY_PORTS(AVERSIVE_DEFINE_PORT)

#undef  AVERSIVE_DEFINE_PORT
#undef  AVERSIVE_DEFINE_PIN

    //// CLK_ENABLE

    namespace Private {

      template<int PORT_ID> inline void clk_enable(const PORT_Type<PORT_ID>& port) {
        static_assert(port && !port, "Error : invalid PORT");
      }

#define AVERSIVE_DEFINE_CLK_ENABLE(letter, ...) \
  AVERSIVE_HAL_STM32CUBEF4_GPIO##letter##_EXISTS(   \
  inline void clk_enable(const decltype(letter)&) { __GPIO##letter##_CLK_ENABLE(); } \
  ,)

      AVERSIVE_APPLY_PORTS(AVERSIVE_DEFINE_CLK_ENABLE)

#undef  AVERSIVE_DEFINE_CLK_ENABLE
    }

    //// Settings

    namespace Private {

      static constexpr inline uint32_t cube_gpio_pull(GPIO_DriverInterface::Pull::Type pull) {
        return (pull == GPIO_DriverInterface::Pull::UNDEFINED) ? GPIO_NOPULL:
               (pull == GPIO_DriverInterface::Pull::UP)        ? GPIO_PULLUP:
               (pull == GPIO_DriverInterface::Pull::DOWN)      ? GPIO_PULLDOWN:
                                                                 GPIO_NOPULL;
      }

      static constexpr inline uint32_t cube_gpio_mode(
          GPIO_DriverInterface::Mode::Type mode,
          GPIO_DriverInterface::OutputMode::Type output_mode) {
        return
            (mode == GPIO_DriverInterface::Mode::OUTPUT && output_mode == GPIO_DriverInterface::OutputMode::PUSH_PULL) ?
              GPIO_MODE_OUTPUT_PP :
            (mode == GPIO_DriverInterface::Mode::OUTPUT && output_mode == GPIO_DriverInterface::OutputMode::UNDEFINED) ?
              GPIO_MODE_OUTPUT_PP :
            (mode == GPIO_DriverInterface::Mode::OUTPUT && output_mode == GPIO_DriverInterface::OutputMode::OPEN_DRAIN) ?
              GPIO_MODE_OUTPUT_OD :
            (mode == GPIO_DriverInterface::Mode::INPUT) ?
              GPIO_MODE_INPUT :
            0;
      }
    }

    //// GPIO PIN PORT

    namespace Private {

#define AVERSIVE_TEST_PIN(num, ...) \
  (offset == num) ? GPIO_PIN_##num :

      static constexpr inline uint32_t cube_gpio_offset(int offset) {
        return
            AVERSIVE_APPLY_PINS(AVERSIVE_TEST_PIN)
            0;
      }

#undef AVERSIVE_TEST_PIN

#define AVERSIVE_TEST_PORT(letter, num, ...) \
  AVERSIVE_HAL_STM32CUBEF4_GPIO##letter##_EXISTS((port == num) ? GPIO##letter, 0?0) :

      static constexpr inline GPIO_TypeDef* cube_gpio_port(int port) {
        return
            AVERSIVE_APPLY_PORTS(AVERSIVE_TEST_PORT)
            0;
      }

#undef AVERSIVE_TEST_PORT

    }

    ////////////////////////////////////////////////////////////////
    //TIMER

    //// Define

    namespace Private {

      enum class TIMER_HAL_Class { TIMER, PWM };

      template<TIMER_HAL_Class CLASS, int ID>
      struct TIMER_HAL_Type {
        using CounterType = u32;
        constexpr inline operator u32() { return ID; }
      };

      template<int ID> using TIMER_Type = TIMER_HAL_Type<TIMER_HAL_Class::TIMER, ID>;
      template<int ID> using PWM_Type  = TIMER_HAL_Type<TIMER_HAL_Class::PWM, ID>;

      template<int ID>
      static constexpr inline TIMER_Type<ID/6> timer(const PWM_Type<ID>&) {
        return TIMER_Type<ID/6>();
      }

      template<int ID>
      static constexpr inline int channel(const PWM_Type<ID>&) {
        return ID%6;
      }

      template<int ID, int CH>
      static constexpr inline PWM_Type<ID*6+CH> pwm(const TIMER_Type<ID>&, const Compil<int, CH>&) {
        return PWM_Type<ID*6+CH>();
      }

    }

#define AVERSIVE_DEFINE_PWM(ch, timer, ...) \
  static constexpr auto TIMER##timer##_CH##ch  = pwm(TIMER##timer, ch##_c);

#define AVERSIVE_DEFINE_TIMER(timer, ...)          \
  AVERSIVE_HAL_STM32CUBEF4_TIMER##timer##_EXISTS(      \
  static constexpr Private::TIMER_Type<timer> TIMER##timer; \
  AVERSIVE_APPLY_CHANNELS(AVERSIVE_DEFINE_PWM, timer)     \
  ,)

    AVERSIVE_APPLY_TIMERS(AVERSIVE_DEFINE_TIMER)

#undef  AVERSIVE_DEFINE_TIMER
#undef  AVERSIVE_DEFINE_PWM

    //// CLK_ENABLE

    namespace Private {

      template<int ID> inline void clk_enable(const TIMER_Type<ID>& timer) {
        static_assert(timer && !timer, "Error : invalid TIMER");
      }

#define AVERSIVE_DEFINE_CLK_ENABLE(id, ...) \
  AVERSIVE_HAL_STM32CUBEF4_TIMER##id##_EXISTS(   \
  inline void clk_enable(decltype(TIMER##id)&) { __TIM##id##_CLK_ENABLE(); } \
  ,)

      AVERSIVE_APPLY_TIMERS(AVERSIVE_DEFINE_CLK_ENABLE)

#undef  AVERSIVE_DEFINE_CLK_ENABLE

    }

    //// TIMER CHANNEL

    namespace Private {

#define AVERSIVE_TEST_CHANNEL(ch, timer ...) \
  AVERSIVE_HAL_STM32CUBEF4_TIMER##timer##_CH##ch##_EXISTS((channel == ch) ? TIM_CHANNEL_##ch, 0?0) :

      static constexpr inline uint32_t cube_timer_channel(int channel) {
        return
            AVERSIVE_APPLY_CHANNELS(AVERSIVE_TEST_CHANNEL, 1)
            0;
      }

#undef AVERSIVE_TEST_CHANNEL

#define AVERSIVE_TEST_TIMER(id, ...) \
  AVERSIVE_HAL_STM32CUBEF4_TIMER##id##_EXISTS((timer == id) ? TIM##id, 0?0) :

      static constexpr inline TIM_TypeDef* cube_timer(int timer) {
        return
            AVERSIVE_APPLY_TIMERS(AVERSIVE_TEST_TIMER)
            0;
      }

#undef AVERSIVE_TEST_TIMER

    }

    //// Encoder

    namespace Private {

      static constexpr inline uint32_t cube_encoder_mode(ENCODER_DriverInterface::Mode::Type mode) {
        return
          (mode == ENCODER_DriverInterface::Mode::BOTH_COUNT) ? TIM_ENCODERMODE_TI12 :
          (mode == ENCODER_DriverInterface::Mode::CHANNEL1_COUNT) ? TIM_ENCODERMODE_TI1 :
          (mode == ENCODER_DriverInterface::Mode::CHANNEL2_COUNT) ? TIM_ENCODERMODE_TI2 :
          TIM_ENCODERMODE_TI12;
      }

      static inline constexpr uint32_t cube_encoder_polarity(ENCODER_DriverInterface::Polarity::Type p) {
        return (p == ENCODER_DriverInterface::Polarity::BOTH)   ?TIM_INPUTCHANNELPOLARITY_BOTHEDGE:
               (p == ENCODER_DriverInterface::Polarity::RISING) ?TIM_INPUTCHANNELPOLARITY_RISING:
               (p == ENCODER_DriverInterface::Polarity::FALLING)?TIM_INPUTCHANNELPOLARITY_FALLING:
               TIM_INPUTCHANNELPOLARITY_RISING;
      }

    }

    ////////////////////////////////////////////////////////////////
    // UART


    //// Define

    namespace Private {

      template<int ID>
      struct UART_HAL_Type {
        constexpr inline operator u32() { return ID; }
      };

      template<int ID> using UART_Type = UART_HAL_Type<ID>;
    }

#define AVERSIVE_DEFINE_UART(type, id, ...)          \
  AVERSIVE_HAL_STM32CUBEF4_UART##id##_EXISTS(        \
  static constexpr Private::UART_Type<id> SERIAL_##type##id;      \
  ,)

    AVERSIVE_APPLY_UARTS(AVERSIVE_DEFINE_UART)

#undef  AVERSIVE_DEFINE_UART

    namespace Private {

      static constexpr inline uint32_t cube_gpio_uart_af(int uart) {
        return
      #ifdef GPIO_AF7_USART1
          (uart == 1) ? GPIO_AF7_USART1 :
      #endif
      #ifdef GPIO_AF7_USART2
          (uart == 2) ? GPIO_AF7_USART2 :
      #endif
      #ifdef GPIO_AF7_USART3
          (uart == 3) ? GPIO_AF7_USART3 :
      #endif
      #ifdef GPIO_AF8_UART4
          (uart == 4) ? GPIO_AF8_UART4 :
      #endif
      #ifdef GPIO_AF8_UART5
          (uart == 5) ? GPIO_AF8_UART5 :
      #endif
      #ifdef GPIO_AF8_USART6
          (uart == 6) ? GPIO_AF8_USART6 :
      #endif
      #ifdef GPIO_AF8_UART7
          (uart == 7) ? GPIO_AF8_UART7 :
      #endif
      #ifdef GPIO_AF8_UART8
          (uart == 8) ? GPIO_AF8_UART8 :
      #endif
          -1;
      }

#define AVERSIVE_TEST_UART(type, id, ...) \
  AVERSIVE_HAL_STM32CUBEF4_UART##id##_EXISTS((uart == id) ? type##id, 0?0) :

      static constexpr inline USART_TypeDef* cube_uart(int uart) {
        return
            AVERSIVE_APPLY_UARTS(AVERSIVE_TEST_UART)
            0;
      }

#undef AVERSIVE_TEST_UART


      static constexpr inline uint32_t cube_uart_parity(UART_DriverInterface::Parity::Type p) {
        return
          (p == UART_DriverInterface::Parity::Type::EVEN) ? UART_PARITY_EVEN :
          (p == UART_DriverInterface::Parity::Type::ODD)  ? UART_PARITY_ODD :
          (p == UART_DriverInterface::Parity::Type::NONE) ? UART_PARITY_NONE:
                                                            UART_PARITY_NONE;
      }

      static constexpr inline uint32_t cube_uart_word_length(UART_DriverInterface::WordSize::Type l) {
        return
            (l == 8) ? UART_WORDLENGTH_8B :
            (l == 9) ? UART_WORDLENGTH_9B :
                       0;
      }

      static constexpr inline uint32_t cube_uart_stop_bit(UART_DriverInterface::StopBit::Type sb) {
        return
            (sb == UART_DriverInterface::StopBit::TWO_BIT) ? UART_STOPBITS_2 :
            (sb == UART_DriverInterface::StopBit::ONE_BIT) ? UART_STOPBITS_1 :
                                                             UART_STOPBITS_1;
      }

#define AVERSIVE_TEST_UART(type, id, ...) \
  AVERSIVE_HAL_STM32CUBEF4_UART##id##_EXISTS((uart == id) ? type##id##_IRQn, 0?UsageFault_IRQn) :

      static constexpr inline IRQn_Type cube_uart_irq(int uart) {
        return
            AVERSIVE_APPLY_UARTS(AVERSIVE_TEST_UART)
            UsageFault_IRQn;
      }

#undef AVERSIVE_TEST_UART


      template<int ID> inline void clk_enable(const UART_Type<ID>& uart) {
        static_assert(uart && !uart, "Error : invalid UART");
      }

#define AVERSIVE_DEFINE_CLK_ENABLE(type, id, ...) \
  AVERSIVE_HAL_STM32CUBEF4_UART##id##_EXISTS(   \
  inline void clk_enable(decltype(SERIAL_##type##id)&) { __##type##id##_CLK_ENABLE(); } \
  ,)

      AVERSIVE_APPLY_UARTS(AVERSIVE_DEFINE_CLK_ENABLE)

#undef  AVERSIVE_DEFINE_CLK_ENABLE

    }


  }

}

#endif//HAL_STM32CUBEF4_TRAITS_HPP
