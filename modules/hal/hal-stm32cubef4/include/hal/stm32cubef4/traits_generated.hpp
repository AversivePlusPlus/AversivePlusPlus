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
#define MACRO_APPLY_ARGS(macro, args...) macro(args)


#ifdef GPIOA
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOA_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOA_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOB
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOB_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOB_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOC
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOC_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOC_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOD
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOD_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOD_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOE
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOE_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOE_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOF
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOF_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOF_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOG
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOG_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOG_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOH
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOH_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOH_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOI
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOI_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOI_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOJ
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOJ_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOJ_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOK
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOK_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOK_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOL
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOL_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOL_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOM
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOM_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOM_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPION
  #define AVERSIVE_HAL_STM32CUBEF4_GPION_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPION_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOO
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOO_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOO_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOP
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOP_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOP_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOQ
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOQ_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOQ_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOR
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOR_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOR_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOS
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOS_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOS_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOT
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOT_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOT_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOU
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOU_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOU_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOV
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOV_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOV_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOW
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOW_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOW_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOX
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOX_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOX_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOY
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOY_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOY_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef GPIOZ
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOZ_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_GPIOZ_EXISTS(txt_if, txt_else) txt_else
#endif


#define AVERSIVE_APPLY_PORTS(macro, args...) \
  macro(A, 0, args) \
  macro(B, 1, args) \
  macro(C, 2, args) \
  macro(D, 3, args) \
  macro(E, 4, args) \
  macro(F, 5, args) \
  macro(G, 6, args) \
  macro(H, 7, args) \
  macro(I, 8, args) \
  macro(J, 9, args) \
  macro(K, 10, args) \
  macro(L, 11, args) \
  macro(M, 12, args) \
  macro(N, 13, args) \
  macro(O, 14, args) \
  macro(P, 15, args) \
  macro(Q, 16, args) \
  macro(R, 17, args) \
  macro(S, 18, args) \
  macro(T, 19, args) \
  macro(U, 20, args) \
  macro(V, 21, args) \
  macro(W, 22, args) \
  macro(X, 23, args) \
  macro(Y, 24, args) \
  macro(Z, 25, args) \

#define AVERSIVE_APPLY_PINS(macro, args...) \
  macro(0, args) \
  macro(1, args) \
  macro(2, args) \
  macro(3, args) \
  macro(4, args) \
  macro(5, args) \
  macro(6, args) \
  macro(7, args) \
  macro(8, args) \
  macro(9, args) \
  macro(10, args) \
  macro(11, args) \
  macro(12, args) \
  macro(13, args) \
  macro(14, args) \
  macro(15, args) \


#ifdef TIM0
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM1
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM2
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM3
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM4
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM5
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM6
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM7
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM8
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM9
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM10
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM11
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM12
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM13
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM14
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM15
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM16
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM17
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM18
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_EXISTS(txt_if, txt_else) txt_else
#endif

#ifdef TIM19
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_EXISTS(txt_if, txt_else) txt_else
#endif


#if AVERSVE_IS_TIMER_CHANNEL(0, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(0, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(0, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(0, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(0, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(0, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER0_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(1, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(1, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(1, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(1, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(1, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(1, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER1_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(2, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(2, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(2, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(2, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(2, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(2, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER2_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(3, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(3, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(3, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(3, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(3, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(3, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER3_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(4, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(4, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(4, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(4, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(4, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(4, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER4_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(5, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(5, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(5, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(5, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(5, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(5, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER5_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(6, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(6, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(6, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(6, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(6, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(6, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER6_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(7, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(7, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(7, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(7, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(7, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(7, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER7_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(8, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(8, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(8, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(8, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(8, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(8, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER8_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(9, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(9, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(9, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(9, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(9, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(9, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER9_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(10, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(10, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(10, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(10, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(10, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(10, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER10_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(11, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(11, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(11, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(11, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(11, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(11, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER11_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(12, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(12, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(12, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(12, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(12, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(12, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER12_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(13, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(13, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(13, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(13, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(13, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(13, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER13_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(14, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(14, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(14, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(14, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(14, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(14, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER14_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(15, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(15, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(15, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(15, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(15, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(15, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER15_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(16, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(16, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(16, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(16, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(16, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(16, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER16_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(17, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(17, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(17, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(17, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(17, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(17, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER17_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(18, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(18, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(18, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(18, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(18, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(18, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER18_CH5_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(19, 0)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH0_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(19, 1)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH1_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(19, 2)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH2_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(19, 3)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH3_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(19, 4)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH4_EXISTS(txt_if, txt_else) txt_else
#endif

#if AVERSVE_IS_TIMER_CHANNEL(19, 5)
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_HAL_STM32CUBEF4_TIMER19_CH5_EXISTS(txt_if, txt_else) txt_else
#endif


#define AVERSIVE_APPLY_TIMERS(macro, args...) \
  macro(0, args) \
  macro(1, args) \
  macro(2, args) \
  macro(3, args) \
  macro(4, args) \
  macro(5, args) \
  macro(6, args) \
  macro(7, args) \
  macro(8, args) \
  macro(9, args) \
  macro(10, args) \
  macro(11, args) \
  macro(12, args) \
  macro(13, args) \
  macro(14, args) \
  macro(15, args) \
  macro(16, args) \
  macro(17, args) \
  macro(18, args) \
  macro(19, args) \

#define AVERSIVE_APPLY_CHANNELS(macro, args...) \
  macro(0, args) \
  macro(1, args) \
  macro(2, args) \
  macro(3, args) \
  macro(4, args) \
  macro(5, args) \


#if defined UART0
  #define AVERSIVE_CUBE_UART0_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART0_EXISTS(txt_if, txt_else) txt_if
#elif defined USART0
  #define AVERSIVE_CUBE_UART0_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART0_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART0_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART0_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART1
  #define AVERSIVE_CUBE_UART1_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART1_EXISTS(txt_if, txt_else) txt_if
#elif defined USART1
  #define AVERSIVE_CUBE_UART1_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART1_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART1_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART1_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART2
  #define AVERSIVE_CUBE_UART2_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART2_EXISTS(txt_if, txt_else) txt_if
#elif defined USART2
  #define AVERSIVE_CUBE_UART2_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART2_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART2_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART2_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART3
  #define AVERSIVE_CUBE_UART3_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART3_EXISTS(txt_if, txt_else) txt_if
#elif defined USART3
  #define AVERSIVE_CUBE_UART3_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART3_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART3_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART3_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART4
  #define AVERSIVE_CUBE_UART4_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART4_EXISTS(txt_if, txt_else) txt_if
#elif defined USART4
  #define AVERSIVE_CUBE_UART4_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART4_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART4_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART4_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART5
  #define AVERSIVE_CUBE_UART5_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART5_EXISTS(txt_if, txt_else) txt_if
#elif defined USART5
  #define AVERSIVE_CUBE_UART5_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART5_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART5_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART5_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART6
  #define AVERSIVE_CUBE_UART6_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART6_EXISTS(txt_if, txt_else) txt_if
#elif defined USART6
  #define AVERSIVE_CUBE_UART6_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART6_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART6_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART6_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART7
  #define AVERSIVE_CUBE_UART7_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART7_EXISTS(txt_if, txt_else) txt_if
#elif defined USART7
  #define AVERSIVE_CUBE_UART7_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART7_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART7_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART7_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART8
  #define AVERSIVE_CUBE_UART8_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART8_EXISTS(txt_if, txt_else) txt_if
#elif defined USART8
  #define AVERSIVE_CUBE_UART8_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART8_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART8_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART8_EXISTS(txt_if, txt_else) txt_else
#endif

#if defined UART9
  #define AVERSIVE_CUBE_UART9_TYPE UART
  #define AVERSIVE_HAL_STM32CUBEF4_UART9_EXISTS(txt_if, txt_else) txt_if
#elif defined USART9
  #define AVERSIVE_CUBE_UART9_TYPE USART
  #define AVERSIVE_HAL_STM32CUBEF4_UART9_EXISTS(txt_if, txt_else) txt_if
#else
  #define AVERSIVE_CUBE_UART9_TYPE UNDEFINED
  #define AVERSIVE_HAL_STM32CUBEF4_UART9_EXISTS(txt_if, txt_else) txt_else
#endif


#define AVERSIVE_APPLY_UARTS(macro, args...) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART0_TYPE, 0, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART1_TYPE, 1, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART2_TYPE, 2, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART3_TYPE, 3, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART4_TYPE, 4, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART5_TYPE, 5, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART6_TYPE, 6, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART7_TYPE, 7, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART8_TYPE, 8, args) \
  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART9_TYPE, 9, args) \


