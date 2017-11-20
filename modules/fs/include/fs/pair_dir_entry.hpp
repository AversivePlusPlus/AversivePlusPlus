#ifndef AVERSIVE_FS_PAIR_DIR_ENTRY_HPP
#define AVERSIVE_FS_PAIR_DIR_ENTRY_HPP

#include "entry.hpp"
#include "filesystem.hpp"
#include "path_list.hpp"

#include <base/pair.hpp>

namespace Aversive {
namespace fs {

template<class Left, class Right>
class PairDirEntry :
    public Entry,
    public FileSystem,
    public PathList<PairDirEntry<Left, Right>> {
protected:
  friend class Path<PairDirEntry>;

protected:
  Aversive::Base::Pair<Left&, Right&> _child;

public:
  PairDirEntry(const char* name, Left& left, Right& right)
    : Entry(name), _child(left, right) {
  }

  File open(const char* p) {
    if(strncmp(p+1, this->_name, strlen(this->_name)) == 0) {
      {
        File ret = _child.left().open(p+1+strlen(this->_name));
        if(ret != INVALID_FILE) return ret;
      }
      {
        File ret = _child.right().open(p+1+strlen(this->_name));
        if(ret != INVALID_FILE) return ret;
      }
    }
    return File();
  }

  unsigned int size(void) {
    return
        _child.left().size() +
        _child.right().size();
  }
};

template<class Left, class Right>
class Path<PairDirEntry<Left, Right>> : public BasePath<PairDirEntry<Left, Right>> {
public:
  inline Path(PairDirEntry<Left, Right>& entry, unsigned int index)
    : BasePath<PairDirEntry<Left, Right>>(entry, index) {
  }

  inline unsigned int size(void) const {
    if(this->_index < this->_entry.size()) {
      if(this->_index < this->_entry._child.left().size()) {
        return 1+this->_entry._child.left()[this->_index].size();
      }
      return 1+this->_entry._child.right()[this->_index-this->_entry._child.left().size()].size();
    }
    return 0;
  }

  inline const char* operator[](unsigned int i) {
    if(this->_index < this->_entry.size()) {
      if(i == 0) {
        return this->_entry.name();
      }
      if(this->_index < this->_entry._child.left().size()) {
        return this->_entry._child.left()[this->_index][i-1];
      }
      return this->_entry._child.right()[this->_index-this->_entry._child.left().size()][i-1];
    }
    return 0;
  }
};

}
}

#endif//AVERSIVE_FS_PAIR_DIR_ENTRY_HPP
