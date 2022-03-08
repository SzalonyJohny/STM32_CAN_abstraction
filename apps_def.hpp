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

struct __attribute__((packed)) Apps_data
{
  uint16_t apps_value;
  int16_t d_apps_dt;
  apps_status_struct apps_status;
};

enum struct Apps_error_type: uint8_t {
  sensor_implausibility,
  sensor_data_over_limit
};

struct __attribute__ ((packed)) Apps_error {
  Apps_error_type error;
};

const int APPS_CAN_ERROR_ID = 0x02;
const int APPS_CAN_ERROR_DLC = sizeof(Apps_error);

const int APPS_CAN_ID = 0x01;
const int APPS_CAN_DLC = sizeof(Apps_data);

const CAN_TxHeaderTypeDef can_tx_header_apps{
    APPS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_CAN_DLC, DISABLE};

#endif