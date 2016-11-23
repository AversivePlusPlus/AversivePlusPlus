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
#ifndef FILTER_PID_HPP
#define FILTER_PID_HPP

#include <filter/proportional.hpp>
#include <filter/integral.hpp>
#include <filter/derivate.hpp>
#include <filter/limiter.hpp>

#include <filter/chain.hpp>
#include <filter/parallel.hpp>

namespace Filter {

  //! \brief PID Filter
  template<typename ValueType>
  class Pid : public Filter<ValueType, Pid<ValueType>> {
  public:
    using InputType  = ValueType;
    using OutputType = ValueType;

  private:
    Proportional<ValueType> _pp;
    Proportional<ValueType> _pi;
    Proportional<ValueType> _pd;

    Integral<ValueType> _i;
    Derivate<ValueType> _d;

    Limiter<ValueType> _li;

    // in --> Integral --> Proportional --> Limiter --> out
    Chain<decltype(_i), decltype(_pi)> _ci{_i, _pi};
    Chain<decltype(_ci), decltype(_li)> _cil{_ci, _li};

    // in --> Derivate --> Proportional --> out
    Chain<decltype(_d), decltype(_pd)> _cd{_d, _pd};

    // in --> Integral --> Proportional --> Limiter -+> out
    //    `->        Derivate --> Proportional      -^
    Parallel<decltype(_cil), decltype(_cd)> _id{_cil, _cd};

    // in --> Integral --> Proportional --> Limiter -+> Limiter --> out
    //    `->        Derivate --> Proportional      -^
    //    `->              Proportional             -^
    Parallel<decltype(_pp), decltype(_id)> _pid{_pp, _id};

  public:
    //! \brief Constructor with initialisation of all gains
    inline Pid(InputType initial, InputType p = 1, InputType i = 0, InputType d = 0, InputType max_i = 0)
      : _pp(p), _pi(i), _pd(d), _i(initial), _d(initial), _li(-max_i, max_i) {
    }

    //! \brief Compute output in function of input
    inline OutputType operator()(InputType value) {
      return _pid(value);
    }

    inline void reset(InputType initial = 0) {
      _i.reset(0);
      _d.reset(0);
    }

    inline void setGains(InputType p, InputType i, InputType d) {
      _pp.setGain(p);
      _pi.setGain(i);
      _pd.setGain(d);
    }

    inline void setMaxIntegral(InputType max_i) {
      _li.setMin(-max_i);
      _li.setMax(max_i);
    }
  };

}

#endif//FILTER_PID_HPP
