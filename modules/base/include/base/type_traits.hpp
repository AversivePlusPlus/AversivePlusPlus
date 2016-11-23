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
#ifndef BASE_TYPE_TRAITS_HPP
#define BASE_TYPE_TRAITS_HPP

namespace Base {

  template<typename T> struct RemoveConst { using Type = T; };
  template<typename T> struct RemoveConst<const T> { using Type = T; };

  template<typename T> struct RemoveRef { using Type = T; };
  template<typename T> struct RemoveRef<T&> { using Type = T; };
  template<typename T> struct RemoveRef<T&&> { using Type = T; };


  template<typename ...TArgs> struct TypeEqual {};

  template<typename T1, typename T2, typename ...TArgs> struct TypeEqual<T1, T2, TArgs...> {
    static constexpr bool VALUE = TypeEqual<T1, T2>::VALUE && TypeEqual<T2, TArgs...>::VALUE;
  };

  template<typename T1, typename T2> struct TypeEqual<T1, T2> {
    static constexpr bool VALUE = false;
  };

  template<typename T> struct TypeEqual<T, T> {
    static constexpr bool VALUE = true;
  };

  template<typename T> struct TypeEqual<T> {
    static constexpr bool VALUE = true;
  };

}

#ifndef AVERSIVE_DISABLE_BASE_DEFAULT
using namespace Base;
#endif//AVERSIVE_DISABLE_BASE_DEFAULT

#endif//BASE_TYPE_TRAITS_HPP
