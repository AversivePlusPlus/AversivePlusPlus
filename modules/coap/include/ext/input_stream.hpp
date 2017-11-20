#ifndef COAP_EXT_INPUT_STREAM_HPP
#define COAP_EXT_INPUT_STREAM_HPP

#include <stdint.h>
#include <stddef.h>

namespace coap {
namespace ext {

class InputStream {
public:
  size_t read(uint8_t* buffer, size_t size);
};

}
}

#endif//COAP_EXT_INPUT_STREAM_HPP
