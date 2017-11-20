extern "C" void __init(void);

extern "C" __attribute__((naked,section(".init0"))) void _init0(void) {
}

extern "C" __attribute__((naked,section(".init2"))) void _init2(void) {
  asm("eor     r1, r1");
  asm("out     0x3f, r1");
  asm("ldi     r28, 0xFF");
  asm("ldi     r29, 0x21");
  asm("out     0x3e, r29");
  asm("out     0x3d, r28");
  asm("ldi     r16, 0x00");
  asm("out     0x3c, r16");
}

extern "C" __attribute__((naked,section(".init9"))) void _init9(void) {
  asm("call    main");
  asm("jmp     _exit");
}

#pragma weak __init = _init0
