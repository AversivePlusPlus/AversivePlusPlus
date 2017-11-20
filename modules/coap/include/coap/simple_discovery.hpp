#ifndef SIMPLE_DISCOVERY_HANDLER_HPP
#define SIMPLE_DISCOVERY_HANDLER_HPP

#include "handler.hpp"
#include "chain_handler.hpp"

#include <string.h>

namespace coap {

template<class Handler>
class SimpleDiscoveryInputStream : ext::InputStream {
public:
  size_t read(uint8_t* buffer, size_t size) {
    return 0;
  }
};

template<class Handler>
inline SimpleDiscoveryInputStream<Handler>& discovery(Handler& handler) {
  static_assert(sizeof(SimpleDiscoveryInputStream<Handler>) == sizeof(Handler), "SimpleDiscoveryInputStream cannot define additional members");
  return *(SimpleDiscoveryInputStream<Handler>*)&handler;
}

template<class DerivedHandler>
class SimpleDiscoveryHandler : public Handler {
protected:
  DerivedHandler& _handler;

public:
  SimpleDiscoveryHandler(DerivedHandler& handler)
    : _handler(handler) {
  }

  inline ReturnCode handle(const PacketReader& req, PacketBuilder& res) {
    enum class State { INIT, WELLKNOWN, CORE };
    State state = State::INIT;
    for(auto it = req.getOptionsBegin() ; it != req.getOptionsEnd() ; it++) {
      auto opt = *it;

      if(opt.getNum() == OptionNum::URI_PATH) {
        if(state == State::INIT) {
          if(strncmp(".well-known", (const char*)opt.getValue(), opt.getLength()) == 0) {
            state = State::WELLKNOWN;
          }
          else {
            return ReturnCode::NEXT_HANDLER;
          }
        }
        else if(state == State::WELLKNOWN) {
          if(strncmp("core", (const char*)opt.getValue(), opt.getLength()) == 0) {
            state = State::CORE;
          }
          else {
            return ReturnCode::NEXT_HANDLER;
          }
        }
        else {
            return ReturnCode::NEXT_HANDLER;
        }
      }
    }

    if(state == State::CORE) {
      if(req.getMethodCode() == MethodCode::GET) {
        if(res.makeResponse(req, ResponseCode::CONTENT, ContentType::APPLICATION_LINKFORMAT, discovery(*this)) == Error::NONE) {
          return ReturnCode::SEND;
        }
        else {
          return ReturnCode::ERROR;
        }
      }
    }

    return ReturnCode::NEXT_HANDLER;
  }
};

template<class Handler>
class SimpleDiscoveryInputStream<SimpleDiscoveryHandler<Handler>> :
    SimpleDiscoveryHandler<Handler> {
public:
  inline size_t read(uint8_t* buffer, size_t max_size) {
    uint8_t* cur = buffer;

    size_t read = discovery(this->_handler).read(buffer, max_size);
    cur += read;
    max_size -= read;

    return (size_t)(cur - buffer);
  }
};

template<class First, class Second>
class SimpleDiscoveryInputStream<ChainHandler<First, Second>> :
    ChainHandler<First, Second> {
public:
  inline size_t read(uint8_t* buffer, size_t max_size) {
    uint8_t* cur = buffer;

    {
      size_t read = discovery(this->_first).read(buffer, max_size);
      cur += read;
      max_size -= read;
    }

    {
      size_t read = discovery(this->_second).read(cur, max_size);
      cur += read;
      max_size -= read;
    }

    return (size_t)(cur - buffer);
  }
};


}

#endif//SIMPLE_DISCOVERY_HANDLER_HPP
