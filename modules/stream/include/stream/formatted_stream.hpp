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
#ifndef FORMATTED_STREAM_HPP
#define FORMATTED_STREAM_HPP

#include "config.hpp"

#include <stream/input_stream.hpp>
#include <stream/output_stream.hpp>

#include <string.h>

namespace Aversive {

namespace Stream {

namespace Private {
template<typename T> struct IsSigned {};

template<> struct IsSigned<s8>  { static constexpr bool VALUE = true; };
template<> struct IsSigned<s16> { static constexpr bool VALUE = true; };
template<> struct IsSigned<s32> { static constexpr bool VALUE = true; };
template<> struct IsSigned<s64> { static constexpr bool VALUE = true; };

template<> struct IsSigned<u8>  { static constexpr bool VALUE = true; };
template<> struct IsSigned<u16> { static constexpr bool VALUE = true; };
template<> struct IsSigned<u32> { static constexpr bool VALUE = true; };
template<> struct IsSigned<u64> { static constexpr bool VALUE = true; };

template<typename T>
static inline constexpr bool SIGNED(T&) {
  return Private::IsSigned<T>::VALUE;
}

template<typename T>
inline char* writeFormattedInteger(T val, char* str, unsigned int MAX_BUFF) {
  bool _neg = false;

  // Initialize string
  char* ptr = str + MAX_BUFF;

  // Parsing sign and digits
  if(SIGNED(val) && val < 0) {
    val = -val;
    _neg = true;
  }

  while(0 < val && str < ptr) {
    *(--ptr) = '0' + (val % 10);
    val /= 10;
  }

  if(SIGNED(val) && _neg) {
    *(--ptr) = '-';
  }

  // If no digits found
  if(ptr == str + MAX_BUFF) {
    *(--ptr) = '0';
  }

  // write
  return ptr;
}

enum ReadIntegerState {
  BEGIN,
  POSITIVE,
  NEGATIVE,
  END,
};

template<typename T, class Stream>
void readFormattedInteger(T& val, Stream& stream) {
  val = 0;
  ReadIntegerState state = BEGIN;

  while(state != END && stream.readable()) {
    char c = stream.get();

    if(c == '-') {
      if(SIGNED(val) && state == BEGIN) {
        state = NEGATIVE;
      }
      else {
        state = END;
      }
    }
    else if('0' <= c && c <= '9') {
      if(state == BEGIN) state = POSITIVE;
      val = val * 10 + ((T) (c - '0'));
    }
    else {
      if(state == NEGATIVE) {
        val = -val;
      }
      state = END;
    }
  }
}

}

//! \brief Abstract two-way stream with formatted read and write.
template<class Stream>
class FormattedStreamDecorator : public Stream {};

struct FormattedEndLine {};
constexpr FormattedEndLine endl = {};

template<class Stream>
static inline constexpr FormattedStreamDecorator<Stream>& formatted(Stream& stream) {
  static_assert(sizeof(FormattedStreamDecorator<Stream>) == sizeof(Stream), "FATAL ERROR");
  return (FormattedStreamDecorator<Stream>&)stream;
}

//! \brief Write an integer into the stream.
//! \param val : the integer to write.
//! \return A reference to the stream.
template<class Stream, typename T>
inline FormattedStreamDecorator<Stream>& operator<<(FormattedStreamDecorator<Stream>& stream, const T& val) {
  constexpr unsigned int MAX_BUFF = 32;
  char str[MAX_BUFF] = {0};
  char* ptr = Private::writeFormattedInteger(val, str, MAX_BUFF);
  stream.write(ptr, MAX_BUFF - (ptr-str));
  return stream;
}

//! \brief Write a string into the stream.
//! \param str : the string to write.
//! \return A reference to the stream.
template<class Stream>
inline FormattedStreamDecorator<Stream>& operator<<(FormattedStreamDecorator<Stream>& stream, const char* str) {
  stream.write(str, strlen(str));
  return stream;
}

//! \brief Write a end of line character into the stream.
//! \return A reference to the stream.
template<class Stream>
inline FormattedStreamDecorator<Stream>& operator<<(FormattedStreamDecorator<Stream>& stream, const FormattedEndLine) {
  stream.put('\n');
  return stream;
}

//! \brief Read an integer from the stream.
//! \param val : a reference to the integer to overwrite.
//! \return A reference to the stream.
template<class Stream, typename T>
inline FormattedStreamDecorator<Stream>& operator>>(FormattedStreamDecorator<Stream>& stream, T& val) {
  Private::readFormattedInteger(val, stream);
  return stream;
}

}

}

#endif//FORMATTED_STREAM_HPP
