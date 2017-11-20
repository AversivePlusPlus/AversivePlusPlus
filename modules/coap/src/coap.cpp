#include <coap/coap.hpp>

namespace coap {

union Extended {
  uint8_t ext1;
  uint16_t ext2;
};

static void _get_extended(size_t val, uint8_t& small, uint8_t& ext_size, Extended& ext) {
  if(val < 13) {
    small = (0x0F & val);
    ext_size = 0;
  }
  else if(val <= 0xFF+13) {
    small = 13;
    ext_size = 1;
    ext.ext1 = val-13;
  }
  else if(val <= 0xFFFF+269) {
    small = 14;
    ext_size = 2;
    ext.ext2 = val-269;
  }
}

static void _set_extended(uint8_t size, Extended& a, Extended& b) {
  if(size == 1) {
    a.ext1 = b.ext1;
  }
  else if(size == 2) {
    a.ext2 = b.ext2;
  }
}

static Error _set_option(uint8_t*& cur, uint16_t& prev_delta, OptionNum num, const uint8_t* value, size_t length) {
  const uint16_t num_value = (uint16_t)num;

  if(num_value < prev_delta) {
    return Error::UNSUPPORTED;
  }

  const size_t delta = num_value - prev_delta;

  uint8_t delta_small;
  uint8_t delta_ext_size;
  Extended delta_ext;
  _get_extended(delta, delta_small, delta_ext_size, delta_ext);

  uint8_t length_small;
  uint8_t length_ext_size;
  Extended length_ext;
  _get_extended(length, length_small, length_ext_size, length_ext);

  Extended& cur_delta = *(Extended*)(cur+1);
  Extended& cur_length = *(Extended*)(cur+1+delta_ext_size);

  cur[0] = (delta_small << 4) | (length_small);

  _set_extended(delta_ext_size, cur_delta, delta_ext);
  _set_extended(length_ext_size, cur_length, length_ext);

  uint8_t* p = &cur[1+delta_ext_size+length_ext_size];
  for(size_t i = 0 ; i < length ; i++) {
    p[i] = value[i];
  }

  cur += 1+delta_ext_size+length_ext_size+length;
  prev_delta = num_value;
  return Error::NONE;
}

static Error _set_option(uint8_t*& cur, uint16_t& prev_delta, OptionNum num, uint16_t value) {
  uint16_t h2n = ((value >> 8) & 0xFF) | ((value & 0xFF) << 8);
  return _set_option(cur, prev_delta, num, (const uint8_t*)&h2n, sizeof(h2n));
}

StatePacketWriter<PacketState::HEADER_FILLED>& StatePacketWriter<PacketState::EMPTY>::buildHeader(const PacketReader& request, ResponseCode response_code) {
  const uint8_t version = 0x01;
  const uint8_t type = (uint8_t)MessageType::ACK;
  const uint8_t code = (uint8_t)response_code;
  const uint8_t token_length = request.getTokenLength();

  if(_max_size < (size_t)4 + token_length) {
    _err = Error::BUFFER_TOO_SMALL;
    return *(StatePacketWriter<PacketState::HEADER_FILLED>*)this;
  }

  // Header
  _buffer[0] =
      (version & 0x03) << 6 |
                          (type & 0x03) << 4 |
                          (token_length & 0x0F);

  _buffer[1] = code;

  uint16_t* buf_id = (uint16_t*)&_buffer[2];
  *buf_id = request.getID();

  // Token
  const uint8_t* token = request.getToken();
  for(size_t i = 0 ; i < token_length ; i++) {
    _buffer[4+i] = token[i];
  }

  // End
  uint8_t* cur = _buffer + 4 + token_length;
  _size = cur - _buffer;
  return *(StatePacketWriter<PacketState::HEADER_FILLED>*)this;
}

StatePacketWriter<PacketState::HEADER_FILLED>&
StatePacketWriter<PacketState::EMPTY>::buildHeader(
    MessageType msg_type, ResponseCode response_code, uint16_t id,
    const uint8_t* token, uint8_t token_length) {
  const uint8_t version = 0x01;
  const uint8_t type = (uint8_t)msg_type;
  const uint8_t code = (uint8_t)response_code;

  if(_max_size < (size_t)4 + token_length) {
    _err = Error::BUFFER_TOO_SMALL;
    return *(StatePacketWriter<PacketState::HEADER_FILLED>*)this;
  }

  // Header
  _buffer[0] =
      (version & 0x03) << 6 |
                          (type & 0x03) << 4 |
                          (token_length & 0x0F);

  _buffer[1] = code;

  uint16_t* buf_id = (uint16_t*)&_buffer[2];
  *buf_id = id;

  // Token
  for(size_t i = 0 ; i < token_length ; i++) {
    _buffer[4+i] = token[i];
  }

  // End
  uint8_t* cur = _buffer + 4 + token_length;
  _size = cur - _buffer;
  return *(StatePacketWriter<PacketState::HEADER_FILLED>*)this;
}

StatePacketWriter<PacketState::HEADER_FILLED>& StatePacketWriter<PacketState::HEADER_FILLED>::addOption(OptionNum num, const uint8_t* value, size_t length) {
  if(_err != Error::NONE) {
    return *this;
  }

  uint8_t* cur = _buffer + _size;
  _err =
      _set_option(cur, _option_delta,
                  num,
                  value, length);
  _size = cur - _buffer;
  return *this;
}

StatePacketWriter<PacketState::HEADER_FILLED>& StatePacketWriter<PacketState::HEADER_FILLED>::addOption(OptionNum num, uint16_t value) {
  if(_err != Error::NONE) {
    return *this;
  }

  uint8_t* cur = _buffer + _size;
  _err =
      _set_option(cur, _option_delta,
                  num,
                  value);
  _size = cur - _buffer;
  return *this;
}

StatePacketWriter<PacketState::PAYLOAD_ADDED>& StatePacketWriter<PacketState::HEADER_FILLED>::addPayload(const uint8_t* content, size_t content_size) {
  if(_err != Error::NONE) {
    return *(StatePacketWriter<PacketState::PAYLOAD_ADDED>*)this;
  }

  uint8_t* cur = _buffer + _size;

  if((_max_size - _size) < content_size) {
    _err = Error::BUFFER_TOO_SMALL;
    return *(StatePacketWriter<PacketState::PAYLOAD_ADDED>*)this;
  }

  if(content_size > 0) {
    *cur = 0xFF;
    cur++;

    for(size_t i = 0 ; i < content_size ; i++) {
      cur[i] = content[i];
    }

    cur += content_size;
  }

  _size = cur - _buffer;
  return *(StatePacketWriter<PacketState::PAYLOAD_ADDED>*)this;
}

StatePacketWriter<PacketState::PAYLOAD_ADDED>& StatePacketWriter<PacketState::PAYLOAD_ADDED>::appendPayload(const uint8_t* content, size_t content_size) {
  if(_err != Error::NONE) {
    return *this;
  }

  uint8_t* cur = _buffer + _size;

  if((_max_size - _size) < content_size) {
    _err = Error::BUFFER_TOO_SMALL;
    return *this;
  }

  for(size_t i = 0 ; i < content_size ; i++) {
    cur[i] = content[i];
  }

  cur += content_size;
  _size = cur - _buffer;
  return *this;
}


}
