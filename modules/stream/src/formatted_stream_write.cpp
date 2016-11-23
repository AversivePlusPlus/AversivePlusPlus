#include <stream/formatted_stream.hpp>

namespace Stream {
/*
  const u16 MAX_BUFF = 32;


  //! \fixme Last character is overwritten by \0 when the user's buffer is fulfilled.
  void FormattedStreamDecoratorBase::write(const char* str, void* s, FormattedStreamDecoratorBase::WriteFunc put_char) {
    while(*str != 0) {
        put_char(s, *str++);
      }
  }

  ////////////////////////////////////////
  // Formatted Write

  template<bool SIGNED = true, typename T>
  inline void basic_formatted_integer_write(T val, void* s, FormattedStreamDecoratorBase::WriteFunc put_char) {
    char str[MAX_BUFF] = {0};
    bool _neg = false;

    // Initialize string
    char* ptr = str + MAX_BUFF;
    *(--ptr) = '\0';

    // Parsing sign and digits
    if(SIGNED && val < 0) {
        val = -val;
        _neg = true;
      }

    while(0 < val && str < ptr) {
        *(--ptr) = '0' + (val % 10);
        val /= 10;
      }

    if(SIGNED && _neg) {
        *(--ptr) = '-';
      }

    // If no digits found
    if(*ptr == '\0') {
        *(--ptr) = '0';
      }

    // Send
    for(; (ptr - str) < MAX_BUFF ; ptr++) {
        put_char(s, *ptr);
      }
  }

  void FormattedStreamDecoratorBase::write(const s8& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const s16& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const s32& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const s64& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const u8& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write<false>(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const u16& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write<false>(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const u32& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write<false>(val, s, put_char);
  }

  void FormattedStreamDecoratorBase::write(const u64& val, void* s, WriteFunc put_char) {
    basic_formatted_integer_write<false>(val, s, put_char);
  }
*/
}
