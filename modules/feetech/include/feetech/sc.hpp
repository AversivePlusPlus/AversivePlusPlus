#ifndef FEETECH_SC_HPP
#define FEETECH_SC_HPP

#include <feetech/servo_map_stream_decorator.hpp>

namespace Feetech {

  template<typename Stream>
  class SC {
  private:
    ServoMapStreamDecorator<16, Stream> _stream;

    template<typename T>
    inline u8* ptr(T& v) {
      return ((u8*)(&v));
    }

    u16 network2host(u16 val) {
      u16 ret;
      ptr(ret)[0] = ptr(val)[1];
      ptr(ret)[1] = ptr(val)[0];
      return ret;
    }

  public:
    inline SC(Stream& stream)
      : _stream(stream) {
    }

    inline bool ping(u8 id) {
      if(id == 0) {
          return false;
        }
      _stream.setServo(id);
      _stream.seek(Protocol::P_ID);
      return _stream.getChar() == id;
    }

    inline void enableTorque(u8 id) {
      _stream.setServo(id);
      _stream.seek(Protocol::P_TORQUE_ENABLE);
      _stream.putChar(1);
    }

    inline void disableTorque(u8 id) {
      _stream.setServo(id);
      _stream.seek(Protocol::P_TORQUE_ENABLE);
      _stream.putChar(0);
    }

    inline bool isTorqueEnabled(u8 id) {
      u8 ret = 0;

      _stream.setServo(id);
      _stream.seek(Protocol::P_TORQUE_ENABLE);
      _stream.read(ptr(ret), sizeof(ret));

      return ret;
    }


    inline void setPosition(u8 id, u16 pos) {
      u16 npos = network2host(pos);

      _stream.setServo(id);
      _stream.seek(Protocol::P_GOAL_POSITION);
      _stream.write(ptr(npos), sizeof(npos));
    }

    inline u16 getPosition(u8 id) {
      u16 ret = 0;

      _stream.setServo(id);
      _stream.seek(Protocol::P_PRESENT_POSITION);
      _stream.read(ptr(ret), sizeof(ret));

      return network2host(ret);
    }

    inline void setId(u8 id, u8 new_id) {
      _stream.setServo(id);

      _stream.seek(Protocol::P_LOCK);
      _stream.putChar(0);

      _stream.seek(Protocol::P_ID);
      _stream.putChar(new_id);

      _stream.seek(Protocol::P_LOCK);
      _stream.putChar(1);
    }

    inline s16 getLoad(u8 id) {
      u16 ret = 0;

      _stream.setServo(id);
      _stream.seek(Protocol::P_PRESENT_LOAD);
      _stream.read(ptr(ret), sizeof(ret));

      return (s16)network2host(ret);
    }

    inline s16 getSpeed(u8 id) {
      u16 ret = 0;

      _stream.setServo(id);
      _stream.seek(Protocol::P_PRESENT_SPEED);
      _stream.read(ptr(ret), sizeof(ret));

      return (s16)network2host(ret);
    }

  };

}

#endif//FEETECH_SC_HPP
