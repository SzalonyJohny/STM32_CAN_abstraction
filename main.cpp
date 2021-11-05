#include <cstdint>
#include <iostream>

#include "can_interface.hpp"

using namespace new_can;

// global HAL CUBE_MX initialized data
CAN_HandleTypeDef hcan1;

// global can interface handle
can_interface can;
// 
uint32_t TxMailbox = 3;

void interrupt_handler()
{
  can_rx_message rx{hcan1, 1};

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
  can.disp();
  interrupt_handler();

  [[maybe_unused]]auto apps = can.get_apps_data();
  [[maybe_unused]]auto d = can.get_acquisition_card_data().wheel_time_interval_left;
  
  can.disp();
}

void send_example()
{
  apps_data apps_test;
  apps_test.apps_value = 1300;
  apps_test.d_apps_dt = 3;
  apps_test.apps_status = apps_status_struct::ALL_OK;
  // example sending senario`
  auto tx = can_tx_message(apps_test, can_tx_header_apps);
  auto res = tx.send(hcan1, &TxMailbox);
  if (res != HAL_StatusTypeDef::HAL_OK)
  {
    // Error_Handler("CAN sending error");
  };
}

void test_case_can_tx_message()
{
  apps_data apps_test;
  apps_test.apps_status = apps_status_struct::ALL_OK;
  apps_test.apps_value = 1300;
  apps_test.d_apps_dt = 3;

  // example sending senario
  auto tx = can_tx_message(apps_test, can_tx_header_apps);
  auto res = tx.send(hcan1, &TxMailbox);
  if (res != HAL_StatusTypeDef::HAL_OK)
  {
    // Error_Handler("CAN sending error");
  };

  // copy tx to rx (CAN simulation)
  can_rx_message rx{hcan1, 1};
  std::copy(tx.buff, tx.buff + sizeof(apps_data), rx.data);

  can.disp();

  // print rx buffor
  printf("\nbuffor: ");
  for (std::size_t i = 0; i < sizeof(apps_data); ++i)
  {
    printf(" %d", (int)rx.data[i]);
  }
  printf("\n\n");

  // CAN recive data
  can.get_message(rx);

  can.disp();

  printf("\n");
}

int main()
{
  test_case_can_tx_message();
}
