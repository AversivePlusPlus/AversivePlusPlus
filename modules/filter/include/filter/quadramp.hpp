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
#ifndef FILTER_QUADRAMP_HPP
#define FILTER_QUADRAMP_HPP

#include <filter/filter.hpp>

#include <filter/integral.hpp>
#include <filter/derivate.hpp>
#include <filter/difference.hpp>

#include <math.h>

namespace Aversive {

namespace Filter {

  template<typename ValueType>
  class Quadramp : public Filter<ValueType, Quadramp<ValueType>> {
  public:
    using InputType  = ValueType;
    using OutputType = ValueType;

  private:

    Integral<InputType> Ispe;
    Integral<InputType> Ipos;

    Derivate<InputType> Dacc;
    Derivate<InputType> Dspe;

    InputType amin;
    InputType amax;
    InputType sneg;
    InputType spos;

  private:
    //Utility

    template<typename T>
    static inline T _min(T v1, T v2) {
      return v1 < v2 ? v1 : v2;
    }

    template<typename T>
    static inline T _max(T v1, T v2) {
      return v1 > v2 ? v1 : v2;
    }

    template<typename T>
    static inline T _sqrt(T val) {
      return sqrt(val);
    }

    template<typename T>
    static inline T _abs(T val) {
      return (val < 0) ? -val : val;
    }

  private:
    static InputType speedCmd(InputType dpos, InputType smax, InputType amin) {
      // Quadramp function
      return _min(_sqrt(amin*dpos*2)-_min(amin, (amin)*dpos)/2, smax);
    }


    static InputType speedErr(InputType spe, InputType cur_spe, InputType amax, InputType amin) {
      // If not fast enough
      if(cur_spe < spe) {
          return _min(amax, spe-cur_spe);
        }
      // Too fast !
      else if(cur_spe > spe) {
          return _max(-amin, spe-cur_spe);
        }
      return 0.;
    }

  public:
    Quadramp(InputType initial, InputType spos, InputType sneg, InputType amax, InputType amin)
      : Ispe(0), Ipos(initial), Dacc(0), Dspe(0),
        amin(amin), amax(amax), sneg(sneg), spos(spos) {
    }

    OutputType operator()(InputType cmd){
      Difference<InputType> DIFF(cmd);
      InputType pos = Ipos(0);
      InputType spe = 0;
      InputType cur_spe = Dspe(pos);

      // Below setpoint
      if(DIFF(pos) > 0) {
          spe = speedCmd(DIFF(pos), spos, -amin);
          spe = Ispe(speedErr(spe, cur_spe, amax, -amin));
        }
      // Over setpoint
      else if(DIFF(pos) < 0) {
          spe = -speedCmd(-DIFF(pos), -sneg, -amin);
          spe = Ispe(-speedErr(-spe, -cur_spe, amax, -amin));
        }
      // At setpoint
      else {
          Ispe.reset();
        }

      // If near setpoint
      if((amin < DIFF(pos) && DIFF(pos) < -amin) ||
         (-_abs(spe) < DIFF(pos) && DIFF(pos) < _abs(spe))) {
          spe = DIFF(pos);
          pos = Ipos(spe);
        }
      // Normal speed integration
      else {
          pos = Ipos(spe);
        }
      return pos;
    }
  };


}

}

#endif//FILTER_QUADRAMP_HPP
