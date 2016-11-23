#ifndef FEETECH_BUS_FRAME_STREAM_DECORATOR_HPP
#define FEETECH_BUS_FRAME_STREAM_DECORATOR_HPP

#include <feetech/protocol.hpp>
#include <stream/output_stream.hpp>
#include <container/buffer.hpp>

namespace Feetech {

  template<u16 BUFFER_SIZE, typename Stream>
  class BusFrameStreamDecorator : ::Stream::OutputStream<BusFrameStreamDecorator<BUFFER_SIZE, Stream>> {
  private:
    Stream& _stream;
    Container::Buffer<BUFFER_SIZE, u8> _write_buffer;
    u8 _id;

  public:
    BusFrameStreamDecorator(Stream& stream)
      : _stream(stream), _id(0) {
    }

    inline void start(u8 id) {
      _id = id;
    }

    inline void end(void) {
      _stream.putChar(Protocol::START);
      _stream.putChar(Protocol::START);
      _stream.putChar(_id);
      u8 sum = _id;
      u8 s = _write_buffer.usedSpace()+1;
      _stream.putChar(s);
      sum += s;
      while(!_write_buffer.isEmpty()) {
          _stream.putChar(_write_buffer.head());
          sum += _write_buffer.head();
          _write_buffer.dequeue();
        }
      _stream.putChar((~sum)&0xFF);
    }

    inline void putChar(u8 c) {
      _write_buffer.enqueue(c);
    }

    inline u16 write(u8 *data, u16 length) {

      for(u16 i = 0 ; i < length ; i++) {
          putChar(data[i]);
        }

      return length;
    }

    inline u16 writable(void) {
      return BUFFER_SIZE - _write_buffer.usedSpace();
    }
  };

}

#endif//FEETECH_BUS_FRAME_STREAM_DECORATOR_HPP
