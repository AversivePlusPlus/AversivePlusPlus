#ifndef COAP_EXT_PARSER_HPP
#define COAP_EXT_PARSER_HPP

namespace coap {
namespace ext {

template<typename Input, typename Output, typename Handler>
class Parser {
protected:
  Handler& _handler;

public:
  inline Parser(Handler& handler)
    : _handler(handler) {
  }

  inline Output parse(Input input);
};

}
}

#endif//COAP_EXT_PARSER_HPP
