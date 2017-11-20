#include<stream/hal/uart_stream.hpp>

struct Settings : Stream::HAL::DefaultUARTStreamSettings {
  static constexpr auto& uart = HAL::SERIAL_USART3;
  static constexpr auto tx = HAL::C10;
  static constexpr auto rx = HAL::C11;
};

int main(int, char**) {
  Stream::HAL::FormattedUARTStream<Settings> fus;

  if(fus.writable()) {
      fus << "WRITABLE\n";
    }

  if(fus.readable()) {
      fus << "READABLE\n";
    }

  while(1) {
      s16 test = 0;
      fus << "Value ? \n";
      fus >> test;
      fus << "You wrote " << test << "\n";
  }

  return 0;
}
