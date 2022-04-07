//Generated on Thu Apr  7 17:02:54 2022
#ifndef DASH
#define DASH

#include <cstdint>
#include "hal_can.hpp"
#include "message_abstraction.hpp"

enum struct Dash_states: uint8_t {
	Power_up,
	Normal_operation,
	Driverless,
};

struct __attribute__ ((packed)) Dash_Main{
	Dash_states device_state; 
};

struct __attribute__ ((packed)) Dash_StateChange{
	uint8_t Driverless_mission; 
	uint8_t Knob_L; 
	uint8_t Knob_R; 
	uint8_t Lap_timer_command; // 
};


const uint16_t DASH_MAIN_CAN_ID = 0;
const uint8_t DASH_MAIN_CAN_DLC = sizeof(Dash_Main);
const uint8_t DASH_MAIN_FREQUENCY = 10;
const uint16_t DASH_STATECHANGE_CAN_ID = 0;
const uint8_t DASH_STATECHANGE_CAN_DLC = sizeof(Dash_StateChange);
const uint8_t DASH_STATECHANGE_FREQUENCY = 0;

const CAN_TxHeaderTypeDef can_tx_header_Dash{
DASH_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_Dash{
DASH_STATECHANGE_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, DASH_STATECHANGE_CAN_DLC, DISABLE};

#endif
