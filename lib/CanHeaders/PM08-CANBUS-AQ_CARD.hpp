//Generated on Thu Apr  7 17:02:53 2022
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
	uint16_t adc_susp_right; 
	uint16_t adc_susp_left; // i brake balance
	uint8_t break_pressure; // pressure of braking lquid front in %
	uint8_t break_pressure; // pressure of braking lquid back in %
};

struct __attribute__ ((packed)) AQ_air_flow{
	uint16_t air_flow_velocity; // rotation wheel speed rpm
};


const uint16_t AQ_MAIN_CAN_ID = 0;
const uint8_t AQ_MAIN_CAN_DLC = sizeof(AQ_main);
const uint8_t AQ_MAIN_FREQUENCY = 100;
const uint16_t AQ_AIR_FLOW_CAN_ID = 0;
const uint8_t AQ_AIR_FLOW_CAN_DLC = sizeof(AQ_air_flow);
const uint8_t AQ_AIR_FLOW_REQUENCY = 695844480;


const CAN_TxHeaderTypeDef can_tx_header_AQ{
AQ_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AQ_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_AQ{
AQ_AIR_FLOW_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, AQ_AIR_FLOW_CAN_DLC, DISABLE};


#endif

