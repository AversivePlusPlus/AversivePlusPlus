# Aversive++

This project provides a C++ library that eases microcontroller programming.

## Description

Its aim is to provide an interface simple enough to be able to create complex applications,
and optimized enough to enable small microcontrollers to execute these applications.

The other aspect of this library is to be multiplatform.
Indeed, it is designed to provide the same API for a simulator
(named SASIAE) and for AVR-based and ARM-based microcontrollers.

Check the project's [official website](http://aversiveplusplus.github.io) to have more information.

## Installation

### Aversive++

The library is a collection of modules that can be installed as conan packages.
(Warning : the conan used is modified, to enable embedded targets,
it may cause some trouble with existing conan installation).

```bash
git clone https://github.com/AversivePlusPlus/AversivePlusPlus.git
cd AversivePlusPlus
make update
make export
```

### Simulator

The project comes with a simple simulator called tinySASIAE, you can build and install it :

```bash
cd tinySASIAE
make
sudo make install
```

## Quick Start

There is an example code, to be used with the simulator.

```bash
cd examples/project-2wheel-asserv
make
tinySASIAE -r build/bin/project-2wheel-asserv
```
