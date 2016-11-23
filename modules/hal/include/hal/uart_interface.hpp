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
#ifndef HAL_UART_INTERFACE_HPP
#define HAL_UART_INTERFACE_HPP

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {

  //! \brief UART Driver Interface
  //! \param T : The type of a standard UART Data Register
  struct UART_DriverInterface {
      
    //! \brief The UART Baudrate
    struct Baudrate {
      using Type = u32;
    };

    //! \brief The UART Parity Mode
    struct Parity {
      enum class Type : u8 { UNDEFINED = 0, NONE, EVEN, ODD };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(NONE);
      AVERSIVE_UNAVAILABLE_ELEMENT(EVEN);
      AVERSIVE_UNAVAILABLE_ELEMENT(ODD);
    };

    //! \brief The UART Stop Bit Length
    struct StopBit {
      enum class Type : u8 { UNDEFINED = 0, ONE_BIT, ONE_AND_HALF_BIT, TWO_BIT };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(ONE_BIT);
      AVERSIVE_UNAVAILABLE_ELEMENT(ONE_AND_HALF_BIT);
      AVERSIVE_UNAVAILABLE_ELEMENT(TWO_BIT);
    };

    //! \brief The UART Word Size
    struct WordSize {
      using Type = u8;
    };

    //! \brief The UART FIFO Size
    struct FifoSize {
      using Type = u8;
    };

    //! \brief The UART Flow Control Mode
    struct FlowControl {
      enum class Type : u8 { UNDEFINED = 0, NONE, CTS, RTS };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(NONE);
      AVERSIVE_UNAVAILABLE_ELEMENT(CTS);
      AVERSIVE_UNAVAILABLE_ELEMENT(RTS);
    };

    //! \brief The UART Endianess
    struct Endianess {
      enum class Type : u8 { UNDEFINED = 0, MSB, LSB };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(MSB);
      AVERSIVE_UNAVAILABLE_ELEMENT(LSB);
    };

    //! \brief The UART Events
    struct Event {
      enum class Type : u8 { TX_COMPLETE, RX_COMPLETE };
      AVERSIVE_UNAVAILABLE_ELEMENT(TX_COMPLETE);
      AVERSIVE_UNAVAILABLE_ELEMENT(RX_COMPLETE);
    };

    struct DisableType {};
    constexpr static auto DISABLE = DisableType();

    //! \brief UART Settings
    template<
      typename BaudrateType,
      typename ParityType,
      typename StopBitType,
      typename WordSizeType,
      typename TXFifoSizeType,
      typename RXFifoSizeType,
      typename FlowControlType,
      typename EndianessType
      >
    struct GenericSettings {
      BaudrateType baudrate;
      ParityType parity;
      StopBitType stop_bit;
      WordSizeType word_size;
      TXFifoSizeType tx_fifo_size;
      RXFifoSizeType rx_fifo_size;
      FlowControlType flow_control;
      EndianessType endianess;
    };

    using Settings = GenericSettings<
      typename Baudrate::Type,
      typename Parity::Type,
      typename StopBit::Type,
      typename WordSize::Type,
      typename FifoSize::Type,
      typename FifoSize::Type,
      typename FlowControl::Type,
      typename Endianess::Type
    >;

    //! \brief Configure the UART
    //! \param uart : The UART module
    //! \param tx : The TX Pin, you can disable TX by passing UART::DISABLE
    //! \param rx : The RX Pin, you can disable RX by passing UART::DISABLE
    //! \param settings : UART settings
    template<typename UARTType, typename TXPinType, typename RXPinType, typename Settings>
    static void init(UARTType uart, TXPinType tx, RXPinType rx, const Settings& settings) AVERSIVE_UNAVAILABLE;

    //! \brief Set interrupt handler for an event
    //! \param uart : The UART module
    //! \param evt : The event to handle
    //! \param handler : The function to call when the event occurs
    template<typename UARTType, typename Event, typename IRQ_Handler>
    static void setHandler(UARTType uart, Event evt, IRQ_Handler handler) AVERSIVE_UNAVAILABLE;

    //! \brief Put a character in the write buffer
    //! \warning The function will block until the character can be put in the buffer
    template<typename UARTType>
    static void putChar(UARTType uart, u8 val) AVERSIVE_UNAVAILABLE;
    
    //! \brief Get a character from the read buffer
    //! \warning The function will block until a character is available in the buffer
    template<typename UARTType>
    static u8 getChar(UARTType uart) AVERSIVE_UNAVAILABLE; // Blocking

    //! \brief Write data in the write buffer
    //! \warning The function will block until the data has been put completely in the buffer
    template<typename UARTType>
    static u32 write(UARTType uart, u8* data, u32 length) AVERSIVE_UNAVAILABLE; // Blocking

    //! \brief Read data from the read buffer
    //! \warning The function will block until the data has been read completely from the buffer
    template<typename UARTType>
    static u32 read(UARTType uart, u8* data, u32 length)  AVERSIVE_UNAVAILABLE; // Blocking

    //! \brief Get the number of character writable in the write buffer
    template<typename UARTType>
    static u32 getWritable(UARTType uart) AVERSIVE_UNAVAILABLE;

    //! \brief Get the number of character available in the read buffer
    template<typename UARTType>
    static u32 getReadable(UARTType uart) AVERSIVE_UNAVAILABLE;
  };

}

#include <hal/macros_undef.hpp>

#endif//HAL_UART_INTERFACE_HPP
