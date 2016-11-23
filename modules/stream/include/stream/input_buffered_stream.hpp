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
#ifndef INPUT_BUFFERED_STREAM_HPP
#define INPUT_BUFFERED_STREAM_HPP

#include <stream/input_stream.hpp>
#include <container/buffer.hpp>

namespace Stream {

  //! \brief Internal buffered stream interface.
  template<class Derived, Container::buffer_t SIZE>
  class InputBufferedStream : public InputStream<InputBufferedStream<Derived, SIZE>> {
  protected:

    //! \brief The input buffer.
    Container::Buffer<SIZE, u8> _input;

  protected:
    InputBufferedStream(void)
      : _input() {
    }

  public:
    //! \brief Discard every data in the input buffer.
    inline void flushInput(void) {
      _input.flush();
    }

    //! \brief Return the buffers' size.
    //! \return The buffers' size.
    constexpr inline u16 inputBufferSize(void) const {
      return _input.SIZE;
    }

    //! \brief Return the amount of characters currently pending into the input buffer.
    //! \return The amount of characters within the input buffer.
    inline u16 readable(void) const {
      return _input.usedSpace();
    }

    inline u8 getChar(void) {
      while(_input.isEmpty());
      u8 ret = _input.head();
      _input.dequeue();
      return ret;
    }

    u16 read(u8* data, u16 length) {
      u16 rem;
      for(rem = length ; rem > 0 && readable() > 0 ; rem-- , data++) {
          *data = _input.head();
          _input.dequeue();
        }
      return length - rem;
    }

  };

}

#endif//INPUT_BUFFERED_STREAM_HPP
