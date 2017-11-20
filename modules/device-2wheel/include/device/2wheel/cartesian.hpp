#ifndef DEVICE_2WHEEL_CARTESIAN_HPP
#define DEVICE_2WHEEL_CARTESIAN_HPP

#include <device/output.hpp>
#include <device/asynchronous.hpp>

namespace Aversive {
namespace Device {
namespace TwoWheel {

template<typename Speed, typename Angle, typename AngleSensor> class CartesianRobotX;
template<typename Speed, typename Angle, typename AngleSensor> class CartesianRobotY;
template<typename Speed, typename Angle, typename AngleSensor> class CartesianRobotAngle;

template<typename Speed, typename PolarAngle, typename AngleSensor>
class CartesianRobot : public Asynchronous {
public:
  using X = CartesianRobotX<Speed, PolarAngle, AngleSensor>;
  using Y = CartesianRobotY<Speed, PolarAngle, AngleSensor>;
  using Angle = CartesianRobotAngle<Speed, PolarAngle, AngleSensor>;

private:
  Speed& _speed;
  PolarAngle& _angle;
  AngleSensor& _angle_sensor;
  double _cmd_vx = 0;
  double _cmd_vy = 0;
  double _cmd_a = 0;

public:
  CartesianRobot(Speed& speed, PolarAngle& angle, AngleSensor& angle_sensor)
    : _speed(speed), _angle(angle), _angle_sensor(angle_sensor) {
  }

public:
  void putX(double vx) {
    _cmd_vx = vx;
  }

  void putY(double vy) {
    _cmd_vy = vy;
  }

  void putAngle(double a) {
    _cmd_a = a;
  }

public:
  void update(void) {
    _speed.put(0);
    if(_cmd_vx != 0 || _cmd_vy != 0) {
      double cmd_a = atan2(_cmd_vy, _cmd_vx);
      double a = _angle_sensor.get();
      double amod = fmod(a, 3.14*2);
      if(amod<-3.14) amod += 3.14;
      if(amod>3.14)  amod -= 3.14;
      double adiv = a - amod;
      double speed_mul = 1;

      if(amod < cmd_a) {
        if(fabs(cmd_a-amod) > fabs(cmd_a-3.14-amod)) {
          cmd_a -= 3.14;
          speed_mul = -1;
        }
      }
      else {
        if(fabs(cmd_a-amod) > fabs(cmd_a+3.14-amod)) {
          cmd_a += 3.14;
          speed_mul = -1;
        }
      }

      _angle.put(cmd_a+adiv);
      if(fabs(cmd_a-amod) < 0.5*3.14/180.0) {
        speed_mul *= cos(cmd_a-amod);
        _speed.put(speed_mul*sqrt(_cmd_vx*_cmd_vx + _cmd_vy*_cmd_vy));
      }
    }
    else {
      _angle.put(_cmd_a);
    }
  }

public:
  inline X& x(void) {
    return (X&)*this;
  }

  inline Y& y(void) {
    return (Y&)*this;
  }

  inline Angle& angle(void) {
    return (Angle&)*this;
  }
};

template<typename Speed, typename Angle, typename AngleSensor>
class CartesianRobotX :
    private CartesianRobot<Speed, Angle, AngleSensor>,
    public Output<double> {
public:
  inline void put(double val) {
    this->putX(val);
  }
};

template<typename Speed, typename Angle, typename AngleSensor>
class CartesianRobotY :
    private CartesianRobot<Speed, Angle, AngleSensor>,
    public Output<double> {
public:
  inline void put(double val) {
    this->putY(val);
  }
};

template<typename Speed, typename Angle, typename AngleSensor>
class CartesianRobotAngle :
    private CartesianRobot<Speed, Angle, AngleSensor>,
    public Output<double> {
public:
  inline void put(double val) {
    this->putAngle(val);
  }
};

}
}
}

#endif//DEVICE_2WHEEL_CARTESIAN_HPP
