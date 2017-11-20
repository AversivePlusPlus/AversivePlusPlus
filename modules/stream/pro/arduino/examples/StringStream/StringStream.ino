#include <aversive_base.h>
#include <aversive_container.h>
#include <aversive_stream.h>

#include <stream/string_stream.hpp> 

Aversive::Stream::FormattedStringStream<32> ss;

void setup() {
  Serial.begin(9600);
  Serial.println("test");
}

void loop() {
  ss << "hello!" << (u16)42 << "\n";
  char buff[32];
  ss.read((u8*)buff, ss.readable());
  
  Serial.println(buff);
}
