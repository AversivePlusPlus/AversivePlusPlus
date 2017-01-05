#include<hal/stm32cubef4/uart.hpp>
#include<hal/stm32cubef4/gpio.hpp>
#include<hal/stm32cubef4/timer.hpp>
#include<hal/stm32cubef4/pwm.hpp>
#include<hal/stm32cubef4/encoder.hpp>

#include<stm32f4xx.h>

using namespace HAL::STM32CubeF4;

constexpr auto& MY_UART = SERIAL_USART3;
constexpr auto& MY_TX = C10;
constexpr auto& MY_RX = C11;

constexpr auto& MY_TIMER = TIMER8;

constexpr auto& PWM_TIMER = TIMER4;
constexpr auto& PWM_CHANNEL = TIMER4_CH2;
constexpr auto& PWM_LED = D13;

constexpr auto& LED1 = D12;
constexpr auto& LED2 = D13;
constexpr auto& LED3 = D14;
constexpr auto& LED4 = D15;

constexpr auto& ENCODER_TIMER = TIMER3;
constexpr auto& ENCODER_CHA = C6;
constexpr auto& ENCODER_CHB = C7;

int main(int, char**) {

  {
    UART::Settings settings;
    settings.baudrate = 9600;
    settings.parity = UART::Parity::NONE;
    settings.stop_bit = UART::StopBit::ONE_BIT;
    settings.word_size = 8;
    settings.flow_control = UART::FlowControl::NONE;

    UART::init(MY_UART,MY_TX,MY_RX, settings);
  }

  {
    GPIO::Settings settings;
    settings.mode = GPIO::Mode::OUTPUT;
    settings.output_mode = GPIO::OutputMode::PUSH_PULL;
    settings.pull = GPIO::Pull::DOWN;

    GPIO::init(LED1, settings);
    GPIO::init(LED2, settings);
    GPIO::init(LED3, settings);
    GPIO::init(LED4, settings);
  }

  {
    TIMER::Settings settings;
    settings.period = 1000000;

    TIMER::init(MY_TIMER, settings);
    TIMER::start(MY_TIMER);

    TIMER::init(PWM_TIMER, settings);
    TIMER::start(PWM_TIMER);
  }

  {
    PWM::Settings settings;
    settings.polarity = PWM::Polarity::HIGH;
    PWM::init(PWM_CHANNEL, PWM_LED, settings);
    PWM::setPulseWidth(PWM_CHANNEL, 10);
  }

  {
    ENCODER::Settings settings;
    settings.mode = ENCODER::Mode::BOTH_COUNT;
    settings.channel1.polarity = ENCODER::Polarity::BOTH;
    settings.channel2.polarity = ENCODER::Polarity::BOTH;
    ENCODER::init(ENCODER_TIMER, ENCODER_CHA, ENCODER_CHB, settings);
  }

  #define MSG "hello world!\r\n"
  UART::write(MY_UART, (u8*)MSG, sizeof(MSG));
  GPIO::setValue(LED1, true);

  UART::setHandler(MY_UART, UART::Event::RX_COMPLETE, []() {
      UART::putChar(MY_UART, UART::getChar(MY_UART));
      GPIO::toggle(LED1);
    });

  TIMER::setOverflowHandler(MY_TIMER, [](){
      GPIO::toggle(LED3);
    });

  if(TIMER::_getPeriod(1000000) != 65306) {
      GPIO::setValue(LED2, true);
    }

  while(1) {
      if(ENCODER::getCounter(ENCODER_TIMER) > 1000) {
          GPIO::setValue(LED4, true);
        }
      else {
          GPIO::setValue(LED4, false);
        }
    }

  return 0;
}
