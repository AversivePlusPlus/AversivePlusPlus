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
#ifndef FILTER_PARALLEL_HPP
#define FILTER_PARALLEL_HPP

#include <base/type_traits.hpp>
#include <filter/filter.hpp>

namespace Filter {

  template <class First, class Second>
  class Parallel :
      public AdaptableFilter<typename First::InputType, typename First::OutputType, Parallel<First, Second>> {
  public:
    using InputType  = typename First::InputType;
    using OutputType = typename First::OutputType;

    static_assert(
        TypeEqual<typename First::InputType, typename Second::InputType>::VALUE &&
        TypeEqual<typename First::OutputType, typename Second::OutputType>::VALUE,
        "ERROR : incompatibles filters in parallel"
        );

  private:
    using FirstFilter = AdaptableFilter<typename First::InputType, typename First::OutputType, First>;
    using SecondFilter = AdaptableFilter<typename Second::InputType, typename Second::OutputType, Second>;

    FirstFilter& first;
    SecondFilter& second;

  public:
    inline Parallel(FirstFilter& first, SecondFilter& second)
      : first(first), second(second) {
    }

    inline OutputType operator()(InputType value) {
      return second(value) + first(value);
    }
  };

}

#endif//FILTER_PARALLEL_HPP
