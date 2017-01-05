#ifndef DEVICE_2WHEEL_ROBOT_HPP
#define DEVICE_2WHEEL_ROBOT_HPP

#include <device/output.hpp>
#include <device/asynchronous.hpp>

namespace Aversive {
namespace Device {
  namespace TwoWheel {

    //! \brief A device that transform a distance speed and anglular speed setpoint into motors speed setpoint for 2 wheeled robots
    //! \param T : The type of data sent to motors
    //! \warning This device is Asynchronous, you will need to call the update() method to send values to motors.
    /*!
      This device does not inherit directly from Input class, since it send complex data :
      the pair (distance speed, angular speed).
      So, it defines 2 subclasses that inherit from Input : Robot<T>::Distance and Robot<T>::Angle.
     */
    template<typename T, typename Left, typename Right>
    class Robot : Asynchronous<Robot<T, Left, Right>> {
    private:
      Output<T, Left>& _left;
      Output<T, Right>& _right;
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
      Robot(Output<T, Left>& mot_l, Output<T, Right>& mot_r)
        : _left(mot_l), _right(mot_r),
          _dist(0), _angle(0) {
      }

      //! \brief Update the motor's setpoints considering distance and angle speed
      inline void update() {
        _left.setValue(_dist - _angle);
        _right.setValue(_dist + _angle);
      }

      //! \brief Set the distance speed.
      inline void setDistance(T val) {
        _dist = val;
      }

      //! \brief Set the angular speed.
      inline void setAngle(T val) {
        _angle = val;
      }

    public:
      //! \brief A Device that set distance speed of a Robot.
      class Distance : public Output<T, Distance> {
        Robot<T, Left, Right>& _bot;
      public:
        inline Distance(Robot<T, Left, Right>& odo)
          : _bot(odo) {
        }

        inline void setValue(T val) {
          return _bot.setDistance(val);
        }
      };

      //! \brief A Device that set angular speed of a Robot.
      class Angle : public Output<T, Angle> {
        Robot<T, Left, Right>& _bot;
      public:
        inline Angle(Robot<T, Left, Right>& odo)
          : _bot(odo) {
        }

        inline void setValue(T val) {
          return _bot.setAngle(val);
        }
      };
    };

  }
}
}

#endif//DEVICE_2WHEEL_ROBOT_HPP

