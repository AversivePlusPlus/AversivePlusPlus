#include<stream/string_stream.hpp>
#include<stream/formatted_stream.hpp>

using namespace Stream;

int main(int, char**) {
  FormattedStringStream<64> fss;
  char s[32];

  fss << 18 << "\n";
  fss >> s;

  return 0;
}
