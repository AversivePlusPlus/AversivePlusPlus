#include<hal/atxmega/gpio.hpp>

using namespace HAL::ATxmega;

constexpr auto& LED1 = A0;
constexpr auto& LED2 = A1;

int main(int, char**) {
  {
    GPIO::Settings settings;
    settings.mode = GPIO::Mode::OUTPUT;
    settings.output_mode = GPIO::OutputMode::UNDEFINED;
    settings.pull = GPIO::Pull::UNDEFINED;

    GPIO::init(LED1, settings);
    GPIO::init(LED2, settings);
  }

  GPIO::setValue(LED1, true);
  GPIO::setValue(LED2, true);

  while(1) {
    }

  return 0;
}
