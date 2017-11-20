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
#ifndef DEVICE_CONTROL_INPUT_FILTER_HPP
#define DEVICE_CONTROL_INPUT_FILTER_HPP

#include "config.hpp"

#include <filter/filter.hpp>
#include <device/input.hpp>
#include <device/asynchronous.hpp>
#include <base/integer.hpp>
#include <base/type_traits.hpp>

namespace Aversive {
namespace Device {
  namespace Control {

    template<typename InDevice, typename InFilter>
    class InputFilter :
        public Input<typename InFilter::OutputType> {

    private:
      InDevice& _in;
      Filter::AdaptableFilter<typename InFilter::InputType, typename InFilter::OutputType, InFilter>& _filter;

    public:
      inline InputFilter(
          InDevice& in,
          InFilter& filter)
        : _in(in),
          _filter(filter) {
      }

      inline typename InFilter::OutputType get() {
        return _filter(_in.get());
      }
    };

    template<typename InDevice, typename InFilter>
    class AsynchronousInputFilter :
        public Input<typename InFilter::OutputType>,
        public Asynchronous {

    private:
      InputFilter<InDevice, InFilter> _input_filter;
      typename InFilter::OutputType _last;

    public:
      inline AsynchronousInputFilter(
          InDevice& in,
          InFilter& filter)
        : _input_filter(in, filter),
          _last(0) {
      }

      inline void update(void) {
        _last = _input_filter.get();
      }

      inline typename InFilter::OutputType get() {
        return _last;
      }
    };

  }
}
}

#endif//DEVICE_CONTROL_INPUT_FILTER_HPP

