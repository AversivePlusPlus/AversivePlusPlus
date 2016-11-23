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
#ifndef AVERSIVE_DEVICE_HAL_INPUT_DIGITAL_PIN_HPP
#define AVERSIVE_DEVICE_HAL_INPUT_DIGITAL_PIN_HPP

#include <device/input.hpp>
#include <hal/gpio.hpp>

namespace Device {
  namespace HAL {

    struct DefaultInputDigitalPinSettings {
      static constexpr auto pin = 0;

      static constexpr auto output_mode = ::HAL::GPIO::OutputMode::UNDEFINED;
      static constexpr auto pull = ::HAL::GPIO::Pull::UNDEFINED;
    };

    template<typename Settings>
    class InputDigitalPin : public Input<bool, InputDigitalPin<Settings>> {
    public:
      InputDigitalPin(void) {
        ::HAL::GPIO::Settings settings;
        settings.mode = ::HAL::GPIO::Mode::INPUT;
        settings.output_mode = Settings::output_mode;
        settings.pull = Settings::pull;
        ::HAL::GPIO::init(Settings::pin, settings);
      }

      bool getValue(void) {
        return ::HAL::GPIO::getValue(Settings::pin);
      }
    };

  }
}


#endif//AVERSIVE_DEVICE_HAL_INPUT_DIGITAL_PIN_HPP
