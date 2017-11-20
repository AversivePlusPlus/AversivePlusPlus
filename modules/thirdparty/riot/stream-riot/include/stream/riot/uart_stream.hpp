#ifndef UART_STREAM_HPP
#define UART_STREAM_HPP

#include <periph/uart.h>

#include <stream/input_stream.hpp>
#include <stream/output_stream.hpp>
#include <container/simple/buffer.hpp>

namespace RIOT {

using namespace Aversive::Base;

template<unsigned int INPUT_BUFFER_SIZE = 128>
class UARTStream :
    public Aversive::Stream::OutputStream<char, unsigned int>,
    public Aversive::Stream::InputStream<char, unsigned int> {

private:
  const uart_t _uart_id;
  Aversive::Container::Simple::Buffer<char, INPUT_BUFFER_SIZE> _input;

public:
  inline UARTStream(uart_t uart_id, u32 baudrate)
    : _uart_id(uart_id) {
    uart_init(_uart_id, baudrate, [](void* t, uint8_t data){ ((UARTStream*)t)->_input.enqueue(data); }, (void*)this);
  }

  inline ~UARTStream(void) {
    uart_init(_uart_id, 0, 0, (void*)0);
  }

  inline void put(char c) {
    uart_write(_uart_id, &c, 1);
  }

  inline unsigned int write(const char* data, unsigned int length) {
    uart_write(_uart_id, (const uint8_t*)data, length);
    return length;
  }

  inline unsigned int writable(void) {
    return -1;
  }

  inline char get(void) {
    char ret = _input.head();
    _input.dequeue();
    return ret;
  }

  inline unsigned int read(char* data, unsigned int length) {
    for(unsigned int i = 0 ; i < length ; i++) {
      data[i] = _input.head();
      _input.dequeue();
    }
    return length;
  }

  inline unsigned int readable(void) {
    return _input.size();
  }
};

}

#endif//UART_STREAM_HPP
