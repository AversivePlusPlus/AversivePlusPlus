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
#ifndef HAL_ATXMEGA_GPIO_HPP
#define HAL_ATXMEGA_GPIO_HPP

#include <base/integer.hpp>
#include <hal/atxmega/traits.hpp>
#include <hal/gpio_interface.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {

  namespace ATxmega {

    //! \brief GPIO Driver
    struct GPIO : public GPIO_DriverInterface {
      using Parent = GPIO_DriverInterface;
      
      //! \brief The GPIO Pin Mode
      struct Mode : Parent::Mode {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(INPUT);
        AVERSIVE_AVAILABLE_ELEMENT(OUTPUT);
      };

      //! \brief The GPIO Pin Output Mode
      struct OutputMode : Parent::OutputMode {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_UNAVAILABLE_ELEMENT(PUSH_PULL);
        AVERSIVE_UNAVAILABLE_ELEMENT(OPEN_DRAIN);
      };

      //! \brief The GPIO Pin Pull Policy
      struct Pull : Parent::Pull {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_UNAVAILABLE_ELEMENT(UP);
        AVERSIVE_UNAVAILABLE_ELEMENT(DOWN);
      };

      //! \brief Configure a GPIO Pin
      //! \param gpio : Pin
      //! \param settings : GPIO settings
      template<int ID, typename Settings>
      static void init(Private::HAL_PIN<ID> pin, const Settings& settings) {
        PORT_t& AVR_PORT = Private::avr_io_port(Private::port(pin));
        const u8 offset = Private::offset(pin);

        if(settings.mode == Mode::OUTPUT) AVR_PORT.DIRSET = (1<<offset);
        else AVR_PORT.DIRCLR = (1<<offset);
      }

      //! \brief Get the value of a pin or a port
      template<int ID>
      static bool getValue(Private::HAL_PIN<ID> pin) {
        PORT_t& AVR_PORT = Private::avr_io_port(Private::port(pin));
        const u8 offset = Private::offset(pin);
        return AVR_PORT.IN & (1<<offset);
      }

      //! \brief Set the value of a pin
      template<int ID>
      static void setValue(Private::HAL_PIN<ID> pin, bool value) {
        PORT_t& AVR_PORT = Private::avr_io_port(Private::port(pin));
        const u8 offset = Private::offset(pin);

        if(value) AVR_PORT.OUTSET = (1<<offset);
        else AVR_PORT.OUTCLR = (1<<offset);
      }

      //! \brief Toggle the value of a pin
      template<int ID>
      static void toggle(Private::HAL_PIN<ID> pin) {
        PORT_t& AVR_PORT = Private::avr_io_port(Private::port(pin));
        const u8 offset = Private::offset(pin);
        AVR_PORT.OUTTGL = (1<<offset);
      }
    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_ATXMEGA_GPIO_HPP
