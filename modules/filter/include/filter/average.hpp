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
#ifndef FILTER_MEAN_HPP
#define FILTER_MEAN_HPP

#include <base/array.hpp>
#include <filter/filter.hpp>

namespace Aversive {

namespace Filter {

  //! \brief Average Filter
  /*!

  Basically returns the average of the N last inputs

 */
  template<typename ValueType, u32 N>
  class Average : public Filter<ValueType, Average<ValueType, N>> {
  public:
    using InputType  = ValueType;
    using OutputType = ValueType;

  private:
    Array<InputType, N> _table;
    u32 _head;
    InputType _sum;

  public:
    //! \brief Default Constructor
    inline Average(InputType initial)
      : _table(initial), _head(0), _sum(initial*N) {
    }

    inline OutputType operator()(InputType value) {
      _sum -= _table[_head];
      _table[_head] = value;
      _sum += _table[_head];
      _head = (_head+1)%N;
      return _sum/N;
    }
  };

}

}

#endif//FILTER_MEAN_HPP
