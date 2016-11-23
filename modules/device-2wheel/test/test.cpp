#include <device/2wheel/odometer.hpp>
#include <device/2wheel/robot.hpp>
#include <device/2wheel/locator.hpp>

#include <base/integer.hpp>

#ifdef AVERSIVE_TOOLCHAIN_SASIAE
#include <cassert>
#include <iostream>
#endif

class MyActuator : public Device::Output<double, MyActuator> {
  double& _val;
public:
  MyActuator(double& val) : _val(val) {}

  void setValue(double val) {
    _val += val;
  }
};

class MySensor : public Device::Input<double, MySensor> {
  double& _val;
public:
  MySensor(double& val) : _val(val) {}

  double getValue(void) {
    return _val;
  }
};

double left = 42;
double right = 42;

constexpr auto PI = 3.141592653589793;

int main(int, char**) {
  MySensor enc_l(left);
  MySensor enc_r(right);

  Device::TwoWheel::Odometer<double, decltype(enc_l), decltype(enc_r)> odo(enc_l, enc_r);
  decltype(odo)::Distance dist(odo);
  decltype(odo)::Angle angle(odo);

  MyActuator mot_l(left);
  MyActuator mot_r(right);

  Device::TwoWheel::Robot<double, decltype(mot_l), decltype(mot_r)> bot(mot_l, mot_r);
  decltype(bot)::Distance bot_d(bot);
  decltype(bot)::Angle    bot_a(bot);

  Device::TwoWheel::Locator<double, double, double, decltype(dist), decltype(angle)> pos(dist, angle);
  decltype(pos)::CoordX x(pos);
  decltype(pos)::CoordY y(pos);
  decltype(pos)::Angle a(pos);

#ifdef AVERSIVE_TOOLCHAIN_SASIAE
  std::cout << dist.getValue() << " " << angle.getValue() << std::endl;
  std::cout << x.getValue() << " " <<  y.getValue() << " " << a.getValue() << std::endl;
  std::cout << "----------" << std::endl;

  assert(x.getValue() == 0);
  assert(y.getValue() == 0);
  assert(a.getValue() == 0);

  assert(dist.getValue() == 42*2);
  assert(angle.getValue() == 0*2);
#endif

  bot_d.setValue(28);
  bot_a.setValue(0);

  bot.update();
  pos.update();


#ifdef AVERSIVE_TOOLCHAIN_SASIAE
  std::cout << dist.getValue() << " " << angle.getValue() << std::endl;
  std::cout << x.getValue() << " " <<  y.getValue() << " " << a.getValue() << std::endl;
  std::cout << "----------" << std::endl;

  assert(x.getValue() == 28*2);
  assert(y.getValue() == 0);
  assert(a.getValue() == 0);

  assert(dist.getValue() == (42+28)*2);
  assert(angle.getValue() == 0*2);
#endif

  bot_d.setValue(0);
  bot_a.setValue(PI/4);

  bot.update();
  pos.update();

#ifdef AVERSIVE_TOOLCHAIN_SASIAE
  std::cout << dist.getValue() << " " << angle.getValue() << std::endl;
  std::cout << x.getValue() << " " <<  y.getValue() << " " << a.getValue() << std::endl;
  std::cout << "----------" << std::endl;

  assert(x.getValue() == 28*2);
  assert(y.getValue() == 0);
  assert(abs(a.getValue() - (PI/4.0)*2.0) < 0.001);

  assert(dist.getValue() == (42+28)*2);
  assert(abs(angle.getValue() - (PI/4.0)*2.0) < 0.001);
#endif

  bot_d.setValue(28);
  bot_a.setValue(0);

  bot.update();
  pos.update();

#ifdef AVERSIVE_TOOLCHAIN_SASIAE
  std::cout << dist.getValue() << " " << angle.getValue() << std::endl;
  std::cout << x.getValue() << " " <<  y.getValue() << " " << a.getValue() << std::endl;
  std::cout << "----------" << std::endl;

  assert(abs(x.getValue() - 28*2) < 0.001);
  assert(abs(y.getValue() - 28*2) < 0.001);
  assert(abs(a.getValue() - (PI/4.0)*2.0) < 0.001);

  assert(dist.getValue() == (42+28+28)*2);
  assert(abs(angle.getValue() - (PI/4.0)*2.0) < 0.001);
#endif

  return 0;
}
