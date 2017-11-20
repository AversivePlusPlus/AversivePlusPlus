#ifndef FEETECH_SC_HPP
#define FEETECH_SC_HPP

#include <feetech/servo.hpp>

namespace Aversive {
namespace Feetech {

  template<typename _Stream>
  class SC {
  public:
    using Stream = _Stream;

  private:
    Stream& _stream;

  private:
    using MyServo = Servo<_Stream>;

  public:
    inline SC(Stream& stream)
      : _stream(stream) {
    }

    inline bool ping(u8 id) {
      return MyServo(_stream, id).ping();
    }

    inline void enableTorque(u8 id) {
      MyServo(_stream, id).enableTorque();
    }

    inline void disableTorque(u8 id) {
      MyServo(_stream, id).disableTorque();
    }

    inline bool isTorqueEnabled(u8 id) {
      return MyServo(_stream, id).isTorqueEnabled();
    }

    inline void setPosition(u8 id, u16 pos) {
      MyServo(_stream, id).setPosition(pos);
    }

    inline u16 getPosition(u8 id) {
      return MyServo(_stream, id).getPosition();
    }

    inline void setId(u8 id, u8 new_id) {
      MyServo(_stream, id).setId(new_id);
    }

    inline s16 getLoad(u8 id) {
      return MyServo(_stream, id).getLoad();
    }

    inline s16 getSpeed(u8 id) {
      return MyServo(_stream, id).getSpeed();
    }
  };

}
}

#endif//FEETECH_SC_HPP
