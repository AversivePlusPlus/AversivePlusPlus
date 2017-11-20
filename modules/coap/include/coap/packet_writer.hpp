#ifndef PACKET_WRITER_HPP
#define PACKET_WRITER_HPP

#include "../ext/input_stream.hpp"
#include "packet_reader.hpp"

namespace coap {

class PacketWriter {
public:
  uint8_t* _buffer;
  const size_t _max_size;
  size_t _size;

public:
  PacketWriter(uint8_t* buffer, size_t max_size)
    : _buffer(buffer), _max_size(max_size), _size(0) {
  }
};

enum class PacketState {
  EMPTY,
  HEADER_FILLED,
  PAYLOAD_ADDED,
};

class PacketBuilder;
template<PacketState STATE> class StatePacketWriter;

class ErrorPacketWriter {
protected:
  uint8_t* _buffer;
  size_t& _size;
  const size_t _max_size;
  Error _err;
  uint16_t _option_delta;

protected:
  ErrorPacketWriter(PacketWriter& pack)
    : _buffer(pack._buffer), _size(pack._size), _max_size(pack._max_size),
      _err(Error::NONE), _option_delta(0) {
  }

public:
  inline Error getError(void) {
    return _err;
  }
};

template<>
class StatePacketWriter<PacketState::EMPTY> : public ErrorPacketWriter {
public:
  StatePacketWriter(PacketWriter& pack)
    : ErrorPacketWriter(pack) {
  }

  StatePacketWriter<PacketState::HEADER_FILLED>&
  buildHeader(const PacketReader& request,
              ResponseCode response_code);
  
  StatePacketWriter<PacketState::HEADER_FILLED>& 
  buildHeader(MessageType msg_type, 
              ResponseCode response_code, 
              uint16_t id, 
              const uint8_t* token, uint8_t token_length);
};

template<>
class StatePacketWriter<PacketState::HEADER_FILLED> : public ErrorPacketWriter {
public:
  StatePacketWriter<PacketState::HEADER_FILLED>&
  addOption(OptionNum num, const uint8_t* value, size_t length);

  StatePacketWriter<PacketState::HEADER_FILLED>&
  addOption(OptionNum num, uint16_t value);

  StatePacketWriter<PacketState::PAYLOAD_ADDED>&
  addPayload(const uint8_t* content, size_t length);

  template<class DerivedInputStream>
  StatePacketWriter<PacketState::PAYLOAD_ADDED>&
  addPayload(DerivedInputStream& stream) {
    if(_err != Error::NONE) {
      return *(StatePacketWriter<PacketState::PAYLOAD_ADDED>*)this;
    }

    uint8_t* cur = _buffer + _size;

    *cur = 0xFF;
    cur++;

    cur += stream.read(cur, _max_size - _size);

    _size = cur - _buffer;
    return *(StatePacketWriter<PacketState::PAYLOAD_ADDED>*)this;
  }
};

template<>
class StatePacketWriter<PacketState::PAYLOAD_ADDED> : public ErrorPacketWriter {
public:
  StatePacketWriter<PacketState::PAYLOAD_ADDED>&
  appendPayload(const uint8_t* content, size_t length);
};

using EmptyPacket = StatePacketWriter<PacketState::EMPTY>;


class PacketBuilder : private PacketWriter {
public:
  PacketBuilder(char* buffer, size_t max_size)
    : PacketWriter((uint8_t*)buffer, max_size) {
  }

  PacketBuilder(uint8_t* buffer, size_t max_size)
    : PacketWriter(buffer, max_size) {
  }

  uint8_t* getBuffer(void) const {
    return _buffer;
  }

  size_t getSize(void) const {
    return _size;
  }

  Error makeResponse(const PacketReader& request, ResponseCode code, ContentType content_type, const uint8_t* content, size_t content_size) {
    EmptyPacket pack = *this;
    pack
        .buildHeader(request, code)
        .addOption(OptionNum::CONTENT_FORMAT, (uint16_t)content_type)
        .addPayload(content, content_size)
        ;
    return pack.getError();
  }

  template<class DerivedInputStream>
  Error makeResponse(const PacketReader& request, ResponseCode code, ContentType content_type, DerivedInputStream& stream) {
    EmptyPacket pack = *this;
    pack
        .buildHeader(request, code)
        .addOption(OptionNum::CONTENT_FORMAT, (uint16_t)content_type)
        .addPayload(stream)
        ;
    return pack.getError();
  }

  Error makeResponse(const PacketReader& request, ResponseCode code) {
    EmptyPacket pack = *this;
    pack.buildHeader(request, code);
    return pack.getError();
  }
};

}

#endif//PACKET_WRITER_HPP
