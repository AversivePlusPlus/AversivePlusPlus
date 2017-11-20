#ifndef AVERSIVE_FS_INVALID_HPP
#define AVERSIVE_FS_INVALID_HPP

namespace Aversive {
namespace fs {

struct InvalidFileType {};
static constexpr InvalidFileType INVALID_FILE = {};

template<class File>
static inline bool operator == (const InvalidFileType& i, const File& f) {
  return (f == i);
}

template<class File>
static inline bool operator != (const File& f, const InvalidFileType& i) {
  return !(f == i);
}

template<class File>
static inline bool operator != (const InvalidFileType& i, const File& f) {
  return !(f == i);
}

}
}

#endif//AVERSIVE_FS_INVALID_HPP
