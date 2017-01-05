#ifndef AVERSIVE_TOOLCHAIN_SASIAE
#error "This DeviceLayer need the target SASIAE"
#endif

#ifndef DEVICE_LAYER_LAYER_HPP
#error "This file must not be included directly, include device_layer/layer.hpp instead"
#endif

#include <device/sasiae/motor.hpp>
#include <device/sasiae/encoder.hpp>
#include <stream/sasiae/stream.hpp>
#include <stream/formatted_stream.hpp>
#include <sasiae/asynchronous_updater.hpp>
#include <filter/integral.hpp>

#define DECL_AUTO_ATTRIBUTE(attr, val) \
  decltype(val) attr = val;

using namespace Aversive;
using namespace Aversive::Base;

namespace DeviceLayer {
  namespace tinySASIAE {

    template<typename Motor>
    class MotorAdapter : public Aversive::Device::Output<s32, MotorAdapter<Motor>> {
      Motor& _mot;
      Filter::Integral<s32> _i;
      double _coeff;
    public:
      MotorAdapter(Motor& mot, double coeff) : _mot(mot), _i(0), _coeff(coeff) {
      }

      void setValue(s32 val) {
        _mot.setValue(_i(val)*_coeff);
      }
    };

    class Dev {
    private:
      Aversive::Stream::SASIAE::Stream _io{"io"};
      Aversive::Device::SASIAE::Motor _motor_left{"leftMot"};
      Aversive::Device::SASIAE::Motor _motor_right{"rightMot"};

    public:
      Aversive::Device::SASIAE::Encoder encoder_left{"leftEnc"};
      Aversive::Device::SASIAE::Encoder encoder_right{"rightEnc"};

      MotorAdapter<decltype(_motor_left)> motor_left{_motor_left, 1.2};
      MotorAdapter<decltype(_motor_right)> motor_right{_motor_right, 1.0};

      Aversive::Stream::FormattedStreamDecorator<decltype(_io)> io{_io};

      DECL_AUTO_ATTRIBUTE(updater_constructor, SASIAE::AsynchronousUpdaterConstructor::instance());
    };

  }

  using namespace tinySASIAE;
}
