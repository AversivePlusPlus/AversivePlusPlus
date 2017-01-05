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
#ifndef HAL_STM32CUBEF4_TRAITS_HPP
#error "This file must not be included directly, include traits.hpp instead"
#endif

#define AVERSVE_IS_TIMER_CHANNEL(timer, channel) \
  ( \
    ((timer == 1) && ( \
      (channel == 1) || \
      (channel == 2) || \
      (channel == 3) || \
      (channel == 4) || \
      0 )) || \
    ((timer == 2) && ( \
      (channel == 1) || \
      (channel == 2) || \
      (channel == 3) || \
      (channel == 4) || \
      0 )) || \
    ((timer == 3) && ( \
      (channel == 1) || \
      (channel == 2) || \
      (channel == 3) || \
      (channel == 4) || \
      0 )) || \
    ((timer == 4) && ( \
      (channel == 1) || \
      (channel == 2) || \
      (channel == 3) || \
      (channel == 4) || \
      0 )) || \
    ((timer == 5) && ( \
      (channel == 1) || \
      (channel == 2) || \
      (channel == 3) || \
      (channel == 4) || \
      0 )) || \
    ((timer == 8) && ( \
      (channel == 1) || \
      (channel == 2) || \
      (channel == 3) || \
      (channel == 4) || \
      0 )) || \
    ((timer == 9) && ( \
      (channel == 1) || \
      (channel == 2) || \
      0 )) || \
    ((timer == 10) && ( \
      (channel == 1) || \
      0 )) || \
    ((timer == 11) && ( \
      (channel == 1) || \
      0 )) || \
    ((timer == 12) && ( \
      (channel == 1) || \
      (channel == 2) || \
      0 )) || \
    ((timer == 13) && ( \
      (channel == 1) || \
      0 )) || \
    ((timer == 14) && ( \
      (channel == 1) || \
      0 )) || \
  0 )

static constexpr inline IRQn_Type get_timer_irq(int timer) {
  return
#if (defined TIM5)
    (timer == 5) ? TIM5_IRQn :
#endif
#if (defined TIM8) and (defined TIM13)
    (timer == 8) ? TIM8_UP_TIM13_IRQn :
#endif
#if (defined TIM8) and (defined TIM13)
    (timer == 13) ? TIM8_UP_TIM13_IRQn :
#endif
#if (defined TIM7)
    (timer == 7) ? TIM7_IRQn :
#endif
#if (defined TIM14)
    (timer == 14) ? TIM8_TRG_COM_TIM14_IRQn :
#endif
#if (defined TIM4)
    (timer == 4) ? TIM4_IRQn :
#endif
#if (defined TIM12)
    (timer == 12) ? TIM8_BRK_TIM12_IRQn :
#endif
#if (defined TIM1) and (not defined TIM10)
    (timer == 1) ? TIM1_UP_IRQn :
#endif
#if (defined TIM1) and (defined TIM10)
    (timer == 1) ? TIM1_UP_TIM10_IRQn :
#endif
#if (defined TIM1) and (defined TIM10)
    (timer == 10) ? TIM1_UP_TIM10_IRQn :
#endif
#if (defined TIM11)
    (timer == 11) ? TIM1_TRG_COM_TIM11_IRQn :
#endif
#if (defined TIM3)
    (timer == 3) ? TIM3_IRQn :
#endif
#if (defined TIM9)
    (timer == 9) ? TIM1_BRK_TIM9_IRQn :
#endif
#if (defined TIM2)
    (timer == 2) ? TIM2_IRQn :
#endif
#if (defined TIM6)
    (timer == 6) ? TIM6_DAC_IRQn :
#endif
    UsageFault_IRQn;
}

