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
#ifndef HAL_PWM_INTERFACE_HPP
#define HAL_PWM_INTERFACE_HPP

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

using namespace Aversive::Base;

namespace HAL {
  
  //! \brief PWM Driver Interface
  struct PWM_DriverInterface {

    //! \brief The OutputCompare Signal Polarity
    struct Polarity {
      enum class Type : u8 { UNDEFINED, HIGH, LOW };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(HIGH);
      AVERSIVE_UNAVAILABLE_ELEMENT(LOW);
    };
        
    //! \brief The OutputCompare Pulse Width
    struct Settings {
      typename Polarity::Type polarity;
    };

    //! \brief Configure the PWM Channel
    template<typename PWMType, typename PinType, typename Settings>
    static void init(PWMType pwm, PinType pin, const Settings& settings) AVERSIVE_UNAVAILABLE;

    //! \brief Set the Pulse Width (percentage)
    //! \detail The unit is a value from 0 to 65535
    //! \detail 0 correspond to a PWM of 0%
    //! \detail 65535 correspond to a PWM of 100%
    template<typename PWMType, typename PWType>
    static void setPulseWidth(PWMType pwm, PWType value) AVERSIVE_UNAVAILABLE;

    //! \brief Get the Pulse Width (percentage)
    //! \detail The unit is a value from 0 to 65535
    //! \detail 0 correspond to a PWM of 0%
    //! \detail 65535 correspond to a PWM of 100%
    template<typename PWMType>
    static u32 getPulseWidth(PWMType pwm) AVERSIVE_UNAVAILABLE;

    //! \brief Get the interrupt handler for comparison event
    template<typename PWMType, typename IRQ_Handler>
    static void setComparHandler(PWMType pwm, IRQ_Handler handler) AVERSIVE_UNAVAILABLE;

  };

}

#include <hal/macros_undef.hpp>

#endif//HAL_PWM_INTERFACE_HPP
