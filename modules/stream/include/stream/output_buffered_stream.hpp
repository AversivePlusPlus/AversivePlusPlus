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
#ifndef OUTPUT_BUFFERED_STREAM_HPP
#define OUTPUT_BUFFERED_STREAM_HPP

#include <stream/output_stream.hpp>
#include <container/buffer.hpp>

namespace Stream {

  //! \brief Internal buffered stream interface.
  template<class Derived, Container::buffer_t SIZE>
  class OutputBufferedStream : public OutputStream<OutputBufferedStream<Derived, SIZE>> {
  protected:

    //! \brief The input buffer.
    Container::Buffer<SIZE, u8> _output;

    //! \brief The function called to begin a write sequence (with interruptions)
    void writeBeginHandler(void) {
      static_cast<Derived*>(this)->writeBeginHandler();
    }

  protected:
    OutputBufferedStream(void)
      : _output() {
    }

  public:

    //! \brief Flush the output (ie: wait for the output buffer to be empty).
    inline void flushOutput(void) const {
      while(!_output.isEmpty());
    }

    //! \brief Return the buffers' size.
    //! \return The buffers' size.
    constexpr inline u16 outputBufferSize(void) const {
      return _output.SIZE;
    }

    //! \brief Return the amout of characters waiting to be sent into the output buffer.
    //! \return The amout of characters within the output buffer.
    inline u16 writable(void) const {
      return _output.freeSpace();
    }

    void putChar(u8 c) {
      while(_output.isFull()) {
          writeBeginHandler();
        }
      _output.enqueue(c);
      writeBeginHandler();
    }

    u16 write(u8* data, u16 length) {
      u16 rem;
      for(rem = length ; rem > 0 && writable() > 0 ; rem-- , data++) {
          _output.enqueue(*data);
          writeBeginHandler();
        }
      return length - rem;
    }
  };

}

#endif//OUTPUT_BUFFERED_STREAM_HPP
