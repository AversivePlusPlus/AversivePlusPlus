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
#ifndef STRING_STREAM_HPP
#define STRING_STREAM_HPP

#include "config.hpp"

#include <stream/io_stream.hpp>
#include <container/buffer.hpp>

#include <stream/formatted_stream.hpp>

namespace Aversive {

namespace Stream {

  //! \warning _SIZE must be a power of 2, it is verified with an assert.
  //! \param _SIZE : the number of elements the stream's buffer can handle at any given time.
  template<Container::buffer_t _SIZE>
  class StringStreamBase {
  protected:
    //! \brief The internal buffer representing the stream.
    Container::Buffer<_SIZE, char> _buffer;

  public:
    //! \brief Default constructor.
    inline StringStreamBase(void)
      : _buffer() {
    }

    //! \brief Return the buffer's size.
    //! \return The buffer's size.
    constexpr inline u16 bufferSize(void) const {
      return _SIZE;
    }

    //! \brief Return the amout of characters that can be written into the stream without blocking.
    //! \return The amout of characters writtable without blocking.
    constexpr inline u16 writable(void) const {
      return _buffer.freeSpace();
    }

    //! \brief Return the amount of characters currently pending into the buffer.
    //! \return The amout of characters within the buffer.
    constexpr inline u16 readable(void) const {
      return _buffer.usedSpace();
    }
  };

  template<Container::buffer_t _SIZE>
  class StringStream : public StringStreamBase<_SIZE>, public IOStream<StringStream<_SIZE>> {
  public:
    StringStream(void)
      : StringStreamBase<_SIZE>() {
    }

    //! \brief Read a char from the stream's buffer.
    //! \return The read character.
    //! \warning Blocking operation if the stream's buffer is empty.
    u8 getChar(void) {
      while(this->_buffer.isEmpty());
      u8 ret = this->_buffer.head();
      this->_buffer.dequeue();
      return ret;
    }

    u16 read(u8* data, u16 length) {
      u16 rem;
      for(rem = length ; rem > 0 && this->readable() > 0 ; rem-- , data++) {
          *data = this->_buffer.head();
          this->_buffer.dequeue();
        }
      return length - rem;
    }

    //! \brief Write a char in the stream's buffer.
    //! \param c : the character to write.
    //! \warning Blocking operation if the stream's buffer is full
    void putChar(u8 c) {
      while(!this->_buffer.enqueue(c));
    }

    u16 write(u8* data, u16 length) {
      u16 rem;
      for(rem = length ; rem > 0 && this->writable() > 0 ; rem-- , data++) {
          this->_buffer.enqueue(*data);
        }
      return length - rem;
    }

    constexpr inline u16 writable(void) const {
      return StringStreamBase<_SIZE>::writable();
    }

    constexpr inline u16 readable(void) const {
      return StringStreamBase<_SIZE>::readable();
    }
  };

  template<Container::buffer_t _SIZE>
  struct FormattedStringStream : StringStream<_SIZE>, FormattedStreamDecorator<FormattedStringStream<_SIZE>> {
    inline FormattedStringStream()
      : FormattedStreamDecorator<FormattedStringStream<_SIZE>>(*this) {}

    inline u8 getChar(void) {
      return StringStream<_SIZE>::getChar();
    }

    inline u16 read(u8* data, u16 length) {
      return StringStream<_SIZE>::read(data, length);
    }

    inline void putChar(u8 c) {
      StringStream<_SIZE>::putChar(c);
    }

    inline u16 write(u8* data, u16 length) {
      return StringStream<_SIZE>::write(data, length);
    }

    constexpr inline u16 writable(void) const {
      return StringStream<_SIZE>::writable();
    }

    constexpr inline u16 readable(void) const {
      return StringStream<_SIZE>::readable();
    }
  };

}

}

#endif//STRING_STREAM_HPP
