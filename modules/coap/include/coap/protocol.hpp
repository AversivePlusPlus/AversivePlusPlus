#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

namespace coap {

//http://tools.ietf.org/html/rfc7252#section-5.10
//http://tools.ietf.org/html/rfc7252#section-12.2
enum class OptionNum {
  IF_MATCH       = 1,
  URI_HOST       = 3,
  ETAG           = 4,
  IF_NONE_MATCH  = 5,
  OBSERVE        = 6,
  URI_PORT       = 7,
  LOCATION_PATH  = 8,
  URI_PATH       = 11,
  CONTENT_FORMAT = 12,
  MAX_AGE        = 14,
  URI_QUERY      = 15,
  ACCEPT         = 17,
  LOCATION_QUERY = 20,
  PROXY_URI      = 35,
  PROXY_SCHEME   = 39
};

//http://tools.ietf.org/html/rfc7252#section-12.1.1
enum class MessageType {
  CON    = 0,
  NONCON = 1,
  ACK    = 2,
  RESET  = 3
};

//http://tools.ietf.org/html/rfc7252#section-5.2
//http://tools.ietf.org/html/rfc7252#section-12.1.1
//http://tools.ietf.org/html/rfc7252#section-12.1.2
using code_t = unsigned char;

static constexpr inline code_t make_code(code_t cls, code_t det) {
  return (cls << 5) | det;
}

enum class MethodCode : code_t {
  GET    = make_code(0, 1),
  POST   = make_code(0, 2),
  PUT    = make_code(0, 3),
  DELETE = make_code(0, 4),
};

enum class ResponseCode : code_t {
  CREATED                    = make_code(2, 1),
  DELETED                    = make_code(2, 2),
  VALID                      = make_code(2, 3),
  CHANGED                    = make_code(2, 4),
  CONTENT                    = make_code(2, 5),

  BAD_REQUEST                = make_code(4, 0),
  UNAUTHORIZED               = make_code(4, 1),
  BAD_OPTION                 = make_code(4, 2),
  FORBIDDEN                  = make_code(4, 3),
  NOT_FOUND                  = make_code(4, 4),
  METHOD_NOT_ALLOWED         = make_code(4, 5),
  NOT_ACCEPTABLE             = make_code(4, 6),
  PRECONDITION_FAILED        = make_code(4, 12),
  REQUEST_ENTRY_TOO_LARGE    = make_code(4, 13),
  UNSUPPORTED_CONTENT_FORMAT = make_code(4, 15),

  INTERNAL_SERVER_ERROR      = make_code(5, 0),
  NOT_IMPLEMENTED            = make_code(5, 1),
  BAD_GATEWAY                = make_code(5, 2),
  SERVICE_UNAVAILABLE        = make_code(5, 3),
  GATEWAY_TIMEOUT            = make_code(5, 4),
  PROXY_NOT_SUPPORTED        = make_code(5, 5),
};

//http://tools.ietf.org/html/rfc7252#section-12.3
enum class ContentType {
  TEXT_PLAIN                = 0,
  APPLICATION_LINKFORMAT    = 40,
  APPLICATION_XML           = 41,
  APPLICATION_OCTECT_STREAM = 42,
  APPLICATION_EXI           = 47,
  APPLICATION_JSON          = 50,
};

////////////////////////////////////////////////////////////////
// Functions return codes

enum class Error {
  NONE,
  BUFFER_TOO_SMALL,
  UNSUPPORTED,
};

}

#endif//PROTOCOL_HPP
