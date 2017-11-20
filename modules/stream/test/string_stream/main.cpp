#include <stream/buffer_stream.hpp>
#include <stream/formatted_stream.hpp>

#include <iostream>
#include <cstring>
#include <cstdio>
#include "../my_assert.hpp"

using namespace Aversive::Stream;
using namespace Aversive::Container::Simple;

static constexpr unsigned int SIZE = 2048;
static constexpr u64 BUFFER_SIZE = 1024;
static char buffer[BUFFER_SIZE] = { 0 };
static constexpr s64 VALUE = 15;

static const char* const str1 = "Hello";
static const char* const str2 = "How are you?";

void clean_buffer(void) {
  for(unsigned int i = 0 ; i < BUFFER_SIZE ; i++) {
    buffer[i] = 0;
  }
}

template<typename Signed, typename Unsigned, typename Stream>
void integerTester(FormattedStreamDecorator<Stream>& stream) {
  constexpr int BIT = sizeof(Signed)*8;

  stream << (Unsigned) VALUE << "\0";
  Unsigned a;
  stream >> a;
  snprintf(buffer, BUFFER_SIZE, "Line " S__LINE__ ": StringStream formatted u%d read and write", BIT);
  myAssert(a == (Unsigned) VALUE, buffer);

  stream << (Signed) VALUE << " ";
  Signed b;
  stream >> b;
  snprintf(buffer, BUFFER_SIZE, "Line " S__LINE__ ": StringStream formatted s%d read and write", BIT);
  myAssert(b == (Signed) VALUE, buffer);
}

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;
  
  BufferStream<SIZE> _stream;
  auto& stream = formatted(_stream);

  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");
  stream.put('a');

  myAssert(stream.writable() == SIZE - 1, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 1, "Line " S__LINE__ ": StringStream<SIZE>::readable");

  char a = stream.get();
  myAssert(a == 'a',  "Line " S__LINE__ ": StringStream get and set value");
  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");

  integerTester<s8,  u8> (stream);
  integerTester<s16, u16>(stream);
  integerTester<s32, u32>(stream);
  integerTester<s64, u64>(stream);
  
  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");

  stream << str1;
  clean_buffer();
  stream.read(buffer, stream.readable());
  myAssert(strcmp(str1, buffer) == 0, "Line " S__LINE__ ": StringStream fomatted string write");

  stream << endl;
  clean_buffer();
  stream.read(buffer, stream.readable());
  myAssert(strcmp("\n", buffer) == 0, "Line " S__LINE__ ": StringStream fomatted endl write");

  myAssert(stream.writable() == SIZE, "Line " S__LINE__ ": StringStream<SIZE>::writable");
  myAssert(stream.readable() == 0, "Line " S__LINE__ ": StringStream<SIZE>::readable");
  
  std::cout << "OK" << std::endl;
  return 0;
}
