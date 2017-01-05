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
#ifndef FIXED_POINT_HPP
#define FIXED_POINT_HPP

#include "config.hpp"
#include "integer.hpp"

namespace Aversive {

namespace Base {

  template<typename T, u16 SHIFT>
  class FixedPoint {
  private:
    T _value;

    constexpr FixedPoint(const T val, bool)
      : _value(val) {
    }

  public:
    constexpr FixedPoint(void)
      : _value(0){
    }

    constexpr FixedPoint(const double val)
      : _value((T)(val*(double)((T)1<<SHIFT))){
    }

    constexpr FixedPoint(const float val)
      : _value((T)(val*(float)((T)1<<SHIFT))){
    }

    template<typename T2>
    explicit constexpr FixedPoint(const T2 val)
      : _value((T)val<<SHIFT) {
    }

    constexpr FixedPoint(const FixedPoint& other)
      : _value(other._value) {
    }

    constexpr FixedPoint operator+(const FixedPoint& other) {
      return FixedPoint(_value + other._value, true);
    }

    constexpr FixedPoint operator-(const FixedPoint& other) {
      return FixedPoint(_value - other._value, true);
    }

    constexpr FixedPoint operator-(void) {
      return FixedPoint(-_value, true);
    }

    constexpr FixedPoint operator*(const FixedPoint& other) {
      return FixedPoint((_value * other._value)>>SHIFT, true);
    }

    constexpr FixedPoint operator/(const FixedPoint& other) {
      return FixedPoint(((_value<<(SHIFT/2)) / other._value)<<(SHIFT-SHIFT/2), true);
    }

    explicit constexpr operator double(void) {
      return ((double)_value)/(double)((T)1<<SHIFT);
    }

    explicit constexpr operator float(void) {
      return ((float)_value)/(float)((T)1<<SHIFT);
    }

    explicit constexpr operator int(void) {
      return _value>>SHIFT;
    }

    FixedPoint& operator+=(const FixedPoint& other) {
      *this = *this + other;
      return *this;
    }

    FixedPoint& operator-=(const FixedPoint& other) {
      *this = *this - other;
      return *this;
    }

    FixedPoint& operator*=(const FixedPoint& other) {
      *this = *this * other;
      return *this;
    }

    FixedPoint& operator/=(const FixedPoint& other) {
      *this = *this / other;
      return *this;
    }
  };

  template<typename T, u16 SHIFT>
  bool operator!=(const FixedPoint<T, SHIFT>& fx, double val) {
    return (double)fx != val;
  }


  template<typename T, u16 SHIFT>
  bool operator>(const FixedPoint<T, SHIFT>& fx, double val) {
    return (double)fx > val;
  }

}

}

#endif//FIXED_POINT_HPP
