//Generated on Mon Mar 28 16:20:12 2022
#ifndef AQ
#define AQ

#include <cstdint>
#include "hal_can.hpp"
#include "message_abstraction.hpp"

enum struct AQ_states: uint8_t {
	Power_up,
	Normal_operation,
	Sensor_impossibility,
};

struct __attribute__ ((packed)) AQ_main{
	uint16_t wheel_speed_right; // rotation wheel speed rpm
	uint16_t wheel_speed_left; // rotation wheel speed rpm
	uint16_t break_pressure; // pressure of braking lquid front
	AQ_states device_state; // -----------------------------------------------------------------
};

struct __attribute__ ((packed)) AQ_“Name”{
	uint16_t air_flow_velocity; // rotation wheel speed rpm
};

const uint16_t AQ_MAIN_CAN_ID = 0;
const uint8_t AQ_MAIN_CAN_DLC = sizeof(AQ_main);
const uint16_t AQ_“NAME”_CAN_ID = 0;
const uint8_t AQ_“NAME”_CAN_DLC = sizeof(AQ_“Name”);

const CAN_TxHeaderTypeDef can_tx_header_apps{
 APPS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_CAN_DLC, DISABLE};

#endif

