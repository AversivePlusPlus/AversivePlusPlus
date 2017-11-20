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
#ifndef HAL_STM32CUBEF4_GPIO_HPP
#define HAL_STM32CUBEF4_GPIO_HPP

#include <stm32f4xx_hal.h>
#include <stm32f4xx.h>

#include <hal/gpio_interface.hpp>

#include <hal/stm32cubef4/traits.hpp>

#include <base/compil.hpp>
#include <base/integer.hpp>
#include <hal/macros_define.hpp>

using namespace Aversive::Base;

namespace HAL {

  namespace STM32CubeF4 {

    //! \brief GPIO Driver Interface
    //! \param T : The type of a standard GPIO I/O Register
    /*!
     * This interface exists to show the developer what can be implemented.
     * But the developper may not implement everything, since not every mirocontroller has as much functionnalities.
     * If a microcontroller provides a service that does not fit this interface, please, contact the main developpers of this project.
     */
    struct GPIO : GPIO_DriverInterface {
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
        AVERSIVE_AVAILABLE_ELEMENT(PUSH_PULL);
        AVERSIVE_AVAILABLE_ELEMENT(OPEN_DRAIN);
      };

      //! \brief The GPIO Pin Pull Policy
      struct Pull : Parent::Pull {
        AVERSIVE_AVAILABLE_ELEMENT(UNDEFINED);
        AVERSIVE_AVAILABLE_ELEMENT(UP);
        AVERSIVE_AVAILABLE_ELEMENT(DOWN);
      };

      template<int PORT_ID, typename Settings>
      static void init(Private::PORT_Type<PORT_ID> port, const Settings& settings) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(port);
        Private::clk_enable(port);

        GPIO_InitTypeDef gpio_init;
        gpio_init.Pull = Private::cube_gpio_pull(settings.pull);
        gpio_init.Speed = GPIO_SPEED_LOW;
        gpio_init.Mode = Private::cube_gpio_mode(settings.mode, settings.output_mode);

        gpio_init.Pin = GPIO_PIN_All;
        HAL_GPIO_Init(gpio, &gpio_init);
      }

      template<int ID, typename Settings>
      static void init(Private::PIN_Type<ID> pin, const Settings& settings) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(Private::port(pin));
        Private::clk_enable(Private::port(pin));

        GPIO_InitTypeDef gpio_init;
        gpio_init.Pull = Private::cube_gpio_pull(settings.pull);
        gpio_init.Speed = GPIO_SPEED_LOW;
        gpio_init.Mode = Private::cube_gpio_mode(settings.mode, settings.output_mode);

        gpio_init.Pin = Private::cube_gpio_offset(Private::offset(pin));
        HAL_GPIO_Init(gpio, &gpio_init);
      }

      template<int PORT_ID>
      static typename Private::PORT_Type<PORT_ID>::ValueType getValue(Private::PORT_Type<PORT_ID> port) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(port);
        return gpio->IDR;
      }

      template<int ID>
      static bool getValue(Private::PIN_Type<ID> pin) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(Private::port(pin));
        uint32_t gpio_pin = Private::cube_gpio_offset(Private::offset(pin));
        return HAL_GPIO_ReadPin(gpio, gpio_pin) == GPIO_PIN_SET;
      }

      template<int PORT_ID, typename ValueType>
      static void setValue(Private::PORT_Type<PORT_ID> port, ValueType value) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(port);
        gpio->ODR = value;
      }

      template<int ID, typename ValueType>
      static void setValue(Private::PIN_Type<ID> pin, ValueType value) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(Private::port(pin));
        uint32_t gpio_pin = Private::cube_gpio_offset(Private::offset(pin));
        HAL_GPIO_WritePin(gpio, gpio_pin, value?GPIO_PIN_SET:GPIO_PIN_RESET);
      }

      template<int ID>
      static void toggle(Private::PIN_Type<ID> pin) {
        GPIO_TypeDef* gpio = Private::cube_gpio_port(Private::port(pin));
        uint32_t gpio_pin = Private::cube_gpio_offset(Private::offset(pin));
        HAL_GPIO_TogglePin(gpio, gpio_pin);
      }
    };

  }
}

#include <hal/macros_undef.hpp>

#endif//HAL_STM32CUBEF4_GPIO_HPP
