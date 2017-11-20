#include <device/control/controller.hpp>
#include <device/control/input_filter.hpp>
#include <device/control/output_filter.hpp>
#include <filter/pid.hpp>
#include <filter/shift.hpp>
#include <filter/quadramp.hpp>
#include <filter/type_adapter.hpp>

#include <device/2wheel/locator.hpp>
#include <device/2wheel/cartesian.hpp>

#include <device/control/controller.hpp>
#include <device/control/input_filter.hpp>
#include <device/control/output_filter.hpp>
#include <filter/pid.hpp>
#include <filter/shift.hpp>
#include <filter/quadramp.hpp>

#include <device/2wheel/odometer.hpp>
#include <device/2wheel/polar.hpp>

#include <device/control/controller.hpp>
#include <filter/pid.hpp>
#include <filter/shift.hpp>

#include <device/sasiae/motor.hpp>
#include <device/sasiae/encoder.hpp>
#include <stream/sasiae/stream.hpp>
#include <stream/formatted_stream.hpp>
#include <sasiae/asynchronous_updater.hpp>
#include <filter/integral.hpp>

using namespace Aversive::Base;

template<class SpeedOutputRef, class PositionInputRef>
class CartesianDeviceLayer {
protected:
  inline CartesianDeviceLayer(void) {}

public:
  inline SpeedOutputRef robot(void);
  inline PositionInputRef locator(void);
};

template<class XRef, class YRef>
class CartesianDevice {
protected:
  inline CartesianDevice(void) {}

public:
  inline XRef x(void);
  inline YRef y(void);
};

template<class XRef, class YRef, class AngleRef>
class HolonomicCartesianDevice :
    public CartesianDevice<XRef, YRef> {
protected:
  inline HolonomicCartesianDevice(void) {}

public:
  inline AngleRef angle(void);
};

template<class PolarRef, class OdometerRef>
class PolarDeviceLayer {
protected:
  inline PolarDeviceLayer(void) {}

public:
  inline PolarRef robot(void);
  inline OdometerRef odometer(void);
};

template<class AngleRef, class DistanceRef>
class PolarDevice {
protected:
  inline PolarDevice(void) {}

public:
  inline AngleRef angle(void);
  inline DistanceRef distance(void);
};

template<class MotorsRef, class EncodersRef>
class WheelsDeviceLayer {
public:
  using Motors = MotorsRef;
  using Encoders = EncodersRef;

protected:
  inline WheelsDeviceLayer(void) {}

public:
  inline MotorsRef motors(void);
  inline EncodersRef encoders(void);
};

template<class LeftRef, class RightRef>
class WheelsDevice {
public:
  using Left = LeftRef;
  using Right = RightRef;

protected:
  inline WheelsDevice(void) {}

public:
  inline LeftRef left(void);
  inline RightRef right(void);
};

template<class Left, class Right>
class SimpleWheelsDevice :
    public WheelsDevice<Left&, Right&> {
private:
  Left& _left;
  Right& _right;

public:
  inline SimpleWheelsDevice(Left& left, Right& right)
    : _left(left), _right(right) {
  }

public:
  inline Left& left(void) {
    return _left;
  }

  inline Right& right(void) {
    return _right;
  }
};

template<class LeftMotor, class RightMotor, class LeftEncoder, class RightEncoder>
class SimpleWheelsDeviceLayer :
    public WheelsDeviceLayer<SimpleWheelsDevice<LeftMotor, RightMotor>&, SimpleWheelsDevice<LeftEncoder, RightEncoder>&> {
  SimpleWheelsDevice<LeftMotor, RightMotor> _motors;
  SimpleWheelsDevice<LeftEncoder, RightEncoder> _encoders;

public:
  inline SimpleWheelsDeviceLayer(LeftMotor& left_motor, RightMotor& right_motor, LeftEncoder& left_encoder, RightEncoder& right_encoder)
    : _motors(left_motor, right_motor), _encoders(left_encoder, right_encoder) {
  }

  inline SimpleWheelsDeviceLayer(SimpleWheelsDevice<LeftMotor, RightMotor> motors, SimpleWheelsDevice<LeftEncoder, RightEncoder> encoders)
    : _motors(motors), _encoders(encoders) {
  }

public:
  inline SimpleWheelsDevice<LeftMotor, RightMotor>& motors(void) {
    return _motors;
  }

  inline SimpleWheelsDevice<LeftEncoder, RightEncoder>& encoders(void) {
    return _encoders;
  }
};

template<class WheelsDeviceLayer>
class SimplePolarDeviceLayer {
private:
  using Motors = RemoveRef<typename WheelsDeviceLayer::Motors>;
  using Encoders = RemoveRef<typename WheelsDeviceLayer::Encoders>;

  using LeftMotor = RemoveRef<typename Motors::Left>;
  using RightMotor = RemoveRef<typename Motors::Right>;

  using LeftEncoder = RemoveRef<typename Encoders::Left>;
  using RightEncoder = RemoveRef<typename Encoders::Right>;

public:
  using Polar = Aversive::Device::TwoWheel::PolarRobot<s32, LeftMotor, RightMotor>;
  using Odometer = Aversive::Device::TwoWheel::Odometer<s32, LeftEncoder, RightEncoder>;

private:
  Polar _polar;
  Odometer _odo;

public:
  inline SimplePolarDeviceLayer(WheelsDeviceLayer& wdl)
    : _polar(wdl.motors().left(), wdl.motors().right()),
      _odo(wdl.encoders().left(), wdl.encoders().right()) {
  }

public:
  inline Polar& robot(void) {
    return _polar;
  }

  inline Odometer& odometer(void) {
    return _odo;
  }

public:
  inline void update(void) {
    _polar.update();
  }
};

template<class PolarDeviceLayer> class ControlledPolarDeviceLayerPolar;

template<class PolarDeviceLayer>
class ControlledPolarDeviceLayer {
public:
  using Polar = ControlledPolarDeviceLayerPolar<PolarDeviceLayer>;
  using Odometer = typename PolarDeviceLayer::Odometer;

private:
  PolarDeviceLayer& _sub;

private:
  Aversive::Filter::Proportional<s32> id{1};

  Aversive::Filter::Derivate<s32> diff_d{0};
  Aversive::Filter::Pid<s32> pid_d{0,1,0,0};
  Aversive::Filter::Shift<s32, u8> shift_d{0};
  Aversive::Filter::Chain<decltype(pid_d), decltype(shift_d)> err_d{pid_d, shift_d};

  Aversive::Filter::Derivate<s32> diff_a{0};
  Aversive::Filter::Pid<s32> pid_a{0,1,0,0};
  Aversive::Filter::Shift<s32, u8> shift_a{0};
  Aversive::Filter::Chain<decltype(pid_a), decltype(shift_a)> err_a{pid_a, shift_a};

  Aversive::Filter::Quadramp<s32> qramp_a{0, -1, 1, 1, 1};

protected:
  using Speed =
  Aversive::Device::Control::SystemController<
  RemoveRef<decltype(_sub.robot().distance())>, RemoveRef<decltype(_sub.odometer().distance())>,
  RemoveRef<decltype(id)>, RemoveRef<decltype(diff_d)>, RemoveRef<decltype(err_d)>
  >;

  using Angle =
  Aversive::Device::Control::SystemController<
  RemoveRef<decltype(_sub.robot().angle())>, RemoveRef<decltype(_sub.odometer().angle())>,
  RemoveRef<decltype(qramp_a)>, RemoveRef<decltype(id)>, RemoveRef<decltype(err_a)>
  >;

  Speed robot_speed{_sub.robot().distance(), _sub.odometer().distance(), id, diff_d, err_d};
  Angle robot_angle{_sub.robot().angle(), _sub.odometer().angle(), qramp_a, id, err_a};

public:
  inline ControlledPolarDeviceLayer(PolarDeviceLayer& sublayer)
    : _sub(sublayer) {
  }

public:
  inline Polar& robot(void) {
    return (Polar&)*this;
  }

  inline Odometer& odometer(void) {
    return _sub.odometer();
  }

public:
  inline void update(void) {
    robot_speed.update();
    robot_angle.update();
  }
};

template<class PolarDeviceLayer>
class ControlledPolarDeviceLayerPolar :
    public ControlledPolarDeviceLayer<PolarDeviceLayer> {
  using Angle = typename ControlledPolarDeviceLayer<PolarDeviceLayer>::Angle;
  using Distance = typename ControlledPolarDeviceLayer<PolarDeviceLayer>::Speed;

public:
  inline Angle& angle(void) {
    return this->robot_angle;
  }

  inline Distance& distance(void) {
    return this->robot_speed;
  }
};

template<class SubLayer> class DoublePolarDeviceLayerPolar;
template<class SubLayer> class DoublePolarDeviceLayerOdometer;

template<class SubLayer>
class DoublePolarDeviceLayer {
  const double ANGLE_COEFF = (45.0/1000.0)*3.14/180.0;

public:
  SubLayer& _sub;

public:
  Aversive::Filter::TypeAdapter<s32, double> _td;
  Aversive::Device::Control::InputFilter<decltype(_sub.odometer().distance()), decltype(_td)> odo_distance{_sub.odometer().distance(), _td};

  Aversive::Filter::Proportional<double> _pa{ANGLE_COEFF};
  Aversive::Filter::TypeAdapter<s32, double> _ta;
  Aversive::Filter::Chain<decltype(_ta), decltype(_pa)> _fa{_ta, _pa};
  Aversive::Device::Control::InputFilter<decltype(_sub.odometer().angle()), decltype(_fa)> odo_angle{_sub.odometer().angle(), _fa};

  Aversive::Filter::Proportional<double> _pra{1.0/(ANGLE_COEFF)};
  Aversive::Filter::TypeAdapter<double, s32> _tra;
  Aversive::Filter::Chain<decltype(_pra), decltype(_tra)> _fra{_pra, _tra};
  Aversive::Device::Control::OutputFilter<decltype(_sub.robot().angle()), decltype(_fra)> robot_angle{_sub.robot().angle(), _fra};

  Aversive::Filter::TypeAdapter<s32, double> _trd;
  Aversive::Device::Control::OutputFilter<decltype(_sub.robot().distance()), decltype(_td)> robot_distance{_sub.robot().distance(), _trd};

public:
  using Polar = DoublePolarDeviceLayerPolar<SubLayer>;
  using Odometer = DoublePolarDeviceLayerOdometer<SubLayer>;

public:
  inline DoublePolarDeviceLayer(SubLayer& sublayer)
    : _sub(sublayer) {
  }

public:
  inline Polar& robot(void) {
    return (Polar&)*this;
  }

  inline Odometer& odometer(void) {
    return (Odometer&)*this;
  }

public:
  inline void update(void) {
  }
};

template<class SubLayer>
class DoublePolarDeviceLayerPolar :
    public DoublePolarDeviceLayer<SubLayer> {
public:
  using Angle = decltype(DoublePolarDeviceLayer<SubLayer>::robot_angle);
  using Distance = decltype(DoublePolarDeviceLayer<SubLayer>::robot_distance);

public:
  inline Angle& angle(void) {
    return this->robot_angle;
  }

  inline Distance& distance(void) {
    return this->robot_distance;
  }
};


template<class SubLayer>
class DoublePolarDeviceLayerOdometer :
    public DoublePolarDeviceLayer<SubLayer> {
public:
  using Angle = decltype(DoublePolarDeviceLayer<SubLayer>::odo_angle);
  using Distance = decltype(DoublePolarDeviceLayer<SubLayer>::odo_distance);

public:
  inline Angle& angle(void) {
    return this->odo_angle;
  }

  inline Distance& distance(void) {
    return this->odo_distance;
  }
};


template<class PolarDeviceLayer>
class SimpleCartesianDeviceLayer {
private:
  using Polar = typename PolarDeviceLayer::Polar;
  using Odometer = typename PolarDeviceLayer::Odometer;

  using PolarAngle = typename Polar::Angle;
  using PolarDistance = typename Polar::Distance;
  using OdometerAngle = typename Odometer::Angle;
  using OdometerDistance = typename Odometer::Distance;

public:
  using Cartesian = Aversive::Device::TwoWheel::CartesianRobot<PolarDistance, PolarAngle, OdometerAngle>;
  using Locator = Aversive::Device::TwoWheel::Locator<double, double, double, OdometerDistance, OdometerAngle>;

private:
  Cartesian _robot;
  Locator _loc;

public:
  inline SimpleCartesianDeviceLayer(PolarDeviceLayer& pdl)
    : _robot(pdl.robot().distance(), pdl.robot().angle(), pdl.odometer().angle()),
      _loc(pdl.odometer().distance(), pdl.odometer().angle()) {
  }

public:
  inline Cartesian& robot(void) {
    return _robot;
  }

  inline Locator& locator(void) {
    return _loc;
  }

public:
  inline void update(void) {
    _robot.update();
    _loc.update();
  }
};


template<typename Output>
using ProportionalOuputFilter = Aversive::Device::Control::OutputFilter<Output, Aversive::Filter::Proportional<double>>;

int main(int, char**) {
  Aversive::Stream::SASIAE::Stream io{"io"};
  Aversive::Device::SASIAE::Motor _motor_left{"leftMot"};
  Aversive::Device::SASIAE::Motor _motor_right{"rightMot"};
  Aversive::Device::SASIAE::Encoder encoder_left{"leftEnc"};
  Aversive::Device::SASIAE::Encoder encoder_right{"rightEnc"};

  Aversive::Filter::Proportional<double> mlp(1.2);
  ProportionalOuputFilter<decltype(_motor_left)> motor_left(_motor_left, mlp);

  Aversive::Filter::Proportional<double> mrp(1.0);
  ProportionalOuputFilter<decltype(_motor_right)> motor_right(_motor_right, mrp);

  SimpleWheelsDeviceLayer<decltype(motor_left), decltype(motor_right), decltype(encoder_left), decltype(encoder_right)>
      wheels(motor_left, motor_right, encoder_left, encoder_right);

  SimplePolarDeviceLayer<decltype(wheels)> polar_robot(wheels);
  ControlledPolarDeviceLayer<decltype(polar_robot)> ctrl_polar_robot(polar_robot);
  DoublePolarDeviceLayer<decltype(ctrl_polar_robot)> double_polar_robot(ctrl_polar_robot);

  SimpleCartesianDeviceLayer<decltype(double_polar_robot)> cartesian_robot(double_polar_robot);

  auto& robot = cartesian_robot;

  SASIAE::AsynchronousUpdaterConstructor::instance()
      .build(polar_robot, 100000)
      .build(ctrl_polar_robot, 100000)
      .build(cartesian_robot, 100000)
      .start()
      ;

  robot.robot().x().put(1000);
  robot.robot().y().put(500);

  while(SASIAE::Aversive::sync()) {
    if(robot.locator().x().get() < -10000) {
      robot.robot().x().put(1000);
    }
    else if(robot.locator().x().get() > 10000) {
      robot.robot().x().put(-1000);
    }

    if(robot.locator().y().get() < -10000) {
      robot.robot().y().put(1000);
    }
    else if(robot.locator().y().get() > 10000) {
      robot.robot().y().put(-1000);
    }
  }

  return 0;
}
