#ifndef DEVICE_2WHEEL_ODOMETER_HPP
#define DEVICE_2WHEEL_ODOMETER_HPP

#include <device/input.hpp>

namespace Aversive {
namespace Device {
namespace TwoWheel {

template<typename T, typename Left, typename Right> class OdometerAngle;
template<typename T, typename Left, typename Right> class OdometerDistance;

//! \brief A device that compute a distance and angle coordinate from 2 encoders sensors
//! \param T : The type of data received from sensors
/*!
    This device does not inherit directly from Input class, since it returns complex data : the pair (distance, angle).
    So, it defines 2 subclasses that inherit from Input : Odometer<T>::Distance and Odometer<T>::Angle.
    You can use these subclasses as part of control systems.
   */
template<typename T, typename Left, typename Right>
class Odometer {
public:
  using Angle = OdometerAngle<T, Left, Right>;
  using Distance = OdometerDistance<T, Left, Right>;

private:
  Left& _left;
  Right& _right;

public:
  //! \brief Constructor
  //! \param left : Left encoder sensor
  //! \param right : Right encoder sensor
  /*!
      The encoders sensors should return data in the same unit, so that the odometer has a relevant formula.
      Indeed, if you gives an encoder that has 128ppr (pulse per revolution) and an other that has 1024ppr,
      without any convertion, don't expect the odometer to return something understandable !

      The encoders should also count in the same way.
      If the robot goes forward, the encoders should both count upward.
      It not, there may be some unwanted behaviours.
      For example, the distance's value and angle's value could be switched.
      Or the angle could not be counted counterclockwise.
     */
  inline Odometer(Left& left, Right& right) :
    _left(left), _right(right) {
  }

public:
  //! \brief Get the angle coordinate
  /*!
      The angle coordinate is basically the difference of distance of the encoders.
      The angle is computed to be counterclockwise.
     */
  inline T getAngle(void) {
    return (_right.get() - _left.get())/2;
  }

  //! \brief Get the distance coordinate
  /*!
      The distance coordinate is basically the sum of distance of the encoders.
     */
  inline T getDistance(void) {
    return (_left.get() + _right.get())/2;
  }

public:
  inline Angle& angle(void) {
    return (Angle&)*this;
  }

  inline Distance& distance(void) {
    return (Distance&)*this;
  }
};

//! \brief A Device that get angle from an odometer.
template<typename T, typename Left, typename Right>
class OdometerAngle :
    private Odometer<T, Left, Right>,
    public Input<T> {
public:
  inline T get(void) {
    return this->getAngle();
  }
};

//! \brief A Device that get distance from an odometer.
template<typename T, typename Left, typename Right>
class OdometerDistance :
    private Odometer<T, Left, Right>,
    public Input<T> {
public:
  inline T get(void) {
    return this->getDistance();
  }
};

}
}
}

#endif//DEVICE_2WHEEL_ODOMETER_HPP
