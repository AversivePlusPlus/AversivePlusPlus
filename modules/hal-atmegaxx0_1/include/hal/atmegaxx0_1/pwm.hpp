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
#ifndef HAL_ATMEGAXX0_1_PWM_HPP
#define HAL_ATMEGAXX0_1_PWM_HPP

#include <hal/pwm_interface.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {

  namespace ATMegaxx0_1 {

    //! \brief PWM Driver
    struct PWM : public PWM_DriverInterface {
      using Parent = PWM_DriverInterface;

      //! \brief The OutputCompare Signal Polarity
      struct Polarity : Parent::Polarity {
        AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_UNAVAILABLE_ELEMENT(HIGH);
        AVERSIVE_UNAVAILABLE_ELEMENT(LOW);
      };

      //! \brief Configure the PWM Channel
      template<typename PWMType, typename PinType, typename Settings>
      static void init(PWMType pwm, PinType pin, const Settings& settings) AVERSIVE_UNAVAILABLE;

      //! \brief Set the Pulse Width (in us)
      template<typename PWMType, typename PWType>
      static void setPulseWidth(PWMType pwm, PWType value) AVERSIVE_UNAVAILABLE;

      //! \brief Get the Pulse Width (in us)
      template<typename PWMType>
      static u32 getPulseWidth(PWMType pwm) AVERSIVE_UNAVAILABLE;

      //! \brief Get the interrupt handler for comparison event
      template<typename PWMType, typename IRQ_Handler>
      static void setComparHandler(PWMType pwm, IRQ_Handler handler) AVERSIVE_UNAVAILABLE;

    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_ATMEGAXX0_1_PWM_HPP
