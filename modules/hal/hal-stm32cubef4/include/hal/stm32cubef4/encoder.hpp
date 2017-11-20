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
#ifndef HAL_STM32CUBEF4_ENCODER_HPP
#define HAL_STM32CUBEF4_ENCODER_HPP

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>

#include <hal/encoder_interface.hpp>
#include <hal/stm32cubef4/gpio.hpp>
#include <hal/stm32cubef4/timer.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

using namespace Aversive::Base;

namespace HAL {

  namespace STM32CubeF4 {

    struct ENCODER : ENCODER_DriverInterface {
      using Parent = ENCODER_DriverInterface;

      //! \brief The Encoder Mode
      struct Mode : Parent::Mode {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(CHANNEL1_COUNT);
        AVERSIVE_AVAILABLE_ELEMENT(CHANNEL2_COUNT);
        AVERSIVE_AVAILABLE_ELEMENT(BOTH_COUNT);
      };

      //! \brief The Encoder Polarity
      struct Polarity : Parent::Polarity {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(RISING);
        AVERSIVE_AVAILABLE_ELEMENT(FALLING);
        AVERSIVE_AVAILABLE_ELEMENT(BOTH);
      };

      template<typename TIMERType, typename C1PinType, typename C2PinType, typename Settings>
      static void init(TIMERType timer, C1PinType c1, C2PinType c2, const Settings& settings) {

        GPIO_InitTypeDef gpio_init;
        gpio_init.Pull = GPIO_PULLUP;
        gpio_init.Speed = GPIO_SPEED_HIGH;
        gpio_init.Mode = GPIO_MODE_AF_PP;
        gpio_init.Alternate = Private::cube_gpio_timer_af(timer);

        gpio_init.Pin = Private::cube_gpio_offset(offset(c1));
        Private::clk_enable(port(c1));
        HAL_GPIO_Init(Private::cube_gpio_port(port(c1)), &gpio_init);

        gpio_init.Pin = Private::cube_gpio_offset(offset(c2));
        Private::clk_enable(port(c2));
        HAL_GPIO_Init(Private::cube_gpio_port(port(c2)), &gpio_init);

        Private::clk_enable(timer);

        TIM_HandleTypeDef& timer_handle = Private::get_timer_cube_handle<timer>();
        timer_handle.Instance = Private::cube_timer(timer);
        timer_handle.Init.Period = 65535;

        TIM_Encoder_InitTypeDef enc_init;
        enc_init.EncoderMode = Private::cube_encoder_mode(settings.mode);

        enc_init.IC1Polarity = Private::cube_encoder_polarity(settings.channel1.polarity);
        enc_init.IC2Polarity = Private::cube_encoder_polarity(settings.channel2.polarity);

        enc_init.IC1Selection = TIM_ICSELECTION_DIRECTTI;
        enc_init.IC2Selection = TIM_ICSELECTION_DIRECTTI;

        enc_init.IC1Prescaler = TIM_ICPSC_DIV1;
        enc_init.IC2Prescaler = TIM_ICPSC_DIV1;

        enc_init.IC1Filter = 0;
        enc_init.IC2Filter = 0;

        HAL_TIM_Encoder_Init(&timer_handle, &enc_init);

        __HAL_TIM_SetCounter(&timer_handle,0);
        HAL_TIM_Encoder_Start(&timer_handle, TIM_CHANNEL_1 | TIM_CHANNEL_2);
      }

      template<typename TIMERType>
      static typename TIMERType::CounterType getCounter(TIMERType timer) {
        return Private::cube_timer(timer)->CNT;
      }

      template<typename TIMERType>
      static void setCounter(TIMERType timer, typename TIMERType::CounterType value) {
        Private::cube_timer(timer)->CNT = value;
      }
    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_STM32CUBEF4_ENCODER_HPP
