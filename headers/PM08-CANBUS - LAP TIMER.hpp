//Generated on Mon Mar 21 18:53:53 2022
#ifndef LAP_TIMER
#define LAP_TIMER

#include <cstdint>
#include "hal_can.hpp"
#include "message_abstraction.hpp"


enum struct Lap_timer_states: uint8_t {
	Waiting,
	Pass_detected,
};

struct __attribute__ ((packed)) Lap_timer_Pass{
	Lap_timer_states device_state; // --------------------------------
};


const uint16_t LAP_TIMER_PASS_CAN_ID = 0;
const uint8_t LAP_TIMER_PASS_CAN_DLC = sizeof(Lap_timer_Pass);

const CAN_TxHeaderTypeDef can_tx_header_apps{
 APPS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_CAN_DLC, DISABLE};

#endif

