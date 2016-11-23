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

#include <stream/io_stream.hpp>

namespace Stream {

  template<class Derived>
  class FormattedStreamDecoratorBase {
  public:
    //! \brief Represents the different ways a stream can read string.
    //! \details Word separators are space, \\t and line separators.
    //! \details Line separators are \\n, \\r and \\0.
    //! \details Default is word.
    //! \note If the stream is in binary mode, whatever the string separator might be, a string reading will completely fulfil the user's buffer.
    enum SeparatorMode {
      WORD, //!< Read string word by word.
      LINE  //!< Read string line by line.
    };

  private:
    //! \brief The current way the stream read string.
    SeparatorMode _sep = WORD;

  protected:
    inline FormattedStreamDecoratorBase(void) {}

    inline u8 getChar(void) {
      return static_cast<Derived*>(this)->getChar();
    }

    inline u8 nextChar(void) {
      return static_cast<Derived*>(this)->nextChar();
    }

    inline void putChar(u8 c) {
      static_cast<Derived*>(this)->putChar(c);
    }

  public:
    //! \brief Return the string separator the stream currently uses.
    //! \return The current stream's string separator.
    inline SeparatorMode separatorMode(void) const {
      return _sep;
    }

    //! \brief Change the way the stream read strings.
    //! \param s : the new string separtor.
    inline void setSeparatorMode(SeparatorMode s) {
      _sep = s;
    }

  protected:
    void clearBlank() {
      char c = nextChar();
      while(c == ' ' || c == '\0' || c == '\n' || c == '\r' || c == '\t') {
          getChar();
          c = nextChar();
        }
    }

    //! \fixme Last character is overwritten by \0 when the user's buffer is fulfilled.
    void readUntilSeparator(char* str) {
      clearBlank();
      bool keep = true;
      while(keep) {
          char c = getChar();
          *str = c;
          if(_sep == WORD && (c == ' ' || c == '\t')) {
              keep = false;
            }
          else if(c == '\r' || c == '\n' || c == '\0') {
              *str = '\n';
              keep = false;
            }
          str++;
        }
      *(str-1) = '\0';
    }

    template<bool SIGNED = true, typename T>
    void readFormattedInteger(T& val) {
      clearBlank();
      val = 0;

      char c = 0;
      bool neg = false;
      c = nextChar();

      if(SIGNED && c == '-') {
          neg = true;
          getChar();
          c = nextChar();
        }

      while(c >= '0' && c <= '9') {
          getChar();
          val = val * 10 + ((T) (c - '0'));
          c = nextChar();
        }
      getChar();

      if(neg) {
          val = -val;
        }
    }

    //! \fixme Last character is overwritten by \0 when the user's buffer is fulfilled.
    void writeUntilEnd(const char* str) {
      while(*str != 0) {
          putChar(*str++);
        }
    }

    static constexpr u32 MAX_BUFF = 32;

    template<bool SIGNED = true, typename T>
    inline void WriteFormattedInteger(T val) {
      char str[MAX_BUFF] = {0};
      bool _neg = false;

      // Initialize string
      char* ptr = str + MAX_BUFF;
      *(--ptr) = '\0';

      // Parsing sign and digits
      if(SIGNED && val < 0) {
          val = -val;
          _neg = true;
        }

      while(0 < val && str < ptr) {
          *(--ptr) = '0' + (val % 10);
          val /= 10;
        }

      if(SIGNED && _neg) {
          *(--ptr) = '-';
        }

      // If no digits found
      if(*ptr == '\0') {
          *(--ptr) = '0';
        }

      // Send
      for(; (u32)(ptr - str) < MAX_BUFF ; ptr++) {
          putChar(*ptr);
        }
    }
  };


  //! \brief Abstract two-way stream with formatted read and write.
  template<class Stream>
  class FormattedStreamDecorator :
      public FormattedStreamDecoratorBase<FormattedStreamDecorator<Stream>>,
      public IOStream<FormattedStreamDecorator<Stream>> {

  private:
    Stream& _stream;

    bool _mini_buffer_used = false;
    u8 _mini_buffer = 0;

  public:
    //! \brief Default constructor.
    inline FormattedStreamDecorator(Stream& stream)
      : _stream(stream) {
    }

    u8 nextChar(void) {
      if(!_mini_buffer_used) {
          _mini_buffer_used = true;
          _mini_buffer = _stream.getChar();
        }
      return _mini_buffer;
    }

    u8 getChar(void) {
      if(_mini_buffer_used) {
          _mini_buffer_used = false;
          return _mini_buffer;
        }
      return _stream.getChar();
    }

    u16 read(u8* data, u16 length) {
      if(_mini_buffer_used) {
          _mini_buffer_used = false;
          return 1 + _stream.read(data+1, length-1);
        }
      return _stream.read(data, length);
    }

    void putChar(u8 c) {
      _stream.putChar(c);
    }

    u16 write(const u8* data, u16 length) {
      return _stream.write(data, length);
    }

  public:
    //! \brief Write an integer into the stream.
    //! \param val : the integer to write.
    //! \return A reference to the stream.
    template<typename T>
    inline FormattedStreamDecorator& operator<<(const T val) {
      FormattedStreamDecoratorBase<
          FormattedStreamDecorator<Stream>
          >::WriteFormattedInteger(val);
      return *this;
    }

    //! \brief Read an integer from the stream.
    //! \param val : a reference to the integer to overwrite.
    //! \return A reference to the stream.
    template<typename T>
    inline FormattedStreamDecorator& operator>>(T val) {
      FormattedStreamDecoratorBase<
          FormattedStreamDecorator<Stream>
          >::readFormattedInteger(val);
      return *this;
    }

    //! \brief Write a string into the stream.
    //! \param str : the string to write.
    //! \return A reference to the stream.
    inline FormattedStreamDecorator& operator<<(const char* str) {
      FormattedStreamDecoratorBase<
          FormattedStreamDecorator<Stream>
          >::writeUntilEnd(str);
      return *this;
    }

    //! \brief Read a string from the stream.
    //! \param str : the buffer to write the read string into.
    //! \return A reference to the stream.
    inline FormattedStreamDecorator& operator>>(char* str) {
      FormattedStreamDecoratorBase<
          FormattedStreamDecorator<Stream>
          >::readUntilSeparator(str);
      return *this;
    }
  };

}

#endif//FORMATTED_STREAM_HPP
