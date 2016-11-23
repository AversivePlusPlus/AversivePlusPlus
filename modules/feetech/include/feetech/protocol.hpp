#ifndef FEETECH_PROTOCOL_HPP
#define FEETECH_PROTOCOL_HPP

#include <base/integer.hpp>

namespace Feetech {

  namespace Protocol {
    static constexpr u8 START = 0xFF;
    static constexpr u16 TIMEOUT = 500; //TIMEOUT 500ms

    static constexpr u8 B_1M     = 0;
    static constexpr u8 B_0_5M   = 1;
    static constexpr u8 B_250K   = 2;
    static constexpr u8 B_128K   = 3;
    static constexpr u8 B_115200 = 4;
    static constexpr u8 B_76800  = 5;
    static constexpr u8 B_57600  = 6;
    static constexpr u8 B_38400  = 7;

    //8bits register Address
    static constexpr u8 P_MODEL_NUMBER_L         = 0;
    static constexpr u8 P_MODEL_NUMBER_H         = 1;
    static constexpr u8 P_VERSION_L              = 3;
    static constexpr u8 P_VERSION_H              = 4;
    static constexpr u8 P_ID                     = 5;
    static constexpr u8 P_BAUD_RATE              = 6;
    static constexpr u8 P_RETURN_DELAY_TIME      = 7;
    static constexpr u8 P_RETURN_LEVEL           = 8;
    static constexpr u8 P_MIN_ANGLE_LIMIT_L      = 9;
    static constexpr u8 P_MIN_ANGLE_LIMIT_H      = 10;
    static constexpr u8 P_MAX_ANGLE_LIMIT_L      = 11;
    static constexpr u8 P_MAX_ANGLE_LIMIT_H      = 12;
    static constexpr u8 P_LIMIT_TEMPERATURE      = 13;
    static constexpr u8 P_MAX_LIMIT_VOLTAGE      = 14;
    static constexpr u8 P_MIN_LIMIT_VOLTAGE      = 15;
    static constexpr u8 P_MAX_TORQUE_L           = 16;
    static constexpr u8 P_MAX_TORQUE_H           = 17;
    static constexpr u8 P_ALARM_LED              = 18;
    static constexpr u8 P_ALARM_SHUTDOWN         = 19;
    static constexpr u8 P_COMPLIANCE_P           = 21;
    static constexpr u8 P_COMPLIANCE_D           = 22;
    static constexpr u8 P_COMPLIANCE_I           = 23;
    static constexpr u8 P_PUNCH_L                = 24;
    static constexpr u8 P_PUNCH_H                = 25;
    static constexpr u8 P_CW_DEAD                = 26;
    static constexpr u8 P_CCW_DEAD               = 27;
    static constexpr u8 P_IMAX_L                 = 28;
    static constexpr u8 P_IMAX_H                 = 29;
    static constexpr u8 P_OFFSET_L               = 30;
    static constexpr u8 P_OFFSET_H               = 31;

    static constexpr u8 P_TORQUE_ENABLE          = 40;
    static constexpr u8 P_LED                    = 41;
    static constexpr u8 P_GOAL_POSITION_L        = 42;
    static constexpr u8 P_GOAL_POSITION_H        = 43;
    static constexpr u8 P_GOAL_TIME_L            = 44;
    static constexpr u8 P_GOAL_TIME_H            = 45;
    static constexpr u8 P_GOAL_SPEED_L           = 46;
    static constexpr u8 P_GOAL_SPEED_H           = 47;
    static constexpr u8 P_LOCK                   = 48;

    static constexpr u8 P_PRESENT_POSITION_L     = 56;
    static constexpr u8 P_PRESENT_POSITION_H     = 57;
    static constexpr u8 P_PRESENT_SPEED_L        = 58;
    static constexpr u8 P_PRESENT_SPEED_H        = 59;
    static constexpr u8 P_PRESENT_LOAD_L         = 60;
    static constexpr u8 P_PRESENT_LOAD_H         = 61;
    static constexpr u8 P_PRESENT_VOLTAGE        = 62;
    static constexpr u8 P_PRESENT_TEMPERATURE    = 63;
    static constexpr u8 P_REGISTERED_INSTRUCTION = 64;
    static constexpr u8 P_ERROR                  = 65;
    static constexpr u8 P_MOVING                 = 66;
    static constexpr u8 P_VIR_POSITION_L         = 67;
    static constexpr u8 P_VIR_POSITION_H         = 68;
    static constexpr u8 P_CURRENT_L              = 69;
    static constexpr u8 P_CURRENT_H              = 70;

    //16bits register address
    static constexpr u8 P_MODEL_NUMBER         = 0;
    static constexpr u8 P_VERSION              = 3;
    static constexpr u8 P_MIN_ANGLE_LIMIT      = 9;
    static constexpr u8 P_MAX_ANGLE_LIMIT      = 11;
    static constexpr u8 P_MAX_TORQUE           = 16;
    static constexpr u8 P_PUNCH                = 24;
    static constexpr u8 P_IMAX                 = 28;
    static constexpr u8 P_OFFSET               = 30;
    static constexpr u8 P_GOAL_POSITION        = 42;
    static constexpr u8 P_GOAL_TIME            = 44;
    static constexpr u8 P_GOAL_SPEED           = 46;
    static constexpr u8 P_PRESENT_POSITION     = 56;
    static constexpr u8 P_PRESENT_SPEED        = 58;
    static constexpr u8 P_PRESENT_LOAD         = 60;
    static constexpr u8 P_VIR_POSITION         = 67;
    static constexpr u8 P_CURRENT              = 69;


    //Instruction:
    static constexpr u8 INST_PING       = 0x01;
    static constexpr u8 INST_READ       = 0x02;
    static constexpr u8 INST_WRITE      = 0x03;
    static constexpr u8 INST_REG_WRITE  = 0x04;
    static constexpr u8 INST_ACTION     = 0x05;
    static constexpr u8 INST_RESET      = 0x06;
    static constexpr u8 INST_SYNC_WRITE = 0x83;
  }

}

#endif//FEETECH_PROTOCOL_HPP
