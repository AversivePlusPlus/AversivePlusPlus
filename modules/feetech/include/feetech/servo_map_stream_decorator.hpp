#ifndef FEETECH_SERVO_MAP_STREAM_DECORATOR_HPP
#define FEETECH_SERVO_MAP_STREAM_DECORATOR_HPP

#include <feetech/bus_frame_stream_decorator.hpp>
#include <stream/io_stream.hpp>
#include <stream/random_access_stream.hpp>

namespace Feetech {

  template<u8 BUFFER_SIZE, typename Stream>
  class ServoMapStreamDecorator :
      public ::Stream::IOStream<ServoMapStreamDecorator<BUFFER_SIZE, Stream>>,
      public ::Stream::RandomAccessStream {
  private:
    BusFrameStreamDecorator<BUFFER_SIZE, Stream> _bfs;
    Stream& _stream;
    u8 _id;

  private:
    u16 readTimeout(u8* data, u16 length) {
      u16 len = 0;
      for(u32 i = 0 ; i < Protocol::TIMEOUT && len < length ; i++) {
          u16 rlen = _stream.readable();
          if(rlen) {
              _stream.read(data+len, rlen);
              len += rlen;
            }
        }
      return len;
    }

  public:
    ServoMapStreamDecorator(Stream& stream)
      : _bfs(stream), _stream(stream), _id(0xfe) {
    }

    inline void setServo(u8 id) {
      _id = id;
    }

    inline void putChar(u8 c) {
      _bfs.start(_id);
      _bfs.putChar(Protocol::INST_WRITE);
      _bfs.putChar(_cursor);
      _bfs.putChar(c);
      _bfs.end();
      move(1);

      u8 buff[6];
      readTimeout(buff, 6);
    }

    inline u16 write(u8* data, u16 length) {
      _bfs.start(_id);
      _bfs.putChar(Protocol::INST_WRITE);
      _bfs.putChar(_cursor);
      for(u16 i = 0 ; i < length ; i++) {
          _bfs.putChar(data[i]);
        }
      _bfs.end();

      u8 buff[6];
      if(readTimeout(buff, 6) != 6) {
          return 0;
        }

      move(length);
      return length;
    }

    inline u16 writable(void) {
      return BUFFER_SIZE-7;
    }

    inline u8 getChar(void) {
      _bfs.start(_id);
      _bfs.putChar(Protocol::INST_READ);
      _bfs.putChar(_cursor);
      _bfs.putChar(1);
      _bfs.end();

      u8 buff[7];

      if(readTimeout(buff, 7) != 7) {
          return 0;
        }

      move(1);
      return buff[5];
    }

    inline u16 read(u8* data, u16 length) {
      _bfs.start(_id);
      _bfs.putChar(Protocol::INST_READ);
      _bfs.putChar(_cursor);
      _bfs.putChar(length);
      _bfs.end();

      u8 buff[BUFFER_SIZE];
      u16 msg_len = length + 6;

      if(readTimeout(buff, msg_len) != msg_len) {
          return 0;
        }

      for(u16 i = 0 ; i < length ; i++) {
          data[i] = buff[i+5];
        }

      move(length);
      return length;
    }

    inline u16 readable(void) {
      return BUFFER_SIZE-6;
    }
  };

}

#endif//FEETECH_SERVO_MAP_STREAM_DECORATOR_HPP
