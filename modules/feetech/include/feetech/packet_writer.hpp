#ifndef FEETECH_PACKET_WRITER_HPP
#define FEETECH_PACKET_WRITER_HPP

#include <feetech/protocol.hpp>

namespace Aversive {
namespace Feetech {

class PacketWriter {
protected:
  u8* _buffer;
  unsigned int _size;
  const unsigned int _limit;

protected:
  PacketWriter(PacketWriter& other)
    : _buffer(other._buffer), _size(other._size), _limit(other._limit) {
  }

public:
  PacketWriter(char* buffer, unsigned int size)
    : _buffer((u8*)buffer), _size(0), _limit(size) {
  }

  const char* data(void) const {
    return (const char*)_buffer;
  }

  unsigned int size(void) const {
    return _size;
  }

public:
  void response(u8 id, const u8* buffer, unsigned int size) {
    const unsigned int len = 2+size;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = 0;

      for(unsigned int i = 0 ; i < size ; i++) {
        sum += _buffer[5+i] = buffer[i];
      }

      _buffer[_size-1] = ~sum;
    }
    else {
      _size = 0;
    }
  }

  void ack(u8 id) {
    const unsigned int len = 2;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = 0;
      _buffer[_size-1] = ~sum;
    }
    else {
      _size = 0;
    }
  }

  void ping(u8 id) {
    const unsigned int len = 2;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = Protocol::INST_PING;

      _buffer[5] = ~sum;
    }
    else {
      _size = 0;
    }
  }

  void write(u8 id, RegisterAddress<u8> reg, u8 value) {
    const unsigned int len = 4;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = Protocol::INST_WRITE;

      sum += _buffer[5] = reg;
      sum += _buffer[6] = value;

      _buffer[7] = ~sum;
    }
    else {
      _size = 0;
    }
  }

  void write(u8 id, RegisterAddress<u16> reg, u16 value) {
    const unsigned int len = 5;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = Protocol::INST_WRITE;

      sum += _buffer[5] = reg;
      sum += _buffer[6] = (value>>8)&0xFF;
      sum += _buffer[7] = value&0xFF;

      _buffer[8] = ~sum;
    }
    else {
      _size = 0;
    }
  }

  void write(u8 id, u8 reg, const u8* buffer, unsigned int size) {
    const unsigned int len = 3+size;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = Protocol::INST_WRITE;

      sum += _buffer[5] = reg;
      for(unsigned int i = 0 ; i < size ; i++) {
        sum += _buffer[6+i] = buffer[i];
      }

      _buffer[_size-1] = ~sum;
    }
    else {
      _size = 0;
    }
  }

  void read(u8 id, u8 reg, unsigned int size) {
    const unsigned int len = 4;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = id;
      sum += _buffer[3] = len;
      sum += _buffer[4] = Protocol::INST_READ;

      sum += _buffer[5] = reg;
      sum += _buffer[6] = (u8)size;

      _buffer[7] = ~sum;
    }
  }

protected:
  friend class SyncWriteHelper;
  class SyncWriteHelper {
  protected:
    PacketWriter& _pw;

    unsigned int required(void) {
      if(8 <= _pw._size && _pw._buffer[4] == Protocol::INST_SYNC_WRITE) {
        return _pw._buffer[6];
      }
      return 0;
    }

  public:
    SyncWriteHelper(PacketWriter& pw) :
      _pw(pw) {
    }

    ~SyncWriteHelper(void) {
      // no item added => invalid
      if(_pw._size <= 8) {
        _pw._size = 0;
      }
    }

    SyncWriteHelper& add(u8 id, const u8* buffer, unsigned int size) {
      if(required() == size && size != 0 && _pw._size+size+1 <= _pw._limit) {
        u8 sum = ~_pw._buffer[_pw._size-1];

        sum += _pw._buffer[_pw._size-1] = id;
        for(unsigned int i = 0 ; i < size ; i++) {
          sum += _pw._buffer[_pw._size+i] = buffer[i];
        }

        _pw._buffer[3] += size+1;
        _pw._buffer[_pw._size+size] = ~(sum+size+1);
        _pw._size += size+1;
      }
      else {
        _pw._size = 0;
      }

      return *this;
    }
  };

  friend class SyncWriteHelper8;
  class SyncWriteHelper8 : public SyncWriteHelper {
  public:
    SyncWriteHelper8(PacketWriter& pw) :
      SyncWriteHelper(pw) {
    }

    SyncWriteHelper8& add(u8 id, u8 value) {
      if(required() == 1 && _pw._size+2 <= _pw._limit) {
        u8 sum = ~_pw._buffer[_pw._size-1];

        sum += _pw._buffer[_pw._size-1] = id;
        sum += _pw._buffer[_pw._size] = value;

        _pw._buffer[3] += 2;
        _pw._buffer[_pw._size+1] = ~(sum+2);
        _pw._size += 2;
      }
      else {
        _pw._size = 0;
      }

      return *this;
    }

    SyncWriteHelper& add(u8 id, const u8* buffer, unsigned int size) {
      return this->SyncWriteHelper::add(id, buffer, size);
    }
  };

  friend class SyncWriteHelper16;
  class SyncWriteHelper16 : public SyncWriteHelper {
  public:
    SyncWriteHelper16(PacketWriter& pw) :
      SyncWriteHelper(pw) {
    }

    SyncWriteHelper16& add(u8 id, u16 value) {
      if(required() == 2 && _pw._size+3 <= _pw._limit) {
        u8 sum = ~_pw._buffer[_pw._size-1];

        sum += _pw._buffer[_pw._size-1] = id;
        sum += _pw._buffer[_pw._size+0] = (value>>8)&0xFF;
        sum += _pw._buffer[_pw._size+1] = value&0xFF;

        _pw._buffer[3] += 3;
        _pw._buffer[_pw._size+2] = ~(sum+3);
        _pw._size += 3;
      }
      else {
        _pw._size = 0;
      }

      return *this;
    }

    SyncWriteHelper& add(u8 id, const u8* buffer, unsigned int size) {
      return this->SyncWriteHelper::add(id, buffer, size);
    }
  };

  void syncWriteBegin(u8 reg, unsigned int size) {
    const unsigned int len = 4;
    if(len+4 <= _limit) {
      _size = len+4;

      u8 sum = 0;

      _buffer[0] = Protocol::START;
      _buffer[1] = Protocol::START;
      sum += _buffer[2] = 0xFF;
      sum += _buffer[3] = len;
      sum += _buffer[4] = Protocol::INST_SYNC_WRITE;

      sum += _buffer[5] = reg;
      sum += _buffer[6] = (u8)size;

      _buffer[7] = ~sum;
    }
  }

public:
  SyncWriteHelper8 syncWrite(RegisterAddress<u8> reg, unsigned int size) {
    syncWriteBegin(reg, size);
    return SyncWriteHelper8(*this);
  }

  SyncWriteHelper16 syncWrite(RegisterAddress<u16> reg, unsigned int size) {
    syncWriteBegin(reg, size);
    return SyncWriteHelper16(*this);
  }

  SyncWriteHelper syncWrite(u8 reg, unsigned int size) {
    syncWriteBegin(reg, size);
    return SyncWriteHelper(*this);
  }
};

}
}

#endif//FEETECH_PACKET_WRITER_HPP
