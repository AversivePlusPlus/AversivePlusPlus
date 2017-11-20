#ifndef FEETECH_PACKET_READER_HPP
#define FEETECH_PACKET_READER_HPP

#include <feetech/protocol.hpp>

namespace Aversive {
namespace Feetech {

class PacketReader {
protected:
  u8* _buffer;
  unsigned int _size;

protected:
  PacketReader(PacketReader& other)
    : _buffer(other._buffer), _size(other._size) {
  }

protected:
  u8 sum(void) const {
    u8 sum = 0;
    for(unsigned int i = 2 ; i < _size-1 ; i++) {
      sum += _buffer[i];
    }
    return sum;
  }

protected:
  bool checkMinSize(void) const {
    return 5 < _size;
  }

  bool checkStart(void) const {
    return
        _buffer[0] == Protocol::START &&
        _buffer[1] == Protocol::START;
  }

  bool checkSize(void) const {
    return _size == (unsigned int)(_buffer[3]+4);
  }

  bool checkSum(void) const {
    return (u8)(~sum()) == (u8)_buffer[_size-1];
  }

public:
  PacketReader(const char* buffer, unsigned int size)
    : _buffer((u8*)buffer), _size(size) {
  }

  bool valid(void) const {
    return checkMinSize() && checkStart() && checkSize() && checkSum();
  }

  u8 id(void) const {
    return _buffer[2];
  }

  u8 instr(void) const {
    return _buffer[4];
  }
};

class AckPacketReader : public PacketReader {
public:
  static inline constexpr unsigned int expected(void) {
    return 6;
  }

public:
  AckPacketReader(const char* buffer, unsigned int size)
    : PacketReader(buffer, size) {
  }

  bool valid(void) const {
    return PacketReader::valid() && instr() == 0;
  }
};

class ResponsePacketReader : public PacketReader {
public:
  static inline constexpr unsigned int expected(unsigned int size) {
    return 6+size;
  }

public:
  ResponsePacketReader(const char* buffer, unsigned int size)
    : PacketReader(buffer, size) {
  }

  bool valid(void) const {
    return PacketReader::valid() && instr() == 0;
  }

  const u8* data(void) const {
    return &_buffer[5];
  }

  unsigned int size(void) const {
    return _buffer[3]-2;
  }
};

class WritePacketReader : public PacketReader {
public:
  WritePacketReader(const char* buffer, unsigned int size)
    : PacketReader(buffer, size) {
  }

  bool valid(void) const {
    return PacketReader::valid() && instr() == Protocol::INST_WRITE;
  }

  const u8* data(void) const {
    return &_buffer[6];
  }

  unsigned int size(void) const {
    return _buffer[3]-3;
  }

  u8 reg(void) const {
    return _buffer[5];
  }
};

class ReadPacketReader : public PacketReader {
public:
  ReadPacketReader(const char* buffer, unsigned int size)
    : PacketReader(buffer, size) {
  }

  bool valid(void) const {
    return PacketReader::valid() && instr() == Protocol::INST_READ;
  }

  unsigned int size(void) const {
    return _buffer[6];
  }

  u8 reg(void) const {
    return _buffer[5];
  }
};

class SyncWritePacketReader : public PacketReader {
public:
  SyncWritePacketReader(const char* buffer, unsigned int size)
    : PacketReader(buffer, size) {
  }

  bool valid(void) const {
    return PacketReader::valid() && instr() == Protocol::INST_SYNC_WRITE;
  }

  unsigned int size(void) const {
    return (_buffer[3]-4)/(_buffer[6]+1);
  }

private:
  class SyncWriteItemRef {
    const SyncWritePacketReader& _pr;
    unsigned int _index;

  public:
    SyncWriteItemRef(const SyncWritePacketReader& pr, unsigned int index)
      : _pr(pr), _index(index) {
    }

    bool valid(void) const {
      return _index < _pr.size();
    }

    u8 reg(void) const {
      return _pr._buffer[5];
    }

    unsigned int size(void) const {
      return _pr._buffer[6];
    }

    u8 id(void) const {
      return _pr._buffer[7+_index*(size()+1)];
    }

    const u8* data(void) const {
      return &_pr._buffer[7+_index*(size()+1)+1];
    }
  };

public:
  const SyncWriteItemRef operator[](unsigned int index) const {
    return SyncWriteItemRef(*this, index);
  }
};

}
}

#endif//FEETECH_PACKET_READER_HPP
