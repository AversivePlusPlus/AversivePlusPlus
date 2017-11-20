#ifndef AVERSIVE_FS_FILE_ENTRY_HPP
#define AVERSIVE_FS_FILE_ENTRY_HPP

#include "entry.hpp"
#include "filesystem.hpp"
#include "path_list.hpp"

namespace Aversive {
namespace fs {

class FileEntry :
    public Entry,
    public FileSystem,
    public PathList<FileEntry> {
private:
  File _file;

public:

  template<class Stream>
  FileEntry(const char* name, Stream& stream)
    : Entry(name), _file(stream) {
  }

  template<class OutputStream, class InputStream>
  FileEntry(const char* name, OutputStream& ostream, InputStream& istream)
    : Entry(name), _file(ostream, istream) {
  }

  File open(const char* p) {
    unsigned int len = strlen(this->_name);
    if(len != strlen(p+1)) {
      return File();
    }
    if(strcmp(p+1, this->_name) != 0) {
      return File();
    }
    return _file;
  }

public:
  unsigned int size(void) {
    return 1;
  }
};

template<>
class Path<FileEntry> : public BasePath<FileEntry> {
public:
  inline Path(FileEntry& entry, unsigned int index)
    : BasePath<FileEntry>(entry, index) {
  }

  inline unsigned int size(void) const {
    return 1;
  }

  inline const char* operator[](unsigned int i) {
    if(_index == 0 && i == 0) {
      return this->_entry.name();
    }
    return 0;
  }
};

}
}

#endif//AVERSIVE_FS_FILE_ENTRY_HPP
