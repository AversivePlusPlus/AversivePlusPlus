# hdl-atmegaxx0_1

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This is an Hardware Description Layer module.

This part is common to the following microcontrollers : 
 - ATMega640
 - ATMega1280
 - ATMega1281
 - ATMega2560
 - ATMega2561
 
This is a proof of concept of a new improved HDL, supposed to replace avr/io.h or CMSIS.
The aim is to add some compile-time verification to registers manipulations (checking if fields are meant to be modified or not, etc...)
