TARGETS = [
    "stm32f479ni",
    "stm32f446re",
    "stm32f411re",
    "stm32f410rb",
    "stm32f439ni",
    "stm32f401vc",
    "stm32f446ze",
    "stm32f401ve",
    "stm32f401re",
    "stm32f469ni",
    "stm32f411ce",
    "stm32f429zi",
    "stm32f407ig",
    "stm32f401cc",
    "stm32f439bg",
    "stm32f411ve",
    "stm32f407vg",
    "stm32f401ce",
    "stm32f429ni",
    "stm32f417ig",
    
    "atmega640",
    "atmega1280",
    "atmega1281",
    "atmega2560",
    "atmega2561",
    "atmega32",
    "atmega128",
    "atxmega192a3",

    "interface",
    "native",
    "sasiae"
    ]

for t in TARGETS:
    print("all:"+t)
    print(t+":")
    print("install:install_"+t)
    print("install_"+t+":")
    print("package:package_"+t)
    print("package_"+t+":")
    print("")
