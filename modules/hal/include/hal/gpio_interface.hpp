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
#ifndef HAL_GPIO_INTERFACE_HPP
#define HAL_GPIO_INTERFACE_HPP

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

namespace HAL {

  //! \brief GPIO Driver Interface
  //! \param T : The type of a standard GPIO I/O Register
  /*!
   * This interface exists to show the developer what can be implemented.
   * But the developper may not implement everything, since not every mirocontroller has as much functionnalities.
   * If a microcontroller provides a service that does not fit this interface, please, contact the main developpers of this project.
   */
  struct GPIO_DriverInterface {
      
    //! \brief The GPIO Pin Mode
    struct Mode {
      enum class Type : u8 { UNDEFINED = 0, INPUT, OUTPUT };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(INPUT);
      AVERSIVE_UNAVAILABLE_ELEMENT(OUTPUT);
    };
    
    //! \brief The GPIO Pin Output Mode
    struct OutputMode {
      enum class Type : u8 { UNDEFINED = 0, PUSH_PULL, OPEN_DRAIN };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(PUSH_PULL);
      AVERSIVE_UNAVAILABLE_ELEMENT(OPEN_DRAIN);
    };

    //! \brief The GPIO Pin Pull Policy
    struct Pull {
      enum class Type : u8 { UNDEFINED = 0, UP, DOWN };
      AVERSIVE_UNAVAILABLE_ELEMENT(UNDEFINED);
      AVERSIVE_UNAVAILABLE_ELEMENT(UP);
      AVERSIVE_UNAVAILABLE_ELEMENT(DOWN);
    };

    //! \brief GPIO Generic Settings
    template <typename ModeType, typename OutputModeType, typename PullType>
    struct GenericSettings {
      ModeType mode;
      OutputModeType output_mode;
      PullType pull;
    };
    
    //! \brief GPIO Settings
    using Settings = GenericSettings<
      typename Mode::Type,
      typename OutputMode::Type,
      typename Pull::Type
      >;

    //! \brief Configure a GPIO Pin or Port
    //! \param gpio : Can be either a Pin or an entire Port
    //! \param settings : GPIO settings
    template<typename GPIOType, typename Settings>
    static void init(GPIOType gpio, const Settings& settings) AVERSIVE_UNAVAILABLE;

    //! \brief Get the value of a pin or a port
    template<typename GPIOType>
    static typename GPIOType::ValueType getValue(GPIOType gpio) AVERSIVE_UNAVAILABLE;

    //! \brief Set the value of a pin or a port
    template<typename GPIOType>
    static void setValue(GPIOType  gpio, typename GPIOType::ValueType value) AVERSIVE_UNAVAILABLE;

    //! \brief Toggle the value of a pin
    template<typename GPIOType>
    static void toggle(GPIOType gpio) AVERSIVE_UNAVAILABLE;
  };
    
}

#include <hal/macros_undef.hpp>

#endif//HAL_GPIO_INTERFACE_HPP
