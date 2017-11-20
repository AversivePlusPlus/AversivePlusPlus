#include <coap/coap.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#include <iostream>
#include <sstream>
using namespace std;

class DummyHandler {
protected:
  const char* _prefix;

public:
  DummyHandler(const char* prefix)
    : _prefix(prefix) {
  }

  inline coap::ReturnCode handle(const coap::PacketReader& req, coap::PacketBuilder& res) {
    for(auto it = req.getOptionsBegin() ; it != req.getOptionsEnd() ; it++) {
      auto opt = *it;
      if(opt.getNum() == coap::OptionNum::URI_PATH &&
         strncmp(_prefix, (const char*)opt.getValue(), opt.getLength()) == 0) {
        if(res.makeResponse(req, coap::ResponseCode::CONTENT, coap::ContentType::TEXT_PLAIN, (const uint8_t*)_prefix, strlen(_prefix)) == coap::Error::NONE) {
          return coap::ReturnCode::SEND;
        }
      }
    }

    return coap::ReturnCode::NEXT_HANDLER;
  }
};

namespace coap {
template<>
class SimpleDiscoveryInputStream<DummyHandler> : DummyHandler {
public:
  size_t read(uint8_t* buffer, size_t size) {
    const char* dirs[] = { "test", "miew", "lool" };
    uint8_t* cur = buffer;

    for(size_t i = 0 ; i < 3 ; i++) {
      stringstream ss;
      ss << "</" << this->_prefix << "/" << dirs[i];
      ss << ">;ct=0,";

      if(ss.str().length() < size - (size_t)(cur-buffer)) {
        memcpy(cur, ss.str().c_str(), ss.str().length());
        cur += ss.str().length();
      }
      else {
        return (size_t)(cur - buffer);
      }
    }

    return (size_t)(cur - buffer);
  }
};
}

void dump(const coap::PacketReader& pack) {
  cout << "version : " << (int)pack.getVersion() << endl;
  cout << "type : " << (int)pack.getType() << endl;
  cout << "code : " << (int)pack.getCode() << endl;
  cout << "id : " << (int)pack.getID() << endl;

  cout << "token : ";
  if(pack.getTokenLength()) {
    cout.write((const char*)pack.getToken(), pack.getTokenLength());
  }
  else {
    cout << "(empty)";
  }
  cout << endl;

  cout << "options {" << endl;
  for(auto it = pack.getOptionsBegin() ; it != pack.getOptionsEnd() ; it++) {
    auto& opt = *it;
    cout << "\t" << (int)opt.getNum() << " => ";
    if(opt.getLength()) {
      if(opt.getNum() == coap::OptionNum::CONTENT_FORMAT) {
        for(size_t i = 0 ; i < opt.getLength() ; i++) {
          cout << (int)opt.getValue()[i] << " ";
        }
      }
      else {
        cout.write((const char*)opt.getValue(), opt.getLength());
      }
    }
    else {
      cout << "(empty)";
    }
    cout << endl;
  }
  cout << "}" << endl;

  cout << "payload : ";
  if(pack.getPayloadLength()) {
    cout.write((const char*)pack.getPayload(), pack.getPayloadLength());
  }
  else {
    cout << "(empty)";
  }
  cout << endl;
}

#define PORT 5683

int main(int, char**) {
  DummyHandler dummy1("dummy1");
  DummyHandler dummy2("dummy2");
  coap::ChainHandler<DummyHandler, DummyHandler> dummy(dummy1, dummy2);
  coap::SimpleDiscoveryHandler<decltype(dummy)> discov(dummy);
  coap::ChainHandler<decltype(discov), decltype(dummy)> handler(discov, dummy);
  coap::Parser<decltype(handler)> parser(handler);
  uint8_t buf_raw[1024];
  coap::Buffer buf {buf_raw,sizeof(buf_raw)};

  int fd;

#ifdef IPV6
  struct sockaddr_in6 servaddr, cliaddr;
  fd = socket(AF_INET6,SOCK_DGRAM,0);
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin6_family = AF_INET6;
  servaddr.sin6_addr = in6addr_any;
  servaddr.sin6_port = htons(PORT);
#else /* IPV6 */
  struct sockaddr_in servaddr, cliaddr;
  fd = socket(AF_INET,SOCK_DGRAM,0);
  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
#endif /* IPV6 */

  bind(fd,(struct sockaddr *)&servaddr, sizeof(servaddr));

  while(1) {
    size_t n;
    socklen_t len = sizeof(cliaddr);

    n = recvfrom(fd, buf.data, buf.len, 0, (struct sockaddr *)&cliaddr, &len);

    {
      cout << endl << "--- REQUEST ---" << endl;
      coap::PacketReader pack(buf.data, n);
      dump(pack);
    }

    coap::ParserOutput out = parser.parse(coap::ParserInput{{buf.data, n}, {buf.data, buf.len}});

    if(out.rc == coap::ReturnCode::SEND) {
      cout << endl << "--- RESPONSE ---" << endl;
      coap::PacketReader pack(out.res.data, out.res.len);
      dump(pack);
      sendto(fd, out.res.data, out.res.len, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }
    else {
      cout << endl << "--- ERROR ---" << endl;
    }
  }

  return 0;
}
