TIMER_INTERRUPTS = {
    "TIM1_UP_TIM10_IRQHandler" : [[1, 10],[]],
    "TIM1_UP_IRQHandler" : [[1], [10]],
    "TIM2_IRQHandler" : [[2],[]],
    "TIM3_IRQHandler" : [[3],[]],
    "TIM4_IRQHandler" : [[4],[]],
    "TIM5_IRQHandler" : [[5],[]],
    "TIM6_DAC_IRQHandler" : [[6],[]],
    "TIM7_IRQHandler" : [[7],[]],
    "TIM8_UP_TIM13_IRQHandler" : [[8, 13],[]],
    "TIM1_BRK_TIM9_IRQHandler" : [[9],[]],
    "TIM1_TRG_COM_TIM11_IRQHandler" : [[11],[]],
    "TIM8_BRK_TIM12_IRQHandler" : [[12],[]],
    "TIM8_TRG_COM_TIM14_IRQHandler" : [[14],[]],
}

UART_INTERRUPTS = {
    "USART1_IRQHandler" : [1],
    "USART2_IRQHandler" : [2],
    "USART3_IRQHandler" : [3],
    "UART4_IRQHandler" : [4],
    "UART5_IRQHandler" : [5],
    "USART6_IRQHandler" : [6],
}


def writeln(f, txt):
    f.write(txt+"\n")

for i in TIMER_INTERRUPTS:
    f = open("timer_"+str(i)+".cpp", "w")
    writeln(f, "#include \"timer.hpp\"")
    writeln(f, "")
    writeln(f, "extern \"C\" {")
    writeln(f, "")
    interrupt = TIMER_INTERRUPTS[i]
    conds = []
    for t in interrupt[0]:
        conds.append("(defined TIM"+str(t)+")")
    for t in interrupt[1]:
        conds.append("(not defined TIM"+str(t)+")")
    writeln(f, "#if " + " and ".join(conds))
    writeln(f, "")
    writeln(f, "void "+i+"(void) {")
    for t in interrupt[0]:
        t = str(t)
        writeln(f, "  {")
        writeln(f, "    auto& h = Private::get_timer_cube_handle<"+t+">();")
        writeln(f, "    if(__HAL_TIM_GET_ITSTATUS(&h, TIM_IT_UPDATE) == SET) {")
        writeln(f, "      if(Private::get_timer_irq_handler<"+t+">()) Private::get_timer_irq_handler<"+t+">()();")
        writeln(f, "      __HAL_TIM_CLEAR_IT(&h, TIM_IT_UPDATE);")
        writeln(f, "    }")
        writeln(f, "  }")
    writeln(f, "}")
    writeln(f, "")
    writeln(f, "#endif")
    writeln(f, "")
    writeln(f, "}")
    writeln(f, "")
    f.close();

for i in UART_INTERRUPTS:
    f = open("uart_"+str(i)+".cpp", "w")
    writeln(f, "#include \"uart.hpp\"")
    writeln(f, "")
    writeln(f, "extern \"C\" {")
    writeln(f, "")
    interrupt = UART_INTERRUPTS[i]
    writeln(f, "void "+i+"(void) {")
    for t in interrupt:
        t = str(t)
        writeln(f, "  {")
        writeln(f, "    if(__HAL_UART_GET_IT_SOURCE(&Private::get_uart_cube_handle<"+t+">(), UART_IT_RXNE)) {")
        writeln(f, "      if(Private::get_uart_rx_irq_handler<"+t+">()) Private::get_uart_rx_irq_handler<"+t+">()();")
        writeln(f, "      __HAL_UART_CLEAR_FLAG(&Private::get_uart_cube_handle<"+t+">(), UART_IT_RXNE);")
        writeln(f, "    }")
        writeln(f, "    else if(__HAL_UART_GET_IT_SOURCE(&Private::get_uart_cube_handle<"+t+">(), UART_IT_TC)) {")
        writeln(f, "      if(Private::get_uart_tx_irq_handler<"+t+">()) Private::get_uart_tx_irq_handler<"+t+">()();")
        writeln(f, "      __HAL_UART_CLEAR_FLAG(&Private::get_uart_cube_handle<"+t+">(), UART_IT_TC);")
        writeln(f, "    }")
        writeln(f, "  }")
    writeln(f, "}")
    writeln(f, "")
    writeln(f, "}")
    writeln(f, "")
    f.close();

