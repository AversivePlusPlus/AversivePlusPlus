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
#ifndef AVERSIVE_BASE_COMPIL_HPP
#define AVERSIVE_BASE_COMPIL_HPP

#include <base/literal_parser.hpp>
#include <base/type_traits.hpp>

namespace Base {

  template<typename T, T VAL>
  struct Compil {
    constexpr inline operator T() { return VAL; }
  };

#define AVERSIVE_DEFINE_COMPIL_OPERATOR(op)				\
  template<typename T1, typename T2, T1 VAL1, T2 VAL2>			\
  constexpr inline Compil<T1, (VAL1 op VAL2)>				\
  operator op(const Compil<T1, VAL1>, const Compil<T2, VAL2>) {		\
  return Compil<T1, (VAL1 op VAL2)>();				\
}									\

  AVERSIVE_DEFINE_COMPIL_OPERATOR(+);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(-);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(*);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(/);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(%);

  AVERSIVE_DEFINE_COMPIL_OPERATOR(&);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(|);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(^);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(&&);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(||);

  AVERSIVE_DEFINE_COMPIL_OPERATOR(<<);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(>>);

  AVERSIVE_DEFINE_COMPIL_OPERATOR(==);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(!=);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(<=);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(>=);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(<);
  AVERSIVE_DEFINE_COMPIL_OPERATOR(>);

#undef AVERSIVE_DEFINE_COMPIL_OPERATOR

#define AVERSIVE_DEFINE_COMPIL_UNARY_OPERATOR(op)	\
  template<typename T, T VAL>				\
  constexpr inline Compil<T, (op VAL)>			\
  operator op(const Compil<T, VAL>) {			\
  return Compil<T, (op VAL)>();			\
}							\

  AVERSIVE_DEFINE_COMPIL_UNARY_OPERATOR(+);
  AVERSIVE_DEFINE_COMPIL_UNARY_OPERATOR(-);
  AVERSIVE_DEFINE_COMPIL_UNARY_OPERATOR(~);
  AVERSIVE_DEFINE_COMPIL_UNARY_OPERATOR(!);

#undef AVERSIVE_DEFINE_COMPIL_UNARY_OPERATOR

  template<typename T> struct RemoveCompil { using Type = T; };
  template<typename T, T VAL> struct RemoveCompil<Compil<T, VAL>> { using Type = T; };

  template<typename T> struct SecureCompil {
    using Type =
    typename RemoveCompil<
    typename RemoveRef<
    typename RemoveConst<
    T
    >::Type
    >::Type
    >::Type;
  };

#define COMPIL(i)							\
  Compil<typename SecureCompil<decltype(i)>::Type, (typename SecureCompil<decltype(i)>::Type)i>()

#define AVERSIVE_DEFINE_COMPIL_LITERAL(type, name)			\
  template<char...ARGS>							\
  constexpr Compil<type, LiteralParser::Parser<LiteralParser::BEG, type, 0, ARGS...>::VALUE> \
  operator "" _##name() {						\
  return Compil<type, LiteralParser::Parser<LiteralParser::BEG, type, 0, ARGS...>::VALUE>(); \
}

  AVERSIVE_DEFINE_COMPIL_LITERAL(u8 , cu8 )
  AVERSIVE_DEFINE_COMPIL_LITERAL(u16, cu16)
  AVERSIVE_DEFINE_COMPIL_LITERAL(u32, cu32)
  AVERSIVE_DEFINE_COMPIL_LITERAL(u64, cu64)

  AVERSIVE_DEFINE_COMPIL_LITERAL(s8 , cs8 )
  AVERSIVE_DEFINE_COMPIL_LITERAL(s16, cs16)
  AVERSIVE_DEFINE_COMPIL_LITERAL(s32, cs32)
  AVERSIVE_DEFINE_COMPIL_LITERAL(s64, cs64)

  AVERSIVE_DEFINE_COMPIL_LITERAL(usys, cusys)

  AVERSIVE_DEFINE_COMPIL_LITERAL(int, c)

#undef AVERSIVE_DEFINE_COMPIL_LITERAL


}

#ifndef AVERSIVE_DISABLE_BASE_DEFAULT
using namespace Base;
#endif//AVERSIVE_DISABLE_BASE_DEFAULT

#endif//AVERSIVE_BASE_COMPIL_HPP
