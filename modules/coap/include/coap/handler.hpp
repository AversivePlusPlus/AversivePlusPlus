#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "packet_reader.hpp"
#include "packet_writer.hpp"

namespace coap {

enum class ReturnCode {
  SEND,
  NOSEND,
  NEXT_HANDLER,
  ERROR,
};

struct Handler {
  inline ReturnCode handle(const PacketReader& req, PacketBuilder& res);
};

}

#endif//HANDLER_HPP
