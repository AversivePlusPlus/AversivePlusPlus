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
#ifndef HAL_ATMEGAXX0_1_UART_HPP
#define HAL_ATMEGAXX0_1_UART_HPP

#include <hal/uart_interface.hpp>
#include <hal/atmegaxx0_1/traits.hpp>
#include <hdl/avr/m2560.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

using namespace Aversive::Base;

namespace HAL {

  namespace ATMegaxx0_1 {

    //! \brief UART Driver Interface
    struct UART : public UART_DriverInterface {
      using Parent = UART_DriverInterface;

    public:

      template<int UART>
      struct UART_IRQ_Handlers {
        static void (*txc)(void);
        static void (*rxc)(void);
      };

    public:
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
        AVERSIVE_UNAVAILABLE_ELEMENT(ONE_AND_HALF_BIT);
        AVERSIVE_UNAVAILABLE_ELEMENT(TWO_BIT);
      };

      //! \brief The UART Flow Control Mode
      struct FlowControl : Parent::FlowControl {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(NONE);
        AVERSIVE_UNAVAILABLE_ELEMENT(CTS);
        AVERSIVE_UNAVAILABLE_ELEMENT(RTS);
      };

      //! \brief The UART Endianess
      struct Endianess : Parent::Endianess {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_UNAVAILABLE_ELEMENT(MSB);
        AVERSIVE_UNAVAILABLE_ELEMENT(LSB);
      };

      //! \brief The UART Events
      struct Event : Parent::Event {
        AVERSIVE_AVAILABLE_ELEMENT(TX_COMPLETE);
        AVERSIVE_AVAILABLE_ELEMENT(RX_COMPLETE);
      };

      //! \brief Configure the UART
      //! \param uart : The UART module
      //! \param tx : The TX Pin, you can disable TX by passing UART::DISABLE
      //! \param rx : The RX Pin, you can disable RX by passing UART::DISABLE
      //! \param settings : UART settings
      template<typename UARTType, typename TXPinType, typename RXPinType, typename Settings>
      static void init(UARTType uart, TXPinType, RXPinType, const Settings& settings) {
        ::HDL::UART<uart>::BRR = 16000000l/16/settings.baudrate-1;
        ::HDL::UART<uart>::Fields::RXEN = true;
        ::HDL::UART<uart>::Fields::TXEN = true;
        ::HDL::UART<uart>::Fields::SBS = false; // Stop bit = 1

        {
          u8 val = 0;

          if(settings.word_size == 5)
            val = 0b00;
          else if(settings.word_size == 6)
            val = 0b01;
          else if(settings.word_size == 7)
            val = 0b10;
          else if(settings.word_size == 8)
            val = 0b11;

          ::HDL::UART<uart>::Fields::CSZ_0_1 = val; // Word size = 8
        }

        ::HDL::UART<uart>::Fields::CSZ_2 = 0b0;    // Word size != 9

        {
          u8 val = 0;

          if(settings.parity == Parity::NONE)
            val = 0b00;
          else if(settings.parity == Parity::EVEN)
            val = 0b10;
          else if(settings.parity == Parity::ODD)
            val = 0b11;

          ::HDL::UART<uart>::Fields::PM = val;
        }
      }

      //! \brief Set interrupt handler for an event1000000
      //! \param uart : The UART module
      //! \param evt : The event to handle
      //! \param handler : The function to call when the even1000000t occurs
      template<typename UARTType, typename Event, typename IRQ_Handler>
      static void setHandler(UARTType uart, Event evt, IRQ_Handler handler) {
        if(evt == Event::TX_COMPLETE) {
            UART_IRQ_Handlers<uart>::txc = handler;
            ::HDL::UART<uart>::Fields::TXCIE = true;
          }
        else if(evt == Event::RX_COMPLETE) {
            UART_IRQ_Handlers<uart>::rxc = handler;
            ::HDL::UART<uart>::Fields::RXCIE = true;
          }
      }

      //! \brief Put a character in the write buffer
      //! \warning The function will block until the character can be put in the buffer
      template<typename UARTType>
      static void putChar(UARTType uart, u8 val) {
        while(!::HDL::UART<uart>::Fields::DRE);
        ::HDL::UART<uart>::DR = val;
      }

      //! \brief Get a character from the read buffer
      //! \warning The function will block until a character is available in the buffer
      template<typename UARTType>
      static u8 getChar(UARTType uart) {
        while(!::HDL::UART<uart>::Fields::RXC);
        return VAL(::HDL::UART<uart>::DR);
      }

      //! \brief Write data in the write buffer
      //! \warning The function will block until the data has been put completely in the buffer
      template<typename UARTType>
      static u32 write(UARTType uart, u8* data, u32 length) {
        u16 ret = length;
            while(length > 0) {
                putChar(uart, *data);
                data++;
                length--;
              }
            return ret;
      }

      //! \brief Read data from the read buffer
      //! \warning The function will block until the data has been read completely from the buffer
      template<typename UARTType>
      static u32 read(UARTType uart, u8* data, u32 length) {
        u16 ret = length;
            while(length > 0) {
                *data = getChar(uart);
                data++;
                length--;
              }
            return ret;
      }

      //! \brief Get the number of character writable in the write buffer
      template<typename UARTType>
      static u32 getWritable(UARTType uart) {
        if(!::HDL::UART<uart>::Fields::DRE && !::HDL::UART<uart>::Fields::RXC)
          return 1;
        return 0;
      }

      //! \brief Get the number of character available in the read buffer
      template<typename UARTType>
      static u32 getReadable(UARTType uart) {
        if(::HDL::UART<uart>::Fields::DRE && ::HDL::UART<uart>::Fields::RXC)
          return 1;
        return 0;
      }

    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_ATMEGAXX0_1_UART_HPP
