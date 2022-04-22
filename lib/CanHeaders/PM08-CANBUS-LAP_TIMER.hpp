//Generated on Fri Apr 22 12:03:14 2022
#ifndef LAP_TIMER
#define LAP_TIMER

#include <cstdint>
#include "hal_can.hpp"
#include "message_abstraction.hpp"

enum struct Lap_timer_states: uint8_t {
	Power_up,
	Pass_detected,
};

struct __attribute__ ((packed)) Lap_timer_Main{
	Lap_timer_states device_state; 
};

struct __attribute__ ((packed)) Lap_timer_StateChange{
	uint8_t Pass_detected; // 
};


const uint16_t LAP_TIMER_MAIN_CAN_ID = 0;
const uint8_t LAP_TIMER_MAIN_CAN_DLC = sizeof(Lap_timer_Main);
const uint8_t LAP_TIMER_MAIN_FREQUENCY = 5;
const uint16_t LAP_TIMER_STATECHANGE_CAN_ID = 0;
const uint8_t LAP_TIMER_STATECHANGE_CAN_DLC = sizeof(Lap_timer_StateChange);
const uint8_t LAP_TIMER_STATECHANGE_FREQUENCY = 0;

const CAN_TxHeaderTypeDef can_tx_header_LAP_TIMER_MAIN{
LAP_TIMER_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, LAP_TIMER_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_LAP_TIMER_STATECHANGE{
LAP_TIMER_STATECHANGE_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, LAP_TIMER_STATECHANGE_CAN_DLC, DISABLE};

#endif

