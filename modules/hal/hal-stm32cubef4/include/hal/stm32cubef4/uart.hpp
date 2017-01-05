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
#ifndef HAL_STM32CUBEF4_UART_HPP
#define HAL_STM32CUBEF4_UART_HPP

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>

#include <hal/uart_interface.hpp>
#include <hal/stm32cubef4/gpio.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

using namespace Aversive::Base;

namespace HAL {

  namespace STM32CubeF4 {
    
    namespace Private {

      template<int ID>
      Func& get_uart_tx_irq_handler();

      template<int ID>
      Func& get_uart_rx_irq_handler();

      template<int ID>
      UART_HandleTypeDef& get_uart_cube_handle();

    }

    struct UART : UART_DriverInterface {
      static UART_HandleTypeDef _uart[5];
      typedef void (*Func)(void);
      static Func _uart_clk_init[5];
      struct Events {
        Func txc;
        Func rxc;
      };
      static Events _uart_events[5];

      using Parent = UART_DriverInterface;
      
      //! \brief The UART Parity Mode
      struct Parity : Parent::Parity {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(NONE);
        AVERSIVE_AVAILABLE_ELEMENT(EVEN);
        AVERSIVE_AVAILABLE_ELEMENT(ODD);
      };

      //! \brief The UART Stop Bit Length
      struct StopBit : Parent::StopBit {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(ONE_BIT);
        //AVERSIVE_AVAILABLE_ELEMENT(ONE_AND_HALF_BIT);
        AVERSIVE_AVAILABLE_ELEMENT(TWO_BIT);
      };

      //! \brief The UART Flow Control Mode
      struct FlowControl : Parent::FlowControl {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(NONE);
        //AVERSIVE_AVAILABLE_ELEMENT(CTS);
        //AVERSIVE_AVAILABLE_ELEMENT(RTS);
      };

      //! \brief The UART Endianess
      struct Endianess : Parent::Endianess {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        //AVERSIVE_AVAILABLE_ELEMENT(MSB);
        //AVERSIVE_AVAILABLE_ELEMENT(LSB);
      };

      //! \brief The UART Events
      struct Event : Parent::Event {
        AVERSIVE_AVAILABLE_ELEMENT(TX_COMPLETE);
        AVERSIVE_AVAILABLE_ELEMENT(RX_COMPLETE);
      };

      template<typename T, DummyType DUMMY = DUMMY_VALUE>
      struct IsDisabled {
        static constexpr bool VALUE = false;
      };

      template<DummyType DUMMY>
      struct IsDisabled<Parent::DisableType, DUMMY> {
        static constexpr bool VALUE = true;
      };

      template<typename T>
      static constexpr inline bool is_enabled(T) {
        return !IsDisabled<T>::VALUE;
      }

      template<typename T>
      static constexpr inline bool is_enabled() {
        return !IsDisabled<T>::VALUE;
      }

      template<int ID, typename UARTType>
      static void _pin_init(Private::PIN_Type<ID> pin, UARTType uart) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(Private::port(pin));
        Private::clk_enable(Private::port(pin));

        GPIO_InitTypeDef gpio_init;
        gpio_init.Pull = GPIO_NOPULL;
        gpio_init.Speed = GPIO_SPEED_HIGH;
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Alternate = Private::cube_gpio_uart_af(uart);
        gpio_init.Pin = Private::cube_gpio_offset(offset(pin));
        HAL_GPIO_Init(gpio, &gpio_init);
      }

      template<typename UARTType>
      static constexpr inline void _pin_init(UART::DisableType, UARTType) {
      }

      template<typename UARTType, typename TXPinType, typename RXPinType, typename Settings>
      static inline void init(UARTType uart, TXPinType tx, RXPinType rx, const Settings& settings) {
        UART_HandleTypeDef& uart_handle = Private::get_uart_cube_handle<uart>();

        _pin_init(tx, uart);
        _pin_init(rx, uart);

        uart_handle.Init.BaudRate = settings.baudrate;
        uart_handle.Init.WordLength = Private::cube_uart_word_length(settings.word_size);
        uart_handle.Init.StopBits  = Private::cube_uart_stop_bit(settings.stop_bit);
        uart_handle.Init.Parity = Private::cube_uart_parity(settings.parity);

        if(is_enabled(tx) && is_enabled(rx)) {
            uart_handle.Init.Mode = UART_MODE_TX_RX;
          }
        else if(is_enabled(tx)) {
            uart_handle.Init.Mode = UART_MODE_TX;
          }
        else if(is_enabled(rx)) {
            uart_handle.Init.Mode = UART_MODE_RX;
          }

        Private::clk_enable(uart);

        uart_handle.Instance = Private::cube_uart(uart);
        HAL_UART_Init(&uart_handle);
      }

      template<typename UARTType, typename Event, typename IRQ_Handler>
      static void setHandler(UARTType uart, Event evt, IRQ_Handler handler) {
        UART_HandleTypeDef& uart_handle = Private::get_uart_cube_handle<uart>();

        if(evt == Event::TX_COMPLETE) {
            Private::get_uart_tx_irq_handler<uart>() = handler;
            __HAL_UART_ENABLE_IT(&uart_handle, UART_IT_TC);
          }
        if(evt == Event::RX_COMPLETE) {
            Private::get_uart_rx_irq_handler<uart>() = handler;
            __HAL_UART_ENABLE_IT(&uart_handle, UART_IT_RXNE);
          }

        IRQn_Type irq = Private::cube_uart_irq(uart);
        HAL_NVIC_EnableIRQ(irq);
        HAL_NVIC_SetPriority(irq, 2,2);
      }

      template<typename UARTType>
      static void putChar(UARTType uart, u8 val) {
        UART_HandleTypeDef& uart_handle = Private::get_uart_cube_handle<uart>();
        HAL_UART_Transmit(&uart_handle, (uint8_t*)&val, 1, 10000);
      }

      template<typename UARTType>
      static u8 getChar(UARTType uart) {
        UART_HandleTypeDef& uart_handle = Private::get_uart_cube_handle<uart>();
        char c = 0;
        HAL_UART_Receive(&uart_handle, (uint8_t*)&c, 1, 10000);
        return c;
      }

      template<typename UARTType>
      static u32 write(UARTType uart, const u8* data, u32 length) {
        UART_HandleTypeDef& uart_handle = Private::get_uart_cube_handle<uart>();
        if(HAL_UART_Transmit(&uart_handle, (uint8_t*)data, length, 10000) != HAL_OK) {
            return 0;
          }
        return length;
      }

      template<typename UARTType>
      static u32 read(UARTType uart, u8* data, u32 length) {
        UART_HandleTypeDef& uart_handle = Private::get_uart_cube_handle<uart>();
        if(HAL_UART_Receive(&uart_handle, (uint8_t*)data, length, 10000) != HAL_OK) {
            return 0;
          }
        return length;
      }

      template<typename UARTType>
      static u32 getWritable(UARTType uart) AVERSIVE_UNAVAILABLE;

      template<typename UARTType>
      static u32 getReadable(UARTType uart) AVERSIVE_UNAVAILABLE;
    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_STM32CUBEF4_UART_HPP
