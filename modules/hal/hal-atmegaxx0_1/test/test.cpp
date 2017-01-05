#include<hal/atmegaxx0_1/uart.hpp>
#include<hal/atmegaxx0_1/gpio.hpp>
#include<hal/atmegaxx0_1/timer.hpp>
#include<hal/atmegaxx0_1/pwm.hpp>
#include<hal/atmegaxx0_1/encoder.hpp>

using namespace HAL::ATMegaxx0_1;

int main(int, char**) {
  {
    GPIO::Settings settings;
    settings.mode = GPIO::Mode::OUTPUT;
    GPIO::init(B7, settings);
  }

  {
    UART::Settings settings;
    settings.baudrate = 9600;
    settings.parity = UART::Parity::NONE;
    settings.stop_bit = UART::StopBit::ONE_BIT;
    settings.word_size = 8;
    UART::init(UART0, E1, E0, settings);
  }

  while(1) {
      UART::putChar(UART0, UART::getChar(UART0)+1);
      GPIO::setValue(B7, true);
    }

  return 0;
}
