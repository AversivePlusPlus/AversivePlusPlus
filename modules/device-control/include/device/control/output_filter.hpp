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
#ifndef DEVICE_CONTROL_OUTPUT_FILTER_HPP
#define DEVICE_CONTROL_OUTPUT_FILTER_HPP

#include <filter/filter.hpp>
#include <device/output.hpp>
#include <device/asynchronous.hpp>
#include <base/integer.hpp>
#include <base/type_traits.hpp>

namespace Device {
  namespace Control {

    template<typename OutDevice, typename OutFilter>
    class OutputFilter :
        public Output<typename OutFilter::InputType, OutputFilter<OutDevice, OutFilter>> {

    private:
      Output<typename OutFilter::OutputType, OutDevice>& _out;
      Filter::AdaptableFilter<typename OutFilter::InputType, typename OutFilter::OutputType, OutFilter>& _filter;

    public:
      inline OutputFilter(
          OutDevice& in,
          OutFilter& filter)
        : _out(in),
          _filter(filter) {
      }
      inline void setValue(typename OutFilter::InputType val) {
        _out.setValue(_filter(val));
      }
    };

    template<typename OutDevice, typename OutFilter>
    class AsynchronousOutputFilter :
        public Output<typename OutFilter::InputType, AsynchronousOutputFilter<OutDevice, OutFilter>>,
        public Asynchronous<AsynchronousOutputFilter<OutDevice, OutFilter>> {

    private:
      OutputFilter<OutDevice, OutFilter> _output_filter;
      typename OutFilter::InputType _cmd;

    public:
      inline AsynchronousOutputFilter(
          OutDevice& in,
          OutFilter& filter)
        : _output_filter(in, filter),
          _cmd(0) {
      }

      inline void update(void) {
        _output_filter.setValue(_cmd);
      }

      inline void setValue(typename OutFilter::InputType val) {
        _cmd = val;
      }
    };

  }
}

#endif//DEVICE_CONTROL_OUTPUT_FILTER_HPP

