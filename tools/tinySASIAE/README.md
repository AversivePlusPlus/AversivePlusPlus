# tinySASIAE

It is a really simple robot simulator that is to be used with Aversive++.
The robot is a 2 wheeled robot that has 2 motor, 2 encoders, and a communication port.

## Install

You only need Qt5 and qmake-qt5.
Here are the commands you need to download, compile, and install the simulator.

```bash
git clone https://github.com/astralien3000/tinySASIAE.git
cd tinySASIAE
make
sudo make install
```

## Use

tinySASIAE only need a robot binary in the elf format.

```bash
tinySASIAE -r $ROBOT_ELF
```

## Develop a robot

### Example code

```c++
#include <device/sasiae/motor.hpp>
#include <device/sasiae/encoder.hpp>
#include <stream/sasiae/stream.hpp>

using namespace Aversive::Base;
using namespace Aversive::Device::SASIAE;
using namespace Aversive::Stream::SASIAE;

// Encoder devices
Encoder left_enc("leftEnc");
Encoder right_enc("rightEnc");

// Motor devices
Motor left_motor("leftMot");
Motor right_motor("rightMot");

// COMM
Stream io("io");

// User code
int main(int, char*) {
  left_motor.setValue(10);
  right_motor.setValue(10);

  while(SASIAE::Aversive::sync()) {
    s32 left_dist = left_encoder.getValue();
    s32 right_dist = right_encoder.getValue();
    io << left_dist << " " << right_dist << "\n";
  }
}
```
