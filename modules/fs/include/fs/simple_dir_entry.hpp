#ifndef AVERSIVE_FS_SIMPLE_DIR_ENTRY_HPP
#define AVERSIVE_FS_SIMPLE_DIR_ENTRY_HPP

#include "entry.hpp"
#include "filesystem.hpp"
#include "path_list.hpp"

namespace Aversive {
namespace fs {

template<class Child>
class SimpleDirEntry :
    public Entry,
    public FileSystem,
    public PathList<SimpleDirEntry<Child>> {
protected:
  friend class Path<SimpleDirEntry>;

protected:
  Child& _child;

public:
  SimpleDirEntry(const char* name, Child& child)
    : Entry(name), _child(child) {
  }

  File open(const char* p) {
    if(strncmp(p+1, this->_name, strlen(this->_name)) == 0) {
      return _child.open(p+1+strlen(this->_name));
    }
    return File();
  }

  unsigned int size(void) {
    return _child.size();
  }
};

template<class Child>
class Path<SimpleDirEntry<Child>> : public BasePath<SimpleDirEntry<Child>> {
public:
  inline Path(SimpleDirEntry<Child>& entry, unsigned int index)
    : BasePath<SimpleDirEntry<Child>>(entry, index) {
  }

  inline unsigned int size(void) const {
    if(this->_index < this->_entry.size()) {
      return 1+this->_entry._child[this->_index].size();
    }
    return 0;
  }

  inline const char* operator[](unsigned int i) {
    if(this->_index < this->_entry.size()) {
      if(i == 0) {
        return this->_entry.name();
      }
      return this->_entry._child[this->_index][i-1];
    }
    return 0;
  }
};

}
}

#endif//AVERSIVE_FS_SIMPLE_DIR_ENTRY_HPP
