#include <hal/atmegaxx0_1/uart.hpp>

template<> void (*HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<1>::txc)(void) = 0;
template<> void (*HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<1>::rxc)(void) = 0;

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART1_RX_vect) {
  if(::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<1>::rxc) {
      ::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<1>::rxc();
    }
}

ISR(USART1_TX_vect) {
  if(::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<1>::txc) {
      ::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<1>::txc();
    }
}
