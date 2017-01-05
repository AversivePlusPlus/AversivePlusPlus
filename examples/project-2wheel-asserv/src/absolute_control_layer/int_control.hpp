#ifndef ABSOLUTE_CONTROL_LAYER_LAYER_HPP
#error "This file must not be included directly, include absolute_control_layer/layer.hpp instead"
#endif

#include "../robot_control_layer/layer.hpp"

#include <device/control/controller.hpp>
#include <device/control/input_filter.hpp>
#include <device/control/output_filter.hpp>
#include <filter/pid.hpp>
#include <filter/shift.hpp>
#include <filter/quadramp.hpp>
#include <filter/type_adapter.hpp>

#include <device/2wheel/locator.hpp>

namespace AbsoluteControlLayer {
  namespace IntControl {

    class Dev : public RobotControlLayer::Dev {
      using Lower = RobotControlLayer::Dev;

      template<typename Speed, typename Angle, typename AngleSensor>
      class RobotSpeedController
          : public Device::Asynchronous<RobotSpeedController<Speed, Angle, AngleSensor>> {
        Dev& _dev;
        Device::Output<s32, Speed>& _speed;
        Device::Output<double, Angle>& _angle;
        Device::Input<double, AngleSensor>& _angle_sensor;
        double _cmd_vx = 0;
        double _cmd_vy = 0;

      public:
        RobotSpeedController(Dev& dev, Speed& speed, Angle& angle, AngleSensor& angle_sensor)
          : _dev(dev), _speed(speed), _angle(angle), _angle_sensor(angle_sensor) {
        }

        void update(void) {
          _speed.setValue(0);
          if(_cmd_vx != 0 || _cmd_vy != 0) {
              double cmd_a = atan2(_cmd_vy, _cmd_vx);
              double a = _angle_sensor.getValue();
              double amod = fmod(a, 3.14*2);
              if(amod<-3.14) amod += 3.14;
              if(amod>3.14)  amod -= 3.14;
              double adiv = a - amod;
              double speed_mul = 1;

              if(amod < cmd_a) {
                  if(abs(cmd_a-amod) > abs(cmd_a-3.14-amod)) {
                      cmd_a -= 3.14;
                      speed_mul = -1;
                    }
                }
              else {
                  if(abs(cmd_a-amod) > abs(cmd_a+3.14-amod)) {
                      cmd_a += 3.14;
                      speed_mul = -1;
                    }
                }

              _angle.setValue(cmd_a+adiv);
              if(fabs(cmd_a-amod) < 5.0*3.14/180.0) {
                  speed_mul *= cos(cmd_a-amod);
                  _speed.setValue(speed_mul*sqrt(_cmd_vx*_cmd_vx + _cmd_vy*_cmd_vy));
                }
            }
        }

        void setSpeedX(double vx) {
          _cmd_vx = vx;
        }

        void setSpeedY(double vy) {
          _cmd_vy = vy;
        }
      };

      Filter::TypeAdapter<s32, double> _td;
      Device::Control::InputFilter<decltype(Lower::distance), decltype(_td)> distance{Lower::distance, _td};

      Filter::Proportional<double> _pa{0.01*3.14/180.0};
      Filter::TypeAdapter<s32, double> _ta;
      Filter::Chain<decltype(_ta), decltype(_pa)> _fa{_ta, _pa};
      Device::Control::InputFilter<decltype(Lower::angle), decltype(_fa)> angle{Lower::angle, _fa};

      Device::TwoWheel::Locator<double, double, double, decltype(distance), decltype(angle)> loc{distance, angle};

      Filter::Proportional<double> _pra{1.0/(0.01*3.14/180.0)};
      Filter::TypeAdapter<double, s32> _tra;
      Filter::Chain<decltype(_pra), decltype(_tra)> _fra{_pra, _tra};
      Device::Control::OutputFilter<decltype(Lower::robot_angle), decltype(_fra)> robot_angle{Lower::robot_angle, _fra};

    public:

      decltype(loc)::CoordX x{loc};
      decltype(loc)::CoordY y{loc};
      decltype(loc)::Angle a{loc};

      RobotSpeedController<decltype(robot_speed), decltype(robot_angle), decltype(angle)> robot{*this, robot_speed, robot_angle, angle};

      DECL_AUTO_ATTRIBUTE(updater_constructor, Lower::updater_constructor
                          .build(loc,   100000)
                          .build(robot, 100000)
                          );
    };

  }
}
