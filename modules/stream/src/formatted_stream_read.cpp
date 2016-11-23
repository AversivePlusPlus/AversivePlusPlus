#include <stream/formatted_stream.hpp>

namespace Stream {
/*
  static void clearBlank(void* s, FormattedStreamDecoratorBase::ReadFunc next_char, FormattedStreamDecoratorBase::ReadFunc get_char) {
    char c = next_char(s);
    while(c == ' ' || c == '\0' || c == '\n' || c == '\r' || c == '\t') {
        get_char(s);
        c = next_char(s);
      }
  }

  //! \fixme Last character is overwritten by \0 when the user's buffer is fulfilled.
  void FormattedStreamDecoratorBase::read(char* str, void* s, FormattedStreamDecoratorBase::ReadFunc next_char, FormattedStreamDecoratorBase::ReadFunc get_char) {
    clearBlank(s, next_char, get_char);
    bool keep = true;
    while(keep) {
        char c = get_char(s);
        *str = c;
        if(_sep == WORD && (c == ' ' || c == '\t')) {
            keep = false;
          }
        else if(c == '\r' || c == '\n' || c == '\0') {
            *str = '\n';
            keep = false;
          }
        str++;
      }
    *(str-1) = '\0';
  }

  ////////////////////////////////////////
  // Formatted Read

  template<bool SIGNED = true, typename T>
  void basic_formatted_integer_read(T& val, void* s, FormattedStreamDecoratorBase::ReadFunc next_char, FormattedStreamDecoratorBase::ReadFunc get_char) {
    clearBlank(s, next_char, get_char);
    val = 0;

    char c = 0;
    bool neg = false;
    c = next_char(s);

    if(SIGNED && c == '-') {
        neg = true;
        get_char(s);
        c = next_char(s);
      }

    while(c >= '0' && c <= '9') {
        get_char(s);
        val = val * 10 + ((T) (c - '0'));
        c = next_char(s);
      }
    get_char(s);

    if(neg) {
        val = -val;
      }
  }

  void FormattedStreamDecoratorBase::read(s8& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(s16& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(s32& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(s64& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(u8& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read<false>(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(u16& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read<false>(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(u32& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read<false>(val, s, next_char, get_char);
  }

  void FormattedStreamDecoratorBase::read(u64& val, void* s, ReadFunc next_char, ReadFunc get_char) {
    basic_formatted_integer_read<false>(val, s, next_char, get_char);
  }
*/
}
