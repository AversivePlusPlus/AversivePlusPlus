#include <device/hal/encoder.hpp>
#include <device/hal/input_digital_pin.hpp>
#include <device/hal/output_digital_pin.hpp>
#include <device/hal/pwm_pin.hpp>

struct MyPWMSettings : Device::HAL::DefaultPWMPinSettings, Device::HAL::DefaultPWMTimerSettings {
  static constexpr auto& timer = HAL::TIMER1;
  static constexpr auto pwm = HAL::TIMER1_CH0;
  static constexpr auto pin = HAL::A0;
};

struct Dev {
  Device::HAL::PWMTimer<MyPWMSettings> timer;
  Device::HAL::PWMPin<MyPWMSettings> pwm1;

  Dev() {
    timer.start();
  }
};

int main(int, char**) {
  Dev dev;

  dev.pwm1.setValue(10);

  while(1);

  return 0;
}
