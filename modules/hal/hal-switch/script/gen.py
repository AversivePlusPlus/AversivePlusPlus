INTERFACES = [
    "encoder",
    "gpio",
    "timer",
    "uart",
    "pwm",
]

MODULES = {
    "hal-stm32cubef4" : {
        "path" : "hal/stm32cubef4",
        "namespace" : "HAL::STM32CubeF4",
        "cond" : "AVERSIVE_TOOLCHAIN_STM32F4",
    },
    "hal-atxmega" : {
        "path" : "hal/atxmega",
        "namespace" : "HAL::ATxmega",
        "cond" : "AVERSIVE_TOOLCHAIN_ATXMEGA",
    },
    "hal-atmegaxx0_1" : {
        "path" : "hal/atmegaxx0_1",
        "namespace" : "HAL::ATMegaxx0_1",
        "cond" : "AVERSIVE_TOOLCHAIN_ATMEGAXX0_1",
    },
}

def writeln(f, txt):
    f.write(txt+"\n")

def gen(interface):
    f = open("include/hal/"+interface+".hpp", "w")
    writeln(f, '#ifndef AVERSIVE_HAL_SWITCH_'+interface.upper()+'_HPP')
    writeln(f, '#define AVERSIVE_HAL_SWITCH_'+interface.upper()+'_HPP')
    for m in MODULES:
        mod = MODULES[m]
        writeln(f, '')
        writeln(f, '#ifdef  '+mod["cond"])
        writeln(f, '#include <'+mod["path"]+'/'+interface+'.hpp>')
        writeln(f, 'namespace HAL { using namespace '+mod["namespace"]+'; }')
        writeln(f, '#endif//'+mod["cond"])
        writeln(f, '')
    writeln(f, '#endif//AVERSIVE_HAL_SWITCH_'+interface.upper()+'_HPP')

    
for i in INTERFACES:
    gen(i)
