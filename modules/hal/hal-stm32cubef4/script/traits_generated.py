MAX_PORTS = 26
MAX_OFFSET = 16

MAX_TIMERS = 20
MAX_CHANNELS = 6

MAX_UARTS = 10

GPIO_TIMER_AFS = {
    1 : 1,
    2 : 1,
    
    3 : 2,
    4 : 2,
    5 : 2,
    
    8  : 3,
    9  : 3,
    10 : 3,
    11 : 3,
    
    12 : 9,
    13 : 9,
    14 : 9,
    
    6 : None,
    7 : None,
}

GPIO_UART_AFS = {
    1 : "GPIO_AF7_USART1",
    2 : "GPIO_AF7_USART2",
    3 : "GPIO_AF7_USART3",
    4 : "GPIO_AF8_UART4",
    5 : "GPIO_AF8_UART5",
    6 : "GPIO_AF8_USART6",
    7 : "GPIO_AF8_UART7",
    8 : "GPIO_AF8_UART8",
}

# Common
print("#define MACRO_APPLY_ARGS(macro, args...) macro(args)")
print("")
print("")

# GPIO Exists
for p in range(0, MAX_PORTS):
    l = chr(ord('A') + p)
    p = str(p)
    print("#ifdef GPIO"+l)
    print("  #define AVERSIVE_HAL_STM32CUBEF4_GPIO"+l+"_EXISTS(txt_if, txt_else) txt_if")
    print("#else")
    print("  #define AVERSIVE_HAL_STM32CUBEF4_GPIO"+l+"_EXISTS(txt_if, txt_else) txt_else")
    print("#endif")
    print("")
print("")

# GPIO Apply loop
print("#define AVERSIVE_APPLY_PORTS(macro, args...) \\")
for p in range(0, MAX_PORTS):
    l = chr(ord('A') + p)
    p = str(p)
    print("  macro("+l+", "+p+", args) \\")
print("")

print("#define AVERSIVE_APPLY_PINS(macro, args...) \\")
for o in range(0, MAX_OFFSET):
    o = str(o)
    print("  macro("+o+", args) \\")
print("")

print("")
    
# TIMER Exists
for t in range(0, MAX_TIMERS):
    t = str(t)
    print("#ifdef TIM"+t)
    print("  #define AVERSIVE_HAL_STM32CUBEF4_TIMER"+t+"_EXISTS(txt_if, txt_else) txt_if")
    print("#else")
    print("  #define AVERSIVE_HAL_STM32CUBEF4_TIMER"+t+"_EXISTS(txt_if, txt_else) txt_else")
    print("#endif")
    print("")
print("")

for t in range(0, MAX_TIMERS):
    for c in range(0, MAX_CHANNELS):
        t = str(t)
        c = str(c)
        print("#if AVERSVE_IS_TIMER_CHANNEL("+t+", "+c+")")
        print("  #define AVERSIVE_HAL_STM32CUBEF4_TIMER"+t+"_CH"+c+"_EXISTS(txt_if, txt_else) txt_if")
        print("#else")
        print("  #define AVERSIVE_HAL_STM32CUBEF4_TIMER"+t+"_CH"+c+"_EXISTS(txt_if, txt_else) txt_else")
        print("#endif")
        print("")
print("")

# TIMER Apply loop
print("#define AVERSIVE_APPLY_TIMERS(macro, args...) \\")
for t in range(0, MAX_TIMERS):
    t = str(t)
    print("  macro("+t+", args) \\")
print("")

print("#define AVERSIVE_APPLY_CHANNELS(macro, args...) \\")
for c in range(0, MAX_CHANNELS):
    c = str(c)
    print("  macro("+c+", args) \\")
print("")

print("")
    
# GPIO Alternate Functions
# print("static constexpr inline uint32_t cube_gpio_timer_af(int timer) {")
# print("  return")
# for t in GPIO_TIMER_AFS:
#     if GPIO_TIMER_AFS[t] != None:
#         print("    (timer == "+str(t)+") ? GPIO_AF"+str(GPIO_TIMER_AFS[t])+"_TIM"+str(t)+" :")
# print("    -1;")
# print("}")
# print("")

# UART Exists
for u in range(0, MAX_UARTS):
    u = str(u)
    print("#if defined UART"+u)
    print("  #define AVERSIVE_CUBE_UART"+u+"_TYPE UART")
    print("  #define AVERSIVE_HAL_STM32CUBEF4_UART"+u+"_EXISTS(txt_if, txt_else) txt_if")
    print("#elif defined USART"+u)
    print("  #define AVERSIVE_CUBE_UART"+u+"_TYPE USART")
    print("  #define AVERSIVE_HAL_STM32CUBEF4_UART"+u+"_EXISTS(txt_if, txt_else) txt_if")
    print("#else")
    print("  #define AVERSIVE_CUBE_UART"+u+"_TYPE UNDEFINED")
    print("  #define AVERSIVE_HAL_STM32CUBEF4_UART"+u+"_EXISTS(txt_if, txt_else) txt_else")
    print("#endif")
    print("")
print("")

# UART Apply loop
print("#define AVERSIVE_APPLY_UARTS(macro, args...) \\")
for u in range(0, MAX_UARTS):
    u = str(u)
    print("  MACRO_APPLY_ARGS(macro, AVERSIVE_CUBE_UART"+u+"_TYPE, "+u+", args) \\")
print("")
print("")

# GPIO Alternate Functions
# print("static constexpr inline uint32_t cube_gpio_uart_af(int uart) {")
# print("  return")
# for u in GPIO_UART_AFS:
#     if GPIO_UART_AFS[u] != None:
#         print("#ifdef "+str(GPIO_UART_AFS[u]))
#         print("    (uart == "+str(u)+") ? "+str(GPIO_UART_AFS[u])+" :")
#         print("#endif")
# print("    -1;")
# print("}")
# print("")
