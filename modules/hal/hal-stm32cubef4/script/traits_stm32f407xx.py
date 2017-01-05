TIMER_INTERRUPTS = {
    "TIM1_UP_TIM10_IRQ" : [[1, 10],[]],
    "TIM1_UP_IRQ" : [[1], [10]],
    "TIM2_IRQ" : [[2],[]],
    "TIM3_IRQ" : [[3],[]],
    "TIM4_IRQ" : [[4],[]],
    "TIM5_IRQ" : [[5],[]],
    "TIM6_DAC_IRQ" : [[6],[]],
    "TIM7_IRQ" : [[7],[]],
    "TIM8_UP_TIM13_IRQ" : [[8, 13],[]],
    "TIM1_BRK_TIM9_IRQ" : [[9],[]],
    "TIM1_TRG_COM_TIM11_IRQ" : [[11],[]],
    "TIM8_BRK_TIM12_IRQ" : [[12],[]],
    "TIM8_TRG_COM_TIM14_IRQ" : [[14],[]],
}

TIMER_CHANNELS = {
    1 : [1, 2, 3, 4],
    2 : [1, 2, 3, 4],
    3 : [1, 2, 3, 4],
    4 : [1, 2, 3, 4],
    5 : [1, 2, 3, 4],
    8 : [1, 2, 3, 4],
    9 : [1, 2],
    10 : [1],
    11 : [1],
    12 : [1, 2],
    13 : [1],
    14 : [1]
}

print("#ifndef HAL_STM32CUBEF4_TRAITS_HPP")
print("#error \"This file must not be included directly, include traits.hpp instead\"")
print("#endif")
print("")

print("#define AVERSVE_IS_TIMER_CHANNEL(timer, channel) \\")
print("  ( \\")
for t in TIMER_CHANNELS:
    print("    ((timer == "+str(t)+") && ( \\")
    for c in TIMER_CHANNELS[t]:
        print("      (channel == "+str(c)+") || \\")
    print("      0 )) || \\")
print("  0 )")
print("")


print("static constexpr inline IRQn_Type get_timer_irq(int timer) {")
print("  return")
for i in TIMER_INTERRUPTS:
    interrupt = TIMER_INTERRUPTS[i]
    conds = []
    for t in interrupt[0]:
        conds.append("(defined TIM"+str(t)+")")
    for t in interrupt[1]:
        conds.append("(not defined TIM"+str(t)+")")
    for t in interrupt[0]:
        t = str(t)
        print("#if " + " and ".join(conds))
        print("    (timer == "+t+") ? "+i+"n :")
        print("#endif")
print("    UsageFault_IRQn;")
print("}")
print("")

