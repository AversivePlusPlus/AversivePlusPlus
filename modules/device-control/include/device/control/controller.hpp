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
#ifndef DEVICE_SYSEM_CONTROLLER_HPP
#define DEVICE_SYSEM_CONTROLLER_HPP

#include "config.hpp"

#include <filter/filter.hpp>
#include <device/output.hpp>
#include <device/input.hpp>
#include <device/asynchronous.hpp>
#include <base/integer.hpp>
#include <base/type_traits.hpp>

namespace Aversive {
namespace Device {
  namespace Control {

    template<typename Actuator, typename Sensor, typename SetpointFilter, typename FeedbackFilter, typename ErrorFilter>
    class SystemController :
        public Output<typename SetpointFilter::InputType>,
        public Asynchronous {

    private:
      Actuator& _actuator;
      Sensor& _sensor;
      Filter::AdaptableFilter<typename SetpointFilter::InputType, typename SetpointFilter::OutputType, SetpointFilter>& _setpoint;
      Filter::AdaptableFilter<typename FeedbackFilter::InputType, typename FeedbackFilter::OutputType, FeedbackFilter>& _feedback;
      Filter::AdaptableFilter<typename ErrorFilter::InputType, typename ErrorFilter::OutputType, ErrorFilter>& _error;
      typename SetpointFilter::InputType _cmd;

      static_assert(TypeEqual<typename SetpointFilter::OutputType, typename FeedbackFilter::OutputType>::VALUE, "Error : incompatible filter types");
      static_assert(TypeEqual<typename SetpointFilter::OutputType, typename ErrorFilter::InputType>::VALUE, "Error : incompatible filter types");

    public:
      inline SystemController(
          Actuator& mot, Sensor& enc,
          SetpointFilter& setpoint,
          FeedbackFilter& feedback,
          ErrorFilter& error)
        : _actuator(mot), _sensor(enc),
          _setpoint(setpoint),
          _feedback(feedback),
          _error(error),
          _cmd(0) {
      }

      inline void update(void) {
        _actuator.put(
              _error(_setpoint(_cmd) - _feedback(_sensor.get()))
              );
      }

      inline void put(typename SetpointFilter::InputType val) {
        _cmd = val;
      }
    };

  }
}
}
  
#endif//DEVICE_SYSEM_CONTROLLER_HPP

