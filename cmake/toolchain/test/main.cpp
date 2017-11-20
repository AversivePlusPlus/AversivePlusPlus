int main(int, char**) {
  return 0;
}

extern "C" void _exit(void) __attribute__((weak));
extern "C" void _exit(void) {}
