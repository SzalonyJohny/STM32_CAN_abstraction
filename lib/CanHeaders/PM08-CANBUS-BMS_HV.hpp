//Generated on Thu Apr  7 17:02:54 2022
#ifndef BMS_HV
#define BMS_HV

#include <cstdint>
#include "hal_can.hpp"
#include "message_abstraction.hpp"

enum struct BMS_HV_states: uint8_t {
	AIR_opened,	// normal
	AIR_closed,	// normal
	Precharge,	// normal
	Charger_connected,	// normal
	Unbalanced,	// warning
	Unbalanced___critical,	// shut down
	Voltage_low,	// shut down
	Voltage_high,	// shut down
	Temp_high,	// shut down
	Current_high,	// shut down
};

struct __attribute__ ((packed)) BMS_HV_main{
	int16_t voltage_sum; 
	int8_t soc; // state of charge
	int8_t temp_max; 
	int8_t temp_avg; // in Celsius
	int8_t current; 
	BMS_HV_states device_state; 
};

struct __attribute__ ((packed)) BMS_HV_temperature{
	data type name; // comment
};


const uint16_t BMS_HV_MAIN_CAN_ID = 0;
const uint8_t BMS_HV_MAIN_CAN_DLC = sizeof(BMS_HV_main);
const uint8_t BMS_HV_MAIN_FREQUENCY = 100;
const uint16_t BMS_HV_TEMPERATURE_CAN_ID = 0;
const uint8_t BMS_HV_TEMPERATURE_CAN_DLC = sizeof(BMS_HV_temperature);
const uint8_t BMS_HV_TEMPERATURE_FREQUENCY = 1;

const CAN_TxHeaderTypeDef can_tx_header_BMS_HV{
BMS_HV_MAIN_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, BMS_HV_MAIN_CAN_DLC, DISABLE};

const CAN_TxHeaderTypeDef can_tx_header_BMS_HV{
BMS_HV_TEMPERATURE_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, BMS_HV_TEMPERATURE_CAN_DLC, DISABLE};

#endif

