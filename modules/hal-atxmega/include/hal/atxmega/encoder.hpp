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
#ifndef HAL_ATXMEGA_ENCODER_HPP
#define HAL_ATXMEGA_ENCODER_HPP

#include <hal/encoder_interface.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {
  
  namespace ATxmega {

    //! \brief ENCODER Driver
    struct ENCODER : public ENCODER_DriverInterface {
      
      //! \brief The Encoder Mode
      struct Mode : Parent::Mode {
        AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_UNAVAILABLE_ELEMENT(CHANNEL1_COUNT);
        AVERSIVE_UNAVAILABLE_ELEMENT(CHANNEL2_COUNT);
        AVERSIVE_UNAVAILABLE_ELEMENT(BOTH_COUNT);
      };

      //! \brief The Encoder Polarity
      struct Polarity : Parent::Polarity {
        AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_UNAVAILABLE_ELEMENT(RISING);
        AVERSIVE_UNAVAILABLE_ELEMENT(FALLING);
        AVERSIVE_UNAVAILABLE_ELEMENT(BOTH);
      };

      //! \brief Configure the Timer in Encoder Mode
      //! \param timer : The TIMER module
      //! \param c1 : First encoder channel pin
      //! \param c2 : Second encoder channel pin
      //! \param settings : The Encoder Settings
      template<typename TIMERType, typename C1PinType, typename C2PinType, typename Settings>
      static void init(TIMERType timer, C1PinType c1, C2PinType c2, const Settings& settings) AVERSIVE_UNAVAILABLE;

      //! \brief Get the counter of the encoder
      template<typename TIMERType>
      static typename TIMERType::CounterType getCounter(TIMERType timer) AVERSIVE_UNAVAILABLE;

      //! \brief Set the counter of the encoder
      template<typename TIMERType>
      static void setCounter(TIMERType timer, typename TIMERType::CounterType value) AVERSIVE_UNAVAILABLE;
    };

  }

}

#include <hal/macros_undef.hpp>

#endif//HAL_ATXMEGA_ENCODER_HPP
