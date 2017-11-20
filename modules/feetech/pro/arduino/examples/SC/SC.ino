#include <aversive_base.h>
#include <aversive_container.h>
#include <aversive_stream.h>
#include <aversive_feetech.h>

#include <feetech/sc.hpp> 

class ArduinoStream : Aversive::Stream::IOStream<ArduinoStream> {
private:
  HardwareSerial& _hs;
  
public:
  inline ArduinoStream(HardwareSerial& serial)
    : _hs(serial) {
  }

  inline u8 get(void) {
    u8 ret = 0;
    _hs.readBytes(&ret, 1);
    return ret;
  }

  inline u16 read(u8* data, u16 length) {
    return _hs.readBytes(data, length);
  }

  inline u16 readable(void) {
    return _hs.available();
  }

  inline void put(u8 c) {
    _hs.write(c);
  }

  inline u16 write(u8* data, u16 length) {
    return _hs.write(data, length);
  }

  inline u16 writable(void) {
    return _hs.availableForWrite();
  }

};

ArduinoStream as(Serial);
Aversive::Feetech::SC<decltype(as)> sc(as);

void setup() {
  Serial.begin(9600);
}

void loop() {
  sc.ping(1);
}
