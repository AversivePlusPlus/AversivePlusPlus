#ifndef AVERSIVE_FS_PATH_HPP
#define AVERSIVE_FS_PATH_HPP

namespace Aversive {
namespace fs {

template<class Entry>
class BasePath {
protected:
  Entry& _entry;
  unsigned int _index;

public:
  inline BasePath(Entry& entry, unsigned int index)
    : _entry(entry), _index(index) {
  }

  inline unsigned int size(void) {
    return 0;
  }

  inline const char* operator[](unsigned int) {
    return 0;
  }
};

template<class Entry>
class Path : public BasePath<Entry> {
public:
  inline Path(Entry& entry, unsigned int index)
    : BasePath<Entry>(entry, index) {
  }
};

}
}

#endif//AVERSIVE_FS_PATH_HPP
