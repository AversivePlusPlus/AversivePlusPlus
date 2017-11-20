#ifndef PACKET_READER_HPP
#define PACKET_READER_HPP

#include "protocol.hpp"

#include <stdint.h>
#include <stddef.h>

namespace coap {

class OptionReader {
protected:
  const uint8_t* _buffer;
  uint16_t _prev_delta;

public:
  inline OptionReader(const uint8_t* buffer, uint16_t prev_delta)
    : _buffer(buffer), _prev_delta(prev_delta) {
  }

  inline const uint8_t* getBuffer(void) const {
    return _buffer;
  }

  bool isValid(void) const {
    if(_buffer == NULL) {
      return false;
    }

    const uint8_t delta = (_buffer[0] >> 4) & 0x0F;
    const uint8_t length = _buffer[0] & 0x0F;
    if(delta == 15) {
      return false;
    }
    if(length == 15) {
      return false;
    }
    return true;
  }

  uint16_t getDelta(void) const {
    const uint8_t delta = (_buffer[0] >> 4) & 0x0F;
    if(delta < 13) {
      return delta;
    }
    else if(delta == 13) {
      const uint8_t ext_delta = _buffer[1];
      return ((uint16_t)ext_delta) + 13;
    }
    else if(delta == 14) {
      const uint16_t ext_delta = *(uint16_t*)&_buffer[1];
      return ext_delta + 269;
    }
    else {
      // ERROR
      return 0;
    }
  }

  size_t getExtendedDeltaSize(void) const {
    const uint8_t delta = (_buffer[0] >> 4) & 0x0F;
    if(delta == 13) {
      return 1;
    }
    else if(delta == 14) {
      return 2;
    }
    return 0;
  }

  uint16_t getLength(void) const {
    const uint8_t length = _buffer[0] & 0x0F;
    const size_t buffer_offset = 1+getExtendedDeltaSize();
    if(length < 13) {
      return length;
    }
    else if(length == 13) {
      const uint8_t ext_length = _buffer[buffer_offset];
      return ((uint16_t)ext_length) + 13;
    }
    else if(length == 14) {
      const uint16_t ext_length = *(uint16_t*)&_buffer[buffer_offset];
      return ext_length + 269;
    }
    else {
      // ERROR
      return 0;
    }
  }

  size_t getExtendedLengthSize(void) const {
    const uint8_t length = _buffer[0] & 0x0F;
    if(length == 13) {
      return 1;
    }
    else if(length == 14) {
      return 2;
    }
    return 0;
  }

  inline size_t getTotalSize(void) const {
    return 1 + getExtendedDeltaSize() + getExtendedLengthSize() + getLength();
  }

  inline const uint8_t* getValue(void) {
    return _buffer + 1 + getExtendedDeltaSize() + getExtendedLengthSize();
  }

  inline OptionNum getNum(void) const {
    return (OptionNum)(_prev_delta + getDelta());
  }
};

class PacketReader {
private:
  const uint8_t* _buffer;
  const size_t _size;

private:
  class OptionIterator : private OptionReader {
  private:
    size_t _remaining;

  private:
    bool check(const uint8_t* buffer, size_t remaining) {
      return *buffer != 0xFF &&
          OptionReader(buffer, 0).getTotalSize() <= remaining;
    }

  public:
    inline OptionIterator(void)
      : OptionReader(NULL,0), _remaining(0) {
    }

    inline OptionIterator(const uint8_t* buffer, uint16_t delta, size_t remaining)
      : OptionReader((check(buffer, remaining))?buffer:NULL,delta),
        _remaining(remaining) {
    }

    OptionIterator operator++(int) {
      const size_t size = getTotalSize();
      const uint8_t* next = getBuffer() + size;
      _remaining = _remaining-size;
      if(check(next, _remaining)) {
        _prev_delta = (uint16_t)getNum();
        _buffer = next;
      }
      else {
        _buffer = NULL;
        _prev_delta = 0;
      }
      return (*this);
    }

    inline OptionReader& operator*(void) {
      return *(OptionReader*)this;
    }

    inline bool operator==(const OptionIterator& other) {
      return getBuffer() == other.getBuffer();
    }

    inline bool operator!=(const OptionIterator& other) {
      return getBuffer() != other.getBuffer();
    }
  };

public:
  inline PacketReader(const char* buffer, size_t size)
    : _buffer((const uint8_t*)buffer), _size(size) {
  }

  inline PacketReader(const uint8_t* buffer, size_t size)
    : _buffer(buffer), _size(size) {
  }

  inline uint8_t getVersion(void) const {
    return (_buffer[0] >> 6) & 0x03;
  }

  inline MessageType getType(void) const {
    return (MessageType)((_buffer[0] >> 4) & 0x03);
  }

  inline uint8_t getTokenLength(void) const {
    return _buffer[0] & 0x0F;
  }

  inline code_t getCode(void) const {
    return (code_t)(_buffer[1]);
  }

  inline MethodCode getMethodCode(void) const {
    return (MethodCode)(_buffer[1]);
  }

  inline ResponseCode getResponseCode(void) const {
    return (ResponseCode)(_buffer[1]);
  }

  inline uint16_t getID(void) const {
    return *(uint16_t*)(&_buffer[2]);
  }

  inline const uint8_t* getToken(void) const {
    return &_buffer[4];
  }

  OptionIterator getOptionsBegin(void) const {
    const uint8_t* beg = _buffer + 4 + getTokenLength();
    return OptionIterator(beg,0, _size-(beg-_buffer));
  }

  inline OptionIterator getOptionsEnd(void) const {
    return OptionIterator();
  }

  const uint8_t* getPayload(void) const {
    const uint8_t* cur = _buffer + 4 + getTokenLength();
    while(cur-_buffer < (int)_size) {
      if(*cur == 0xFF) {
        return cur+1;
      }
      cur += OptionReader(cur, 0).getTotalSize();
    }
    return NULL;
  }

  size_t getPayloadLength(void) const {
    const uint8_t* const p = getPayload();
    if(p == NULL) {
      return 0;
    }
    return _size - (p - _buffer);
  }
};

}

#endif//PACKET_READER_HPP
