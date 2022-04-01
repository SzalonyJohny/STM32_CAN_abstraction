//Generated on Sat Apr  2 17:44:11 2022
#ifndef STEERING_WHEEL
#define STEERING_WHEEL

#include <cstdint>
#include "hal_can.hpp"
#include "message_abstraction.hpp"


enum struct buttonStates: uint8_t {
	button1,	//button1
	button2,	//button2
	button3,	//button3
	button4,	//button4
	button5,	//button1 + button2
	button6,	//button1 + button3
	button7,	//button1 + button4
	button8,	//button2 + button3
	button9,	//button2 + button4
	button10,	//button3 + button4
};

enum struct scrollStates: uint8_t {
	l_s_1,	//left_scroll_1
	l_s_2,	//left_scroll_2
	l_s_3,	//left_scroll_3
	l_s_4,	//left_scroll_4
	r_s_1,	//right_scroll_1
	r_s_2,	//right_scroll_2
	r_s_3,	//right_scroll_3
	r_s_4,	//right_scroll_4
};


enum struct Steering_Wheel_states: uint8_t {
	OK,
	Power_up,
	Normal_operation,
};

struct __attribute__ ((packed)) Steering_Wheel_main{
	int16_t s_w_a; // "steering wheel angle [-180
	Steering_Wheel_states device_state; // -----------------------------------------------------------------
};

struct __attribute__ ((packed)) Steering_Wheel_“Name”{
	uint8_t button; // see button state
	uint8_t l_s_1; // see button state
	uint8_t r_s_1; // see button state
};


const uint16_t STEERING_WHEEL_MAIN_CAN_ID = 0;
const uint8_t STEERING_WHEEL_MAIN_CAN_DLC = sizeof(Steering_Wheel_main);
const uint8_t STEERING_WHEEL_MAIN_FREQUENCY = 100;
const uint16_t STEERING_WHEEL_“NAME”_CAN_ID = 0;
const uint8_t STEERING_WHEEL_“NAME”_CAN_DLC = sizeof(Steering_Wheel_“Name”);
const uint8_t STEERING_WHEEL_“NAME”_FREQUENCY = 0;

const CAN_TxHeaderTypeDef can_tx_header_apps{
 APPS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_CAN_DLC, DISABLE};

#endif

