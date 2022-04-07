#include <cstdint>
#include <iostream>

#include "can_interface.hpp"

using namespace new_can;

// global HAL CUBE_MX initialized data
CAN_HandleTypeDef hcan1;

// global can interface handle
Can_interface can;
// 
uint32_t TxMailbox = 3;

void interrupt_handler()
{
  Can_rx_message rx{hcan1, 1};

  if (rx.status == HAL_StatusTypeDef::HAL_OK)
  {
    can.get_message(rx);
  }
  else
  {
    // Error_handler("Error while reciving data from CAN");
  }
}

void recive_example()
{
  interrupt_handler();

  [[maybe_unused]]auto apps = can.get_apps_data();
  [[maybe_unused]]auto d = can.get_acquisition_card_data().wheel_time_interval_left;
}

void send_example()
{
  Apps_data apps_test;
  apps_test.apps_value = 1300;
  apps_test.d_apps_dt = 3;
  apps_test.apps_status = Apps_status_struct::ALL_OK;
  // example sending senario`
  auto tx = Can_tx_message(apps_test, can_tx_header_apps);
  auto res = tx.send(hcan1, &TxMailbox);
  if (res != HAL_StatusTypeDef::HAL_OK)
  {
    // Error_Handler("CAN sending error");
  };
}

void test_case_can_tx_message()
{
  Apps_data apps_test;
  apps_test.apps_status = Apps_status_struct::ALL_OK;
  apps_test.apps_value = 1300;
  apps_test.d_apps_dt = 3;

  // example sending senario
  auto tx = Can_tx_message(apps_test, can_tx_header_apps);
  auto res = tx.send(hcan1, &TxMailbox);
  if (res != HAL_StatusTypeDef::HAL_OK)
  {
    // Error_Handler("CAN sending error");
  };

  // copy tx to rx (CAN simulation)
  Can_rx_message rx{hcan1, 1};
  std::copy(tx.buff, tx.buff + sizeof(Apps_data), rx.data);

  // print rx buffor
  printf("\nbuffor: ");
  for (std::size_t i = 0; i < sizeof(Apps_data); ++i)
  {
    printf(" %d", (int)rx.data[i]);
  }
  // CAN recive data
  can.get_message(rx);
}

int main()
{
  test_case_can_tx_message();
}
