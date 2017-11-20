#ifndef DEVICE_2WHEEL_POLAR_HPP
#define DEVICE_2WHEEL_POLAR_HPP

#include <device/output.hpp>
#include <device/asynchronous.hpp>

namespace Aversive {
namespace Device {
namespace TwoWheel {

template<typename T, typename Left, typename Right> class PolarRobotAngle;
template<typename T, typename Left, typename Right> class PolarRobotDistance;

//! \brief A device that transform a distance speed and anglular speed setpoint into motors speed setpoint for 2 wheeled robots
//! \param T : The type of data sent to motors
//! \warning This device is Asynchronous, you will need to call the update() method to send values to motors.
/*!
    This device does not inherit directly from Input class, since it send complex data :
    the pair (distance speed, angular speed).
    So, it defines 2 subclasses that inherit from Input : Robot<T>::Distance and Robot<T>::Angle.
*/
template<typename T, typename Left, typename Right>
class PolarRobot : Asynchronous {
public:
  using Angle = PolarRobotAngle<T, Left, Right>;
  using Distance = PolarRobotDistance<T, Left, Right>;

private:
  Left& _left;
  Right& _right;
  T _dist;
  T _angle;

public:
  //! \brief Constructor
  //! \param left : Left motor
  //! \param right : Right motor
  /*!
      The left and the right motors should be controlled in speed, and behave identically withe the same setpoint,
      but it is not compulsory.
     */
  PolarRobot(Left& mot_l, Right& mot_r)
    : _left(mot_l), _right(mot_r),
      _dist(0), _angle(0) {
  }

public:
  //! \brief Update the motor's setpoints considering distance and angle speed
  inline void update() {
    _left.put(_dist - _angle);
    _right.put(_dist + _angle);
  }

public:
  //! \brief Set the distance speed.
  inline void putDistance(T val) {
    _dist = val;
  }

  //! \brief Set the angular speed.
  inline void putAngle(T val) {
    _angle = val;
  }

public:
  inline Angle& angle(void) {
    return (Angle&)*this;
  }

  inline Distance& distance(void) {
    return (Distance&)*this;
  }
};

//! \brief A Device that set angular speed of a Robot.
template<typename T, typename Left, typename Right>
class PolarRobotAngle :
    private PolarRobot<T, Left, Right>,
    public Output<T>{
public:
  inline void put(T val) {
    return this->putAngle(val);
  }
};

//! \brief A Device that set distance speed of a Robot.
template<typename T, typename Left, typename Right>
class PolarRobotDistance :
    private PolarRobot<T, Left, Right>,
    public Output<T>{
public:
  inline void put(T val) {
    return this->putDistance(val);
  }
};

}
}
}

#endif//DEVICE_2WHEEL_POLAR_HPP

