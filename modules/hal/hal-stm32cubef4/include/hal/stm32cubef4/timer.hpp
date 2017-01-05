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
#ifndef HAL_STM32CUBEF4_TIMER_HPP
#define HAL_STM32CUBEF4_TIMER_HPP

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>

#include <hal/timer_interface.hpp>
#include <hal/stm32cubef4/traits.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

using namespace Aversive::Base;

namespace HAL {

  namespace STM32CubeF4 {

    namespace Private {

      template<int ID>
      Func& get_timer_irq_handler();

      template<int ID>
      TIM_HandleTypeDef& get_timer_cube_handle();

    }

    //! \brief TIMER Driver Interface
    //! \param T : The type of a standard Timer Counter Register
    struct TIMER : TIMER_DriverInterface {

      static inline u32 _getPrescaler(u32 period) {
        u32 f_sys = HAL_RCC_GetSysClockFreq();
        u32 coeff_user = (f_sys / 1000000) * period;
        u32 ret = 1;
        while((coeff_user / ret) > 0xFFFF) {
            ret++;
          }
        return ret;
      }

      static inline u32 _getPeriod(u32 period) {
        u32 f_sys = HAL_RCC_GetSysClockFreq();
        u32 coeff_user = (f_sys / 1000000) * period;
        return coeff_user / _getPrescaler(period);
      }

      template<int ID, typename Settings>
      static void init(Private::TIMER_Type<ID> timer, const Settings& settings) {
        auto& timer_handle = Private::get_timer_cube_handle<timer>();
        timer_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
        timer_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
        timer_handle.Init.Prescaler = _getPrescaler(settings.period)-1;
        timer_handle.Init.Period = _getPeriod(settings.period)-1;
        timer_handle.Init.RepetitionCounter = 0x0;

        Private::clk_enable(timer);

        timer_handle.Instance = Private::cube_timer(timer);
        HAL_TIM_Base_Init(&timer_handle);
        HAL_TIM_Base_Stop_IT(&timer_handle);
        __HAL_TIM_SetCounter(&timer_handle,0);
      }

      template<int ID, typename IRQ_Handler>
      static void setOverflowHandler(Private::TIMER_Type<ID> timer, IRQ_Handler handler) {
        Private::get_timer_irq_handler<timer>() = handler;

        IRQn_Type irq = get_timer_irq(timer);
        HAL_NVIC_EnableIRQ(irq);
        HAL_NVIC_SetPriority(irq, 2,2);
      }

      template<int ID>
      static void start(Private::TIMER_Type<ID> timer) {
        auto& timer_handle = Private::get_timer_cube_handle<timer>();
        HAL_TIM_Base_Start_IT(&timer_handle);
      }

      template<int ID>
      static void stop(Private::TIMER_Type<ID> timer) {
        auto& timer_handle = Private::get_timer_cube_handle<timer>();
        HAL_TIM_Base_Stop_IT(&timer_handle);
        __HAL_TIM_SetCounter(&timer_handle,0);
      }

      template<int ID>
      static void pause(Private::TIMER_Type<ID> timer) {
        auto& timer_handle = Private::get_timer_cube_handle<timer>();
        HAL_TIM_Base_Stop_IT(&timer_handle);
      }
    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_STM32CUBEF4_TIMER_HPP
