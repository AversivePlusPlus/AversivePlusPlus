#ifndef AVERSIVE_FS_FILE_HPP
#define AVERSIVE_FS_FILE_HPP

#include "invalid.hpp"

#include <stream/input_stream.hpp>
#include <stream/output_stream.hpp>

namespace Aversive {
namespace fs {

class File :
    ::Aversive::Stream::InputStream<char, unsigned int>,
    ::Aversive::Stream::OutputStream<char, unsigned int> {
public:
  using ElementType = char;
  using SizeType = unsigned int;

private:
  void* _ostream;
  void (*_put)(void*, ElementType);
  SizeType (*_write)(void*, const ElementType*, SizeType);
  SizeType (*_writable)(void*);

  void* _istream;
  ElementType (*_get)(void*);
  SizeType (*_read)(void*, ElementType*, SizeType);
  SizeType (*_readable)(void*);

public:
  File(void)
    : _ostream(0), _put(0), _write(0), _writable(0),
      _istream(0), _get(0), _read(0), _readable(0) {
  }

  template<class Stream>
  File(Stream& stream)
    : _ostream(&stream),
      _put([](void* s, ElementType e) { ((Stream*)s)->put(e); }),
      _write([](void* s, const ElementType* data, SizeType size) { return (SizeType)(((Stream*)s)->write(data, size)); }),
      _writable([](void* s) { return (SizeType)(((Stream*)s)->writable()); }),
      _istream(&stream),
      _get([](void* s) { return (ElementType)(((Stream*)s)->get()); }),
      _read([](void* s, ElementType* data, SizeType size) { return (SizeType)(((Stream*)s)->read(data, size)); }),
      _readable([](void* s) { return (SizeType)(((Stream*)s)->readable()); }) {
  }

  template<class OutputStream, class InputStream>
  File(OutputStream& ostream, InputStream& istream)
    : _ostream(&ostream),
      _put([](void* s, ElementType e) { ((OutputStream*)s)->put(e); }),
      _write([](void* s, const ElementType* data, SizeType size) { return (SizeType)(((OutputStream*)s)->write(data, size)); }),
      _writable([](void* s) { return (SizeType)(((OutputStream*)s)->writable()); }),
      _istream(&istream),
      _get([](void* s) { return (ElementType)(((InputStream*)s)->get()); }),
      _read([](void* s, ElementType* data, SizeType size) { return (SizeType)(((InputStream*)s)->read(data, size)); }),
      _readable([](void* s) { return (SizeType)(((InputStream*)s)->readable()); }) {
  }

public:
  inline void put(ElementType e) {
    if(_ostream == 0 || _put == 0) return;
    return _put(_ostream, e);
  }

  inline SizeType write(const ElementType* data, SizeType length) {
    if(_ostream == 0 || _write == 0) return 0;
    return _write(_ostream, data, length);
  }

  inline SizeType writable(void) {
    if(_ostream == 0 || _writable == 0) return 0;
    return _writable(_ostream);
  }

public:
  inline ElementType get(void) {
    if(_istream == 0 || _get == 0) return 0;
    return _get(_istream);
  }

  inline SizeType read(ElementType* data, SizeType length) {
    if(_istream == 0 || _read == 0) return 0;
    return _read(_istream, data, length);
  }

  inline SizeType readable(void) {
    if(_istream == 0 || _readable == 0) return 0;
    return _readable(_istream);
  }

public:
  bool operator==(const decltype(INVALID_FILE)&) const {
    return _istream == 0 && _ostream == 0;
  }
};

}
}

#endif//AVERSIVE_FS_FILE_HPP
