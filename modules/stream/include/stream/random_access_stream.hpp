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
#ifndef RANDOM_ACCESS_STREAM
#define RANDOM_ACCESS_STREAM

#include "config.hpp"

namespace Aversive {

namespace Stream {

  //! \brief Abstract random access stream.
  class RandomAccessStream {
  protected:
    inline RandomAccessStream() {}

    //! \brief The current position of the stream's reader head.
    volatile u16 _cursor = 0;

  public:
    //! \brief Place the cursor at a given position.
    //! \param pos : the new cursor's position.
    inline void seek(u16 pos) {
      _cursor = pos;
    }

    //! \brief Move the cursor by a given offset.
    //! \param offset : the offset to move the cursor with.
    inline void move(s16 offset) {
      _cursor += offset;
    }

    //! \brief Return the current cursor's position.
    //! \return The cursor's position.
    inline u16 cursor(void) const {
      return _cursor;
    }
  };

}

}

#endif//RANDOM_ACCESS_STREAM
