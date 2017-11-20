#include <fs/file_entry.hpp>
#include <fs/simple_dir_entry.hpp>
#include <fs/pair_dir_entry.hpp>

#include <stream/buffer_stream.hpp>

#include <iostream>
using namespace std;
using namespace Aversive::fs;
using namespace Aversive::Stream;

template<class Entry>
std::ostream& operator<<(std::ostream& stream, Path<Entry> path) {
  for(unsigned int i = 0 ; i < path.size() ; i++) {
    stream << "/" << path[i];
  }
  return stream;
}

int main(int, char**) {
  BufferStream<128> bs1;
  BufferStream<128> bs2;
  FileEntry f1("test", bs1);
  FileEntry f2("lol", bs2);
  SimpleDirEntry<FileEntry> d2("test", f2);
  PairDirEntry<FileEntry, decltype(d2)> d1("miew", f1, d2);
  auto& fs = d1;

  bs1.write("a", 2);
  bs2.write("b", 2);

  {
    auto f = fs.open("/miew/test");
    if(f != INVALID_FILE) {
      char buffer[128] = {};
      f.read(buffer, f.readable());
      cout << buffer << endl;
    }
    else {
      cout << "ERROR" << endl;
    }
  }

  {
    auto f = fs.open("/miew/test/lol");
    if(f != INVALID_FILE) {
      char buffer[128] = {};
      f.read(buffer, f.readable());
      cout << buffer << endl;
    }
    else {
      cout << "ERROR" << endl;
    }
  }

  for(unsigned int i = 0 ; i < fs.size() ; i++) {
    cout << fs[i] << endl;
  }

  return 0;
}
