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
#ifndef AVERSIVE_DEVICE_HAL_ENCODER_HPP
#define AVERSIVE_DEVICE_HAL_ENCODER_HPP

#include <device/input.hpp>
#include <hal/encoder.hpp>

namespace Device {
  namespace HAL {

    struct DefaultEncoderSettings {
      static constexpr auto timer = 0;
      static constexpr auto channel1 = 0;
      static constexpr auto channel2 = 0;

      static constexpr auto mode = ::HAL::ENCODER::Mode::BOTH_COUNT;
      static constexpr auto channel1_polarity = ::HAL::ENCODER::Polarity::RISING;
      static constexpr auto channel2_polarity = ::HAL::ENCODER::Polarity::RISING;
    };

    template<typename Settings>
    class Encoder : public Input<u32, Encoder<Settings>> {
    public:
      Encoder(void) {
        ::HAL::ENCODER::Settings settings;
        settings.mode = Settings::mode;
        settings.channel1.polarity = Settings::channel1_polarity;
        settings.channel2.polarity = Settings::channel2_polarity;
        ::HAL::ENCODER::init(Settings::timer, Settings::channel1, Settings::channel2, settings);
      }

      u32 getValue(void) {
        return ::HAL::ENCODER::getCounter(Settings::timer);
      }

      void reset(void) {
        return ::HAL::ENCODER::setCounter(Settings::timer, 0);
      }
    };

  }
}


#endif//AVERSIVE_DEVICE_HAL_ENCODER_HPP
