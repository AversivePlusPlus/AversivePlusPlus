#include "../my_assert.hpp"
#include <iostream>
#include <string.h>

#include <stream/buffer_stream.hpp>
#include <feetech/sc.hpp>

#include <feetech/packet_writer.hpp>
#include <feetech/packet_reader.hpp>

#include <feetech/servo_stream.hpp>

#include <feetech/servo.hpp>

using namespace Aversive::Base;
using namespace Aversive::Stream;
using namespace Aversive::Feetech;

class MoreInfosPacketReader : public PacketReader {
public:
  MoreInfosPacketReader(const char* buffer, unsigned int size)
    : PacketReader(buffer, size) {
  }

  u8 sum(void) {
    return this->PacketReader::sum();
  }

  bool checkMinSize(void) {
    return this->PacketReader::checkMinSize();
  }

  bool checkStart(void) {
    return this->PacketReader::checkStart();
  }

  bool checkSize(void) {
    return this->PacketReader::checkSize();
  }

  bool checkSum(void) {
    return this->PacketReader::checkSum();
  }

};

class DummyFeetechStream :
    public InputStream<char, unsigned int>,
    public OutputStream<char, unsigned int> {
private:
  constexpr static unsigned int SIZE = 128;
  char _buffer[SIZE];
  unsigned int _write;
  unsigned int _readable;
  unsigned int _read;

  void update(void) {
    PacketReader pr(_buffer, _write);
    _read = _readable = 0;
    if(!pr.valid()) return;

    if(pr.instr() == Protocol::INST_WRITE) {
      WritePacketReader pr(_buffer, _write);
      if(pr.valid()) {
        const u8 id = pr.id();
        PacketWriter pw(_buffer, SIZE);
        pw.ack(id);
        _readable = pw.size();
      }
    }
    else if(pr.instr() == Protocol::INST_PING) {
      PacketReader pr(_buffer, _write);
      if(pr.valid()) {
        const u8 id = pr.id();
        PacketWriter pw(_buffer, SIZE);
        pw.ack(id);
        _readable = pw.size();
      }
    }
    else if(pr.instr() == Protocol::INST_READ) {
      ReadPacketReader pr(_buffer, _write);
      if(pr.valid() && pr.size() < SIZE) {
        const u8 id = pr.id();
        const unsigned int s = pr.size();
        PacketWriter pw(_buffer, SIZE);
        char tmp[SIZE];
        for(unsigned int i = 0 ; i < s ; i++) {
          tmp[i] = 42;
        }
        pw.response(id, (const u8*)tmp, s);
        _readable = pw.size();
      }
    }

    _write = 0;
  }

public:
  DummyFeetechStream(void)
    : _buffer{0}, _write(0), _read(0) {
  }

  void put(char c) {
    if(_write+1 <= SIZE) {
      _buffer[_write] = c;
      _write += 1;
      update();
    }
  }

  unsigned int write(const char* data, unsigned int size) {
    if(_write+size <= SIZE) {
      for(unsigned int i = 0 ; i < size ; i++) {
        _buffer[_write+i] = data[i];
      }
      _write += size;
      update();
      return size;
    }
    return 0;
  }

  unsigned int writable(void) {
    return SIZE-_write;
  }

  char get(void) {
    if(_read+1 <= _readable) return _buffer[_read++];
    return 0;
  }

  unsigned int read(char* data, unsigned int size) {
    if(_read+size <= _readable) {
      for(unsigned int i = 0 ; i < size ; i++) {
        data[i] = _buffer[_read+i];
      }
      _read += size;
      return size;
    }
    return 0;
  }

  unsigned int readable(void) {
    return _readable-_read;
  }
};


int main(void) {
  ////////////////////////////////////////////////////////////////
  // PacketWriter/PacketReader
  char buf[32];
  PacketWriter pw(buf, 32);
  myAssert(pw.data() == buf, "Line " S__LINE__ "PacketWriter::data");
  myAssert(pw.size() == 0, "Line " S__LINE__ "PacketWriter::size");

  pw.response(1, (u8*)"hello", sizeof("hello"));
  myAssert(pw.size() == 12, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == 0, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    ResponsePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == sizeof("hello"), "Line " S__LINE__ "ResponsePacketReader::size");
    myAssert(strcmp((const char*)pr.data(), "hello") == 0, "Line " S__LINE__ "ResponsePacketReader::data");
  }

  pw.ack(1);
  myAssert(pw.size() == 6, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == 0, "Line " S__LINE__ "PacketReader::instr");
  }

  pw.ping(1);
  myAssert(pw.size() == 6, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_PING, "Line " S__LINE__ "PacketReader::instr");
  }

  pw.write(1, Protocol::P_ID, 2);
  myAssert(pw.size() == 8, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    WritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 1, "Line " S__LINE__ "ResponsePacketReader::size");
    myAssert(pr.data()[0] == 2, "Line " S__LINE__ "ResponsePacketReader::data");
    myAssert(pr.reg() == Protocol::P_ID, "Line " S__LINE__ "ResponsePacketReader::reg");
  }

  pw.write(1, Protocol::P_GOAL_POSITION, 512);
  myAssert(pw.size() == 9, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    WritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 2, "Line " S__LINE__ "ResponsePacketReader::size");
    myAssert(pr.data()[0] == 2, "Line " S__LINE__ "ResponsePacketReader::data");
    myAssert(pr.data()[1] == 0, "Line " S__LINE__ "ResponsePacketReader::data");
    myAssert(pr.reg() == Protocol::P_GOAL_POSITION, "Line " S__LINE__ "ResponsePacketReader::reg");
  }

  pw.write(1, Protocol::P_ID, (u8*)"hello", sizeof("hello"));
  myAssert(pw.size() == 13, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    WritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == sizeof("hello"), "Line " S__LINE__ "ResponsePacketReader::size");
    myAssert(strcmp((const char*)pr.data(), "hello") == 0, "Line " S__LINE__ "ResponsePacketReader::data");
    myAssert(pr.reg() == Protocol::P_ID, "Line " S__LINE__ "ResponsePacketReader::reg");
  }

  pw.read(1, Protocol::P_ID, 1);
  myAssert(pw.size() == 8, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 1, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_READ, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    ReadPacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 1, "Line " S__LINE__ "ResponsePacketReader::size");
    myAssert(pr.reg() == Protocol::P_ID, "Line " S__LINE__ "ResponsePacketReader::reg");
  }

  pw.syncWrite(Protocol::P_ID, 1);
  myAssert(pw.size() == 0, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(!pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(!pr.valid(), "Line " S__LINE__ "PacketReader::valid");
  }

  pw.syncWrite(Protocol::P_ID, 1)
      .add(2,1)
      .add(3,1);
  myAssert(pw.size() == 12, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 0xFF, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_SYNC_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    SyncWritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 2, "Line " S__LINE__ "SyncWritePacketReader::size");
    myAssert(pr[0].id() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[0].size() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[0].data()[0] == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
    myAssert(pr[1].id() == 3, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[1].size() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[1].data()[0] == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
  }

  auto swpw = pw.syncWrite(Protocol::P_ID, 1);
  swpw.add(2,1);
  myAssert(pw.size() == 10, "Line " S__LINE__ "PacketWriter::size");
  swpw.add(3,1);
  myAssert(pw.size() == 12, "Line " S__LINE__ "PacketWriter::size");
  swpw.add(4,1);
  myAssert(pw.size() == 14, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 0xFF, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_SYNC_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    SyncWritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 3, "Line " S__LINE__ "SyncWritePacketReader::size");
    myAssert(pr[0].id() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[0].size() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[0].data()[0] == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
    myAssert(pr[1].id() == 3, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[1].size() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[1].data()[0] == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
    myAssert(pr[2].id() == 4, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[2].size() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[2].data()[0] == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
  }

  pw.syncWrite(Protocol::P_ID, 2)
      .add(2,1)
      .add(3,1);
  myAssert(pw.size() == 0, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(!pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(!pr.valid(), "Line " S__LINE__ "PacketReader::valid");
  }

  pw.syncWrite(Protocol::P_GOAL_POSITION, 2)
      .add(2,512)
      .add(3,1024);
  myAssert(pw.size() == 14, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 0xFF, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_SYNC_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    SyncWritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 2, "Line " S__LINE__ "SyncWritePacketReader::size");
    myAssert(pr[0].id() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[0].size() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[0].data()[0] == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
    myAssert(pr[0].data()[1] == 0, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
    myAssert(pr[1].id() == 3, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[1].size() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(pr[1].data()[0] == 4, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
    myAssert(pr[1].data()[1] == 0, "Line " S__LINE__ "SyncWritePacketReader::[]::data");
  }

  pw.syncWrite(5, 6)
      .add(1,(u8*)"hello", sizeof("hello"))
      .add(2,(u8*)"hello", sizeof("hello"));
  myAssert(pw.size() == 22, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 0xFF, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_SYNC_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    SyncWritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 2, "Line " S__LINE__ "SyncWritePacketReader::size");
    myAssert(pr[0].id() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[0].size() == sizeof("hello"), "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(strcmp((const char*)pr[0].data(), "hello") == 0, "Line " S__LINE__ "ResponsePacketReader::data");
    myAssert(pr[1].id() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[1].size() == sizeof("hello"), "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(strcmp((const char*)pr[1].data(), "hello") == 0, "Line " S__LINE__ "ResponsePacketReader::data");
  }

  pw.syncWrite(Protocol::P_ID, 6)
      .add(1,(u8*)"hello", sizeof("hello"))
      .add(2,(u8*)"hello", sizeof("hello"));
  myAssert(pw.size() == 22, "Line " S__LINE__ "PacketWriter::size");
  {
    MoreInfosPacketReader pr(pw.data(), pw.size());
    myAssert(pr.checkMinSize(), "Line " S__LINE__ "PacketReader::checkMinSize");
    myAssert(pr.checkStart(), "Line " S__LINE__ "PacketReader::checkStart");
    myAssert(pr.checkSize(), "Line " S__LINE__ "PacketReader::checkSize");
    //std::cout << (int)(u8)~pr.sum() << " " << (int)((u8)buf[pw.size()-1]) << std::endl;
    myAssert(pr.checkSum(), "Line " S__LINE__ "PacketReader::checkSum");
    myAssert(pr.valid(), "Line " S__LINE__ "PacketReader::valid");
    myAssert(pr.id() == 0xFF, "Line " S__LINE__ "PacketReader::id");
    myAssert(pr.instr() == Protocol::INST_SYNC_WRITE, "Line " S__LINE__ "PacketReader::instr");
  }
  {
    SyncWritePacketReader pr(pw.data(), pw.size());
    myAssert(pr.size() == 2, "Line " S__LINE__ "SyncWritePacketReader::size");
    myAssert(pr[0].id() == 1, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[0].size() == sizeof("hello"), "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(strcmp((const char*)pr[0].data(), "hello") == 0, "Line " S__LINE__ "ResponsePacketReader::data");
    myAssert(pr[1].id() == 2, "Line " S__LINE__ "SyncWritePacketReader::[]::id");
    myAssert(pr[1].size() == sizeof("hello"), "Line " S__LINE__ "SyncWritePacketReader::[]::size");
    myAssert(strcmp((const char*)pr[1].data(), "hello") == 0, "Line " S__LINE__ "ResponsePacketReader::data");
  }

  ////////////////////////////////////////////////////////////////
  // ServoStream
  DummyFeetechStream dfs;
  ServoStream<decltype(dfs)> ss(dfs, 1);
  ss.seek(Protocol::P_ID);
  myAssert(ss.tell() == Protocol::P_ID, "Line " S__LINE__ "ServoStream::tell");
  ss.put(2);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(ss.tell() == Protocol::P_ID+1, "Line " S__LINE__ "ServoStream::tell");
  ss.write("hello", sizeof("hello"));
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(ss.tell() == Protocol::P_ID+1+sizeof("hello"), "Line " S__LINE__ "ServoStream::tell");
  ss.seek(0);
  myAssert(ss.writable() == 255, "Line " S__LINE__ "ServoStream::writable");
  myAssert(ss.readable() == 255, "Line " S__LINE__ "ServoStream::readable");
  ss.seek(255);
  myAssert(ss.writable() == 0, "Line " S__LINE__ "ServoStream::writable");
  myAssert(ss.readable() == 0, "Line " S__LINE__ "ServoStream::readable");
  ss.seek(Protocol::P_ID);
  myAssert(ss.get() == 42, "Line " S__LINE__ "ServoStream::get");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(ss.tell() == Protocol::P_ID+1, "Line " S__LINE__ "ServoStream::tell");
  {
    constexpr unsigned int size = 6;
    char buffer[size] = {0};
    myAssert(ss.read(buffer, size) == size, "Line " S__LINE__ "ServoStream::read");
    myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
    for(unsigned int i = 0 ; i < size ; i++) {
      myAssert(buffer[i] == 42, "Line " S__LINE__ "ServoStream::read");
    }
    myAssert(ss.tell() == Protocol::P_ID+1+size, "Line " S__LINE__ "ServoStream::tell");
  }

  ////////////////////////////////////////////////////////////////
  // ServoStream
  Servo<decltype(dfs)> servo(dfs, 1);
  myAssert(servo.ping(), "Line " S__LINE__ ": Servo::ping");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  servo.enableTorque();
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  servo.disableTorque();
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(!servo.isTorqueEnabled(), "Line " S__LINE__ ": Servo::isTorqueEnabled");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  servo.setPosition(512);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(servo.getPosition() == 42+42*256, "Line " S__LINE__ ": Servo::getPosition");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  servo.setId(2);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(servo.getLoad() == 42+42*256, "Line " S__LINE__ ": Servo::getLoad");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(servo.getSpeed() == 42+42*256, "Line " S__LINE__ ": Servo::getSpeed");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");

  ////////////////////////////////////////////////////////////////
  // SC
  constexpr unsigned int id = 1;
  SC<decltype(dfs)> sc(dfs);
  myAssert(sc.ping(id), "Line " S__LINE__ ": SC::ping");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  sc.enableTorque(id);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  sc.disableTorque(id);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(!sc.isTorqueEnabled(id), "Line " S__LINE__ ": SC::isTorqueEnabled");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  sc.setPosition(id, 512);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(sc.getPosition(id) == 42+42*256, "Line " S__LINE__ ": SC::getPosition");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  sc.setId(id, 2);
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(sc.getLoad(id) == 42+42*256, "Line " S__LINE__ ": SC::getLoad");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");
  myAssert(sc.getSpeed(id) == 42+42*256, "Line " S__LINE__ ": SC::getSpeed");
  myAssert(dfs.readable() == 0, "Line " S__LINE__ ": DummyFeetechStream::readable");

  std::cout << "OK" << std::endl;
  return 0;
}
