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
#ifndef AVERSIVE_BASE_LITERAL_PARSER_HPP
#define AVERSIVE_BASE_LITERAL_PARSER_HPP

#include "config.hpp"
#include "integer.hpp"
#include "dummy.hpp"

namespace Aversive {

namespace Base {

  namespace LiteralParser {
    enum ParserState {
      BEG,
      OCT,
      HEX,
      BIN,
      DEC
    };

    // NUMERIC VALUE
    template<ParserState STATE, typename T, T RES, u8 CHAR> struct Numeric {};

    template<typename T, T RES, u8 CHAR>
    struct Numeric<BIN, T, RES, CHAR> {
      static_assert(('0' <= CHAR) && (CHAR < '1'+1), "ERROR : invalid binary character");
      static constexpr T VALUE = RES*2+CHAR-'0';
    };

    template<typename T, T RES, u8 CHAR>
    struct Numeric<OCT, T, RES, CHAR> {
      static_assert(('0' <= CHAR) && (CHAR < '9'+1), "ERROR : invalid octal character");
      static constexpr T VALUE = RES*8+CHAR-'0';
    };

    template<typename T, T RES, u8 CHAR>
    struct Numeric<DEC, T, RES, CHAR> {
      static_assert(('0' <= CHAR) && (CHAR < '9'+1), "ERROR : invalid decimal character");
      static constexpr T VALUE = RES*10+CHAR-'0';
    };

    template<typename T, T RES, u8 CHAR>
    struct Numeric<HEX, T, RES, CHAR> {
    private:
      static constexpr bool NUM   = ('0' <= CHAR) && (CHAR < '9'+1);
      static constexpr bool UPPER = ('A' <= CHAR) && (CHAR < 'F'+1);
      static constexpr bool LOWER = ('a' <= CHAR) && (CHAR < 'f'+1);
      static constexpr u8 FLAG = (NUM?1:0) | (UPPER?2:0) | (LOWER?4:0);

      template<u8 FLAG, DummyType DUMMY = DUMMY_VALUE>
      struct Helper {
        static_assert(!FLAG&&FLAG, "ERROR : invalid hexadecimal character");
      };

      template<DummyType DUMMY>
      struct Helper<0b001, DUMMY> {
        static constexpr T VALUE = CHAR-'0';
      };

      template<DummyType DUMMY>
      struct Helper<0b010, DUMMY> {
        static constexpr T VALUE = CHAR-'A'+10;
      };

      template<DummyType DUMMY>
      struct Helper<0b100, DUMMY> {
        static constexpr T VALUE = CHAR-'a'+10;
      };

    public:
      static constexpr T VALUE = RES*16+Helper<FLAG>::VALUE;
    };

    // DEFAULT
    template<ParserState STATE, typename T, T RES, char FIRST, char ... NEXT>
    struct Parser {
      static constexpr T VALUE = Parser<STATE, T,  Numeric<STATE, T, RES, FIRST>::VALUE, NEXT...>::VALUE;
    };

    template<ParserState STATE, typename T, T RES, char FIRST>
    struct Parser<STATE, T, RES, FIRST> {
      static constexpr T VALUE = Numeric<STATE, T, RES, FIRST>::VALUE;
    };

    // PARTICULAR CASES
    template<typename T, T RES, char FIRST>
    struct Parser<BEG, T, RES, FIRST> {
      static constexpr T VALUE = Numeric<DEC, T, RES, FIRST>::VALUE;
    };

    template<typename T, T RES>
    struct Parser<BEG, T, RES, '0'> {
      static constexpr T VALUE = 0;
    };

    // BEG
    template<typename T, T RES, char FIRST, char ... NEXT>
    struct Parser<BEG, T, RES, FIRST, NEXT...> {
      static constexpr T VALUE = Parser<DEC, T, RES, FIRST, NEXT...>::VALUE;
    };

    template<typename T, T RES, char ... NEXT>
    struct Parser<BEG, T, RES, '0', NEXT...> {
      static constexpr T VALUE = Parser<OCT, T, RES, NEXT...>::VALUE;
    };

    // OCT
    template<typename T, T RES, char ... NEXT>
    struct Parser<OCT, T, RES, 'x', NEXT...> {
      static constexpr T VALUE = Parser<HEX, T, RES, NEXT...>::VALUE;
    };

    template<typename T, T RES, char ... NEXT>
    struct Parser<OCT, T, RES, 'b', NEXT...> {
      static constexpr T VALUE = Parser<BIN, T, RES, NEXT...>::VALUE;
    };

  }

}

}

#endif//AVERSIVE_BASE_LITERAL_PARSER_HPP
