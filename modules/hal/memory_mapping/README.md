# memory_mapping

## Description

This project is a part of the [Aversive++ library](https://github.com/AversivePlusPlus/AversivePlusPlus).
This module is designed to help the developper to define some Hardware Description Layer (HLD) module.
An HDL is a library that "gives names to register addresses". A well known example is ARM's CMSIS library.
An other exmaple is the "avr/io.h" for AVRs microcontrollers.

The aim of defining new HDLs for targets that already have one is to add some usefull services.
One of them is to have a Compile-time verification of how the developer use the registers.
Indeed, the library could prevent the developer to modify a register's field he does not want because of a bad bitwise operation.

There is a [proof of concept, for ATMegaxx0_1](https://github.com/AversivePlusPlus/hdl-atmegaxx0_1).
