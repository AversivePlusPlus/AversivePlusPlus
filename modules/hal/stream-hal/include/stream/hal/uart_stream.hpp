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
#ifndef UART_STREAM_HPP
#define UART_STREAM_HPP

#include <stream/io_stream.hpp>
#include <stream/formatted_stream.hpp>

#include <hal/uart.hpp>

namespace Aversive {
namespace Stream {
  namespace HAL {

  struct DefaultUARTStreamSettings {
    static constexpr auto uart = 0;
    static constexpr auto tx = ::HAL::UART_DriverInterface::DISABLE;
    static constexpr auto rx = ::HAL::UART_DriverInterface::DISABLE;

    static constexpr auto baudrate     = 9600;
    static constexpr auto word_size    = 8;
    static constexpr auto stop_bit     = ::HAL::UART_DriverInterface::StopBit::ONE_BIT;
    static constexpr auto parity       = ::HAL::UART_DriverInterface::Parity::NONE;
    static constexpr auto endianess    = ::HAL::UART_DriverInterface::Endianess::UNDEFINED;
    static constexpr auto flow_control = ::HAL::UART_DriverInterface::FlowControl::NONE;
  };

  template<typename Settings>
  class InputUARTStream : public InputStream<InputUARTStream<Settings>> {
    using UART = ::HAL::UART;

  protected:
    inline InputUARTStream(int) {}

  public:
    InputUARTStream(void) {
      UART::Settings settings;
      settings.baudrate = Settings::baudrate;
      settings.word_size = Settings::word_size;
      settings.stop_bit = Settings::stop_bit;
      settings.parity = Settings::parity;
      settings.endianess = Settings::endianess;
      settings.flow_control = Settings::flow_control;
      UART::init(Settings::uart, UART::DISABLE, Settings::rx, settings);
    }

    //! \brief Read a char from the stream's buffer.
    //! \return The read character.
    //! \warning Blocking operation if the stream's buffer is empty.
    inline u8 getChar(void) {
      return UART::getChar(Settings::uart);
    }

    inline u16 read(u8* data, u16 length) {
      return UART::read(Settings::uart, data, length);
    }

    inline u16 readable(void) {
      return UART::getReadable(Settings::uart);
    }
  };

  template<typename Settings>
  class OutputUARTStream : public OutputStream<OutputUARTStream<Settings>> {
    using UART = ::HAL::UART;

  protected:
    inline OutputUARTStream(int) {}

  public:
    OutputUARTStream(void) {
      UART::Settings settings;
      settings.baudrate = Settings::baudrate;
      settings.word_size = Settings::word_size;
      settings.stop_bit = Settings::stop_bit;
      settings.parity = Settings::parity;
      settings.endianess = Settings::endianess;
      settings.flow_control = Settings::flow_control;
      UART::init(Settings::uart, Settings::tx, UART::DISABLE, settings);
    }

    //! \brief Write a char in the stream's buffer.
    //! \param c : the character to write.
    //! \warning Blocking operation if the stream's buffer is full
    inline void putChar(u8 c) {
      UART::putChar(Settings::uart, c);
    }

    inline u16 write(u8* data, u16 length) {
      return UART::write(Settings::uart, data, length);
    }

    inline u16 writable(void) {
      return UART::getWritable(Settings::uart);
    }
  };

  template<typename Settings>
  class UARTStream :
      public IOStream<UARTStream<Settings>>,
      public InputUARTStream<Settings>,
      public OutputUARTStream<Settings> {

    using UART = ::HAL::UART;
    using _I = InputUARTStream<Settings>;
    using _O = OutputUARTStream<Settings>;

  public:
    UARTStream(void)
      : _I(0), _O(0) {
      UART::Settings settings;
      settings.baudrate = Settings::baudrate;
      settings.word_size = Settings::word_size;
      settings.stop_bit = Settings::stop_bit;
      settings.parity = Settings::parity;
      settings.endianess = Settings::endianess;
      settings.flow_control = Settings::flow_control;
      UART::init(Settings::uart, Settings::tx, Settings::rx, settings);
    }

    inline u8 getChar(void) {
      return _I::getChar();
    }

    inline u16 read(u8* data, u16 length) {
      return _I::read(data, length);
    }

    inline u16 readable(void) {
      return _I::readable();
    }

    inline void putChar(u8 c) {
      _O::putChar(c);
    }

    inline u16 write(u8* data, u16 length) {
      return _O::write(data, length);
    }

    inline u16 writable(void) {
      return _O::writable();
    }
  };


  template<typename Stream>
  struct GenericFormattedUARTStream : FormattedStreamDecorator<Stream> {

    Stream _stream;

    GenericFormattedUARTStream()
      : FormattedStreamDecorator<Stream>(_stream) {}
  };

  template<typename Settings> using FormattedUARTStream = GenericFormattedUARTStream<UARTStream<Settings>>;
  template<typename Settings> using FormattedInputUARTStream = GenericFormattedUARTStream<InputUARTStream<Settings>>;
  template<typename Settings> using FormattedOutputUARTStream = GenericFormattedUARTStream<OutputUARTStream<Settings>>;

  }
}
}

#endif//UART_STREAM_HPP
