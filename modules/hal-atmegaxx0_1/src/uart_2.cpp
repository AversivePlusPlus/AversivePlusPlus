#include <hal/atmegaxx0_1/uart.hpp>

template<> void (*HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<2>::txc)(void) = 0;
template<> void (*HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<2>::rxc)(void) = 0;

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(USART2_RX_vect) {
  if(::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<2>::rxc) {
      ::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<2>::rxc();
    }
}

ISR(USART2_TX_vect) {
  if(::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<2>::txc) {
      ::HAL::ATMegaxx0_1::UART::UART_IRQ_Handlers<2>::txc();
    }
}
