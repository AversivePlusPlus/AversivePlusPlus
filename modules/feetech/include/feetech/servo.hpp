#ifndef FEETECH_SERVO_HPP
#define FEETECH_SERVO_HPP

#include <stream/input_stream.hpp>
#include <stream/output_stream.hpp>
#include <stream/random_access_stream.hpp>

#include <feetech/packet_writer.hpp>
#include <feetech/packet_reader.hpp>

namespace Aversive {
namespace Feetech {

template<typename _Stream>
class Servo {
private:
  using Stream = _Stream;

private:
  Stream& _stream;
  u8 _id;

private:
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
  Servo(Stream& stream, u8 id)
    : _stream(stream), _id(id) {
  }

  inline bool ping(void) {
    constexpr unsigned int size = 6;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.ping(_id);
    _stream.write(pw.data(), pw.size());

    constexpr unsigned int esize = AckPacketReader::expected();
    if(_stream.read(buffer, esize) == esize) {
      AckPacketReader pr(buffer, esize);
      return pr.valid() && pr.id() == _id;
    }
    return false;
  }

  inline void enableTorque(void) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.write(_id, Protocol::P_TORQUE_ENABLE, 1);
    _stream.write(pw.data(), pw.size());

    _stream.read(buffer, AckPacketReader::expected());
  }

  inline void disableTorque(void) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.write(_id, Protocol::P_TORQUE_ENABLE, 0);
    _stream.write(pw.data(), pw.size());

    _stream.read(buffer, AckPacketReader::expected());
  }

  inline bool isTorqueEnabled(void) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.read(_id, Protocol::P_TORQUE_ENABLE, 1);
    _stream.write(pw.data(), pw.size());

    constexpr unsigned int esize = ResponsePacketReader::expected(1);
    if(_stream.read(buffer, esize) == esize) {
      ResponsePacketReader pr(buffer, esize);
      return pr.valid() && pr.id() == _id && pr.data()[0] == 1;
    }
    return false;
  }

  inline void setPosition(u16 pos) {
    constexpr unsigned int size = 9;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.write(_id, Protocol::P_GOAL_POSITION, pos);
    _stream.write(pw.data(), pw.size());

    _stream.read(buffer, AckPacketReader::expected());
  }

  inline u16 getPosition(void) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.read(_id, Protocol::P_PRESENT_POSITION, 2);
    _stream.write(pw.data(), pw.size());

    constexpr unsigned int esize = ResponsePacketReader::expected(2);
    if(_stream.read(buffer, esize) == esize) {
      ResponsePacketReader pr(buffer, esize);
      if(pr.valid() && pr.id() == _id && pr.size() == 2) {
        return network2host(*(u16*)pr.data());
      }
    }
    return 0xFFFF;
  }

  inline void setId(u8 id) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.write(_id, Protocol::P_ID, id);
    _stream.write(pw.data(), pw.size());

    _stream.read(buffer, AckPacketReader::expected());
    _id = id;
  }

  inline s16 getLoad(void) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.read(_id, Protocol::P_PRESENT_LOAD, 2);
    _stream.write(pw.data(), pw.size());

    constexpr unsigned int esize = ResponsePacketReader::expected(2);
    if(_stream.read(buffer, esize) == esize) {
      ResponsePacketReader pr(buffer, esize);
      if(pr.valid() && pr.id() == _id && pr.size() == 2) {
        return network2host(*(u16*)pr.data());
      }
    }
    return 0xFFFF;
  }

  inline s16 getSpeed(void) {
    constexpr unsigned int size = 8;
    char buffer[size];
    PacketWriter pw(buffer, size);
    pw.read(_id, Protocol::P_PRESENT_SPEED, 2);
    _stream.write(pw.data(), pw.size());

    constexpr unsigned int esize = ResponsePacketReader::expected(2);
    if(_stream.read(buffer, esize) == esize) {
      ResponsePacketReader pr(buffer, esize);
      if(pr.valid() && pr.id() == _id && pr.size() == 2) {
        return network2host(*(u16*)pr.data());
      }
    }
    return 0xFFFF;
  }
};

}
}

#endif//FEETECH_SERVO_HPP
