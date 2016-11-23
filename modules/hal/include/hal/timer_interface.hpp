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
#ifndef HAL_TIMER_INTERFACE_HPP
#define HAL_TIMER_INTERFACE_HPP

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {
  
  //! \brief TIMER Driver Interface
  struct TIMER_DriverInterface {
  public:
    //! \brief The TIMER Counter Period
    struct Period {
      using Type = u32;
    };

    template<typename PeriodType>
    struct GenericSettings {
      PeriodType period; // in us
    };
    
    using Settings = GenericSettings<
      typename Period::Type
      >;

    //! \brief Configure the timer with the timer counter disabled (counter reset to 0)
    template<typename TIMERType, typename Settings>
    static void init(TIMERType timer, const Settings&) AVERSIVE_UNAVAILABLE;

    //! \brief Set the interruption handler
    template<typename TIMERType, typename IRQ_Handler>
    static void setOverflowHandler(TIMERType timer, IRQ_Handler handler) AVERSIVE_UNAVAILABLE;

    //! \brief Enables the timer counter incrementation
    template<typename TIMERType>
    static void start(TIMERType timer) AVERSIVE_UNAVAILABLE;

    //! \brief Disables the timer counter incrementation and reset the counter to 0
    template<typename TIMERType>
    static void stop(TIMERType timer) AVERSIVE_UNAVAILABLE;

    //! \brief Disables the timer counter incrementation
    template<typename TIMERType>
    static void pause(TIMERType timer) AVERSIVE_UNAVAILABLE;
  };

}

#include <hal/macros_undef.hpp>

#endif//HAL_TIMER_INTERFACE_HPP
