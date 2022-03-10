#ifndef ACQUISITION_CARD_H
#define ACQUISITION_CARD_H

#include <cstdint>

#include "hal_can.hpp"
#include "message_abstraction.hpp"

enum struct Acquisition_card_status_struct : uint8_t
{
  ALL_OK,
  COS_SIE_rozwalilo,
  SUPPLY_VOLTAGE_INCORECT,
  Bateria_laduje
};

struct __attribute__((packed)) Acquisition_card_data
{
  uint32_t wheel_time_interval_left;
  uint32_t wheel_time_interval_right;
  Acquisition_card_status_struct ac_status =
      Acquisition_card_status_struct::ALL_OK;
};

const int AC_CAN_ID = 0x02;
const int AC_CAN_DLC = sizeof(Acquisition_card_data);

const CAN_TxHeaderTypeDef CAN_TX_HEADER_AC{
    AC_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AC_CAN_DLC, DISABLE};

#endif