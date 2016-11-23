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
#ifndef HAL_STM32CUBEF4_PWM_HPP
#define HAL_STM32CUBEF4_PWM_HPP

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>

#include <hal/pwm_interface.hpp>
#include <hal/stm32cubef4/gpio.hpp>
#include <hal/stm32cubef4/timer.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {

  namespace STM32CubeF4 {

    struct PWM : PWM_DriverInterface {
      using Parent = PWM_DriverInterface;

      //! \brief The OutputCompare Signal Polarity
      struct Polarity : Parent::Polarity {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(HIGH);
        AVERSIVE_AVAILABLE_ELEMENT(LOW);
      };

      template<int ID, int PIN, typename Settings>
      static void init(Private::PWM_Type<ID> pwm, Private::PIN_Type<PIN> pin, const Settings&) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(Private::port(pin));
        Private::clk_enable(Private::port(pin));

        GPIO_InitTypeDef gpio_init;
        gpio_init.Pull = GPIO_PULLDOWN;
        gpio_init.Speed = GPIO_SPEED_HIGH;
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Alternate = Private::cube_gpio_timer_af(Private::timer(pwm));
        gpio_init.Pin = Private::cube_gpio_offset(Private::offset(pin));
        HAL_GPIO_Init(gpio, &gpio_init);

        auto& timer_handle = Private::get_timer_cube_handle<Private::timer(pwm)>();

        TIM_OC_InitTypeDef oc_enable;
        //oc_enable.OCMode = TIM_OCMODE_PWM2;
        oc_enable.OCMode = TIM_OCMODE_PWM1;
        oc_enable.OCPolarity = TIM_OCPOLARITY_HIGH;
        oc_enable.OCFastMode = TIM_OCFAST_DISABLE;
        oc_enable.Pulse = 0;

        u32 chan = Private::cube_timer_channel(Private::channel(pwm));
        HAL_TIM_OC_ConfigChannel(&timer_handle, &oc_enable, chan);
        HAL_TIM_OC_Start(&timer_handle, chan);
      }

      template<int ID>
      static void setPulseWidth(Private::PWM_Type<ID> pwm, u16 value) {
        u32 chan = Private::cube_timer_channel(Private::channel(pwm));
        TIM_HandleTypeDef& _timer = Private::get_timer_cube_handle<Private::timer(pwm)>();
        __HAL_TIM_SetCompare(&_timer, chan, ((u32)value*_timer.Instance->ARR)/65536);
      }
    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_STM32CUBEF4_PWM_HPP
