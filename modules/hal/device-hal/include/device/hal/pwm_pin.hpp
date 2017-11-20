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
#ifndef AVERSIVE_DEVICE_HAL_PWM_PIN_HPP
#define AVERSIVE_DEVICE_HAL_PWM_PIN_HPP

#include <device/output.hpp>
#include <hal/pwm.hpp>
#include <hal/timer.hpp>

namespace Aversive {
namespace Device {
  namespace HAL {

    struct DefaultPWMPinSettings {
      static constexpr auto pwm = 0;
      static constexpr auto pin = 0;
    };

    struct DefaultPWMTimerSettings {
      static constexpr auto timer = 0;

      static constexpr auto period = 20000;
    };

    template<typename Settings>
    class PWMPin : public Output<u32, PWMPin<Settings>> {
    public:
      PWMPin(void) {
        ::HAL::PWM::Settings settings;
        settings.polarity = ::HAL::PWM::Polarity::HIGH;
        ::HAL::PWM::init(Settings::pwm, Settings::pin, settings);
      }

    public:
      void setValue(u32 value) {
        ::HAL::PWM::setPulseWidth(Settings::pwm, value);
      }
    };

    template<typename Settings>
    class PWMTimer {
    public:
      PWMTimer(void) {
        ::HAL::TIMER::Settings settings;
        settings.period = Settings::period;
        ::HAL::TIMER::init(Settings::timer, settings);
      }

      void start(void) {
        ::HAL::TIMER::start(Settings::timer);
      }

      void stop(void) {
        ::HAL::TIMER::stop(Settings::timer);
      }

      void pause(void) {
        ::HAL::TIMER::pause(Settings::timer);
      }
    };

  }
}
}

#endif//AVERSIVE_DEVICE_HAL_PWM_PIN_HPP
