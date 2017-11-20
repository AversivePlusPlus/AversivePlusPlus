#include <device/2wheel/odometer.hpp>
#include <device/2wheel/locator.hpp>

#include <device/2wheel/polar.hpp>
#include <device/2wheel/cartesian.hpp>

#include <base/integer.hpp>

#include <cassert>
#include <iostream>

using namespace Aversive;

class MyActuator : public Device::Output<double> {
  double& _val;
public:
  MyActuator(double& val) : _val(val) {}

  void put(double val) {
    _val += val;
  }
};

class MySensor : public Device::Input<double> {
  double& _val;
public:
  MySensor(double& val) : _val(val) {}

  double get(void) {
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
  decltype(odo)::Distance& dist = odo.distance();
  decltype(odo)::Angle& angle = odo.angle();

  MyActuator mot_l(left);
  MyActuator mot_r(right);

  Device::TwoWheel::PolarRobot<double, decltype(mot_l), decltype(mot_r)> bot(mot_l, mot_r);
  decltype(bot)::Distance bot_d = bot.distance();
  decltype(bot)::Angle    bot_a = bot.angle();

  Device::TwoWheel::Locator<double, double, double, decltype(dist), decltype(angle)> pos(dist, angle);
  decltype(pos)::X x = pos.x();
  decltype(pos)::Y y = pos.y();
  decltype(pos)::Angle a = pos.angle();

  Device::TwoWheel::CartesianRobot<decltype(bot_d), decltype(bot_a), decltype(a)> cartesian_bot(bot_d, bot_a, a);
  (void) cartesian_bot; // TODO

#ifdef DEBUG
  std::cout << dist.get() << " " << angle.get() << std::endl;
  std::cout << x.get() << " " <<  y.get() << " " << a.get() << std::endl;
  std::cout << "----------" << std::endl;
#endif

  assert(x.get() == 0);
  assert(y.get() == 0);
  assert(a.get() == 0);

  assert(dist.get() == 42*2);
  assert(angle.get() == 0*2);

  bot_d.put(28);
  bot_a.put(0);

  bot.update();
  pos.update();


#ifdef DEBUG
  std::cout << dist.get() << " " << angle.get() << std::endl;
  std::cout << x.get() << " " <<  y.get() << " " << a.get() << std::endl;
  std::cout << "----------" << std::endl;
#endif

  assert(x.get() == 28*2);
  assert(y.get() == 0);
  assert(a.get() == 0);

  assert(dist.get() == (42+28)*2);
  assert(angle.get() == 0*2);

  bot_d.put(0);
  bot_a.put(PI/4);

  bot.update();
  pos.update();

#ifdef DEBUG
  std::cout << dist.get() << " " << angle.get() << std::endl;
  std::cout << x.get() << " " <<  y.get() << " " << a.get() << std::endl;
  std::cout << "----------" << std::endl;
#endif

  assert(x.get() == 28*2);
  assert(y.get() == 0);
  assert(abs(a.get() - (PI/4.0)*2.0) < 0.001);

  assert(dist.get() == (42+28)*2);
  assert(abs(angle.get() - (PI/4.0)*2.0) < 0.001);

  bot_d.put(28);
  bot_a.put(0);

  bot.update();
  pos.update();

#ifdef DEBUG
  std::cout << dist.get() << " " << angle.get() << std::endl;
  std::cout << x.get() << " " <<  y.get() << " " << a.get() << std::endl;
  std::cout << "----------" << std::endl;
#endif
  
  assert(abs(x.get() - 28*2) < 0.001);
  assert(abs(y.get() - 28*2) < 0.001);
  assert(abs(a.get() - (PI/4.0)*2.0) < 0.001);

  assert(dist.get() == (42+28+28)*2);
  assert(abs(angle.get() - (PI/4.0)*2.0) < 0.001);

  std::cout << "OK" << std::endl;
  return 0;
}
