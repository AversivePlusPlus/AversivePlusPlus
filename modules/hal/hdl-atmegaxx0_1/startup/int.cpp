#include <hdl/avr/mxx0_1/int.hpp>

#define XJMP(lbl) "jmp "#lbl

#define VECTORS __attribute__((naked,section(".vectors")))

extern "C" void __aversive_vectors(void) VECTORS;

void __aversive_vectors(void) {
  asm(XJMP(__init));                                          //  0
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh0EE9interruptEv));  //  1
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh1EE9interruptEv));  //  2
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh2EE9interruptEv));  //  3
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh3EE9interruptEv));  //  4
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh4EE9interruptEv));  //  5
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh5EE9interruptEv));  //  6
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh6EE9interruptEv));  //  7
  asm(XJMP(_ZN3HDL10Interrupts8ExternalILh7EE9interruptEv));  //  8
  asm(XJMP(_ZN3HDL10Interrupts9PinChangeILh0EE9interruptEv)); //  9
  asm(XJMP(_ZN3HDL10Interrupts9PinChangeILh1EE9interruptEv)); // 10
  asm(XJMP(_ZN3HDL10Interrupts9PinChangeILh2EE9interruptEv)); // 11
  asm(XJMP(_default_handler));                                // 12
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh2EE2OCILh0EE4compEv)); // 13
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh2EE2OCILh1EE4compEv)); // 14
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh2EE3ovfEv));           // 15
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh1EE4captEv));          // 16
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh1EE2OCILh0EE4compEv)); // 17
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh1EE2OCILh1EE4compEv)); // 18
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh1EE2OCILh2EE4compEv)); // 19
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh1EE3ovfEv));           // 20
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh0EE2OCILh0EE4compEv)); // 21
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh0EE2OCILh1EE4compEv)); // 22
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh0EE3ovfEv));           // 23
  asm(XJMP(_default_handler));                                // 24
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh0EE2rxEv));             // 25
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh0EE2dreEv));            // 26
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh0EE2txEv));             // 27
  asm(XJMP(_default_handler));                                // 28
  asm(XJMP(_default_handler));                                // 29
  asm(XJMP(_default_handler));                                // 30
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh3EE4captEv));          // 31
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh3EE2OCILh0EE4compEv)); // 32
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh3EE2OCILh1EE4compEv)); // 33
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh3EE2OCILh2EE4compEv)); // 34
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh3EE3ovfEv));           // 35
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh1EE2rxEv));             // 36
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh1EE2dreEv));            // 37
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh1EE2txEv));             // 38
  asm(XJMP(_default_handler));                                // 39
  asm(XJMP(_default_handler));                                // 40
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh4EE4captEv));          // 41
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh4EE2OCILh0EE4compEv)); // 42
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh4EE2OCILh1EE4compEv)); // 43
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh4EE2OCILh2EE4compEv)); // 44
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh4EE3ovfEv));           // 45
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh5EE4captEv));          // 46
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh5EE2OCILh0EE4compEv)); // 47
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh5EE2OCILh1EE4compEv)); // 48
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh5EE2OCILh2EE4compEv)); // 49
  asm(XJMP(_ZN3HDL10Interrupts5TIMERILh5EE3ovfEv));            // 50
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh2EE2rxEv));             // 51
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh2EE2dreEv));            // 52
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh2EE2txEv));             // 53
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh3EE2rxEv));             // 54
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh3EE2dreEv));            // 55
  asm(XJMP(_ZN3HDL10Interrupts4UARTILh3EE2txEv));             // 56
};

#include "int_default.hpp"

extern "C" __attribute__((naked)) void _default_handler(void) {
  while(1);
}
