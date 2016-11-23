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
#ifndef FILTER_LIMITER_HPP
#define FILTER_LIMITER_HPP

#include <filter/filter.hpp>

namespace Filter {

  //! \brief Limiter Filter
  /*!
  If the input is contained in the interval, return the input.
  Otherwise, return the interval's limit that is the nearest of the input.
 */
  template<typename ValueType>
  class Limiter : public Filter<ValueType, Limiter<ValueType>> {
  public:
    using InputType  = ValueType;
    using OutputType = ValueType;

  private:
    InputType _min;
    InputType _max;

  public:
    //! \brief Default Constructor
    inline Limiter(InputType min, InputType max)
      : _min(min), _max(max) {
    }
    
    //! \brief Computes output in function of input
    inline OutputType operator()(InputType value) {
      return (value < _min) ? _min :
             (value > _max) ? _max :
             value;
    }

    inline InputType min(void) {
      return _min;
    }

    inline InputType max(void) {
      return _max;
    }

    inline void setMin(InputType min) {
      _min = min;
    }

    inline void setMax(InputType max) {
      _max = max;
    }

  };

}

#endif//FILTER_LIMITER_HPP
