import mcu

import stm32fx_gen
import stm32fxxx_gen
import stm32fxxxxx_gen


for fx in mcu.mcu:
    stm32fx_gen.gen_cmake(fx[1:2])
    for fxxx in mcu.mcu[fx]:
        stm32fxxx_gen.gen_cmake(fx[1:2], fxxx)
        for fxxxxx in mcu.mcu[fx][fxxx]:
            stm32fxxxxx_gen.gen_cmake(fx[1:2], fxxx, fxxxxx)
