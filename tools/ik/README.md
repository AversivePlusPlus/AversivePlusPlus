# ik

This tool is a part of the [Aversive++ project](https://github.com/AversivePlusPlus/AversivePlusPlus).

# Description

This is a python tool that generates C++ code to solve inverse kinematics problems.
The generated C++ code can then be used in microcontrollers projects.

The tool can import kinematics chain from `blend` files.

# Installation

The tool cannot be installed yet. But you can test it anyway !

# Use

To list available endpoints in the blend file :
```bash
./bin/blend2cpp <blend_file>
```

To generate C++ code from an endpoint : 
```bash
./bin/blend2cpp <blend_file> <endpoint>
```
