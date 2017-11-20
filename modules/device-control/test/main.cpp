#include <device/control/controller.hpp>
#include <device/control/input_filter.hpp>
#include <device/control/output_filter.hpp>
#include <filter/proportional.hpp>

#include <cassert>
#include <iostream>
using namespace std;

using namespace Aversive;
using namespace Aversive::Base;

class MyActuator : public Device::Output<s32> {
  s32& _val;
public:
  MyActuator(s32& val) : _val(val) {}

  void put(s32 val) {
    _val += val;
  }
};

class MySensor : public Device::Input<s32> {
  s32& _val;
public:
  MySensor(s32& val) : _val(val) {}

  s32 get(void) {
    return _val;
  }
};

s32 val = 42;

int main(int, char**) {
  MyActuator _ac(val);
  MySensor _sn(val);

  Filter::Proportional<s32> fo(1), fi(1);
  Device::Control::AsynchronousInputFilter<decltype(_sn), decltype(fi)> sn(_sn, fi);
  Device::Control::AsynchronousOutputFilter<decltype(_ac), decltype(fo)> ac(_ac, fo);

  Filter::Proportional<s32> sp(1), fb(1), er(1);
  Device::Control::SystemController<
      decltype(ac), decltype(sn),
      decltype(sp),decltype(fb),decltype(er)
      > controller(ac, sn, sp, fb, er);

  controller.put(10);
  sn.update();
  controller.update();
  ac.update();

  assert(val == 10);

  cout << "OK" << endl;
  return 0;
}
