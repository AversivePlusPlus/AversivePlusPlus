#ifndef COAP_PARSER_HPP
#define COAP_PARSER_HPP

#include "../ext/parser.hpp"
#include "handler.hpp"

namespace coap {

struct Buffer {
  uint8_t *data;
  size_t len;
};

struct ReadOnlyBuffer {
  const uint8_t *data;
  size_t len;
};

struct ParserInput {
  ReadOnlyBuffer req;
  Buffer res;
};

struct ParserOutput {
  ReturnCode rc;
  ReadOnlyBuffer res;
};

template<class Handler>
class Parser :
    public ext::Parser<ParserOutput, ParserInput, Handler> {
private:
  using Parent = ext::Parser<ParserOutput, ParserInput, Handler>;

public:
  Parser(Handler& handler)
    : Parent(handler) {
  }

  inline ParserOutput parse(ParserInput input) {
    PacketReader req(input.req.data, input.req.len);
    PacketBuilder res(input.res.data, input.res.len);
    Handler& h = Parent::_handler;

    ReturnCode rc = h.handle(req, res);

    if(rc == ReturnCode::ERROR) {
      res.makeResponse(req, ResponseCode::INTERNAL_SERVER_ERROR);
      rc = ReturnCode::SEND;
    }
    else if(rc == ReturnCode::NEXT_HANDLER) {
      res.makeResponse(req, ResponseCode::NOT_FOUND);
      rc = ReturnCode::SEND;
    }

    return ParserOutput{rc, ReadOnlyBuffer{res.getBuffer(), res.getSize()}};
  }

};

}


#endif//COAP_PARSER_HPP
