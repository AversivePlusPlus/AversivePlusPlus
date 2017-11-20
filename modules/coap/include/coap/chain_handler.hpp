#ifndef CHAIN_HANDLER_HPP
#define CHAIN_HANDLER_HPP

#include "handler.hpp"

namespace coap {

template<class First, class Second>
class ChainHandler : public Handler {

protected:
  First& _first;
  Second& _second;

public:
  ChainHandler(First& first, Second& second)
    : _first(first), _second(second) {
  }

  inline ReturnCode handle(const PacketReader& req, PacketBuilder& res) {
    {
      ReturnCode rc = _first.handle(req, res);
      if(rc != ReturnCode::NEXT_HANDLER) {
        return rc;
      }
    }

    {
      ReturnCode rc = _second.handle(req, res);
      if(rc != ReturnCode::NEXT_HANDLER) {
        return rc;
      }
    }

    return ReturnCode::NEXT_HANDLER;
  }
};

}

#endif//CHAIN_HANDLER_HPP
