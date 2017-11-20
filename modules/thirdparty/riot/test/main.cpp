#include <stdio.h>

#include <board.h>
#include <stream/riot/uart_stream.hpp>
#include <stream/formatted_stream.hpp>

#include <shell.h>

using namespace Aversive::Base;
using namespace Aversive::Stream;

RIOT::UARTStream<> uart(1, 1000000);
FormattedStreamDecorator<decltype(uart)>& io = formatted(uart);

int serial_cmd(int argc, char** argv) {
  if(argc <= 1) {
    io << "hello !" << "\n";
  }
  
  io << (const char*)argv[1] << "\n";
  return 0;
}

static const shell_command_t shell_commands[] = {
    { "serial", "send data over serial", serial_cmd },
    { NULL, NULL, NULL }
};

int main(void) {
  /* start shell */
  puts("All up, running the shell now");
  char line_buf[SHELL_DEFAULT_BUFSIZE];
  shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
  
  return 0;
}
