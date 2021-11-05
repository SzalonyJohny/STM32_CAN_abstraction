#ifndef APPS_DEF_H
#define APPS_DEF_H

#include <cstdint>

#include "hal_can.hpp"
#include "message_abstraction.hpp"

enum struct apps_status_struct : uint8_t
{
  ALL_OK,
  SENSOR_IMPLOSIBILITY,
  SUPPLY_VOLTAGE_INCORECT,
};

struct __attribute__((packed)) apps_data
{
  uint16_t apps_value;
  int16_t d_apps_dt;
  apps_status_struct apps_status;
};

const int APPS_CAN_ID = 0x01;
const int APPS_CAN_DLC = sizeof(apps_data);

const CAN_TxHeaderTypeDef can_tx_header_apps{
    APPS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_CAN_DLC, DISABLE};

#endif
