#ifndef MESSAGE_ABSTRACTION_H
#define MESSAGE_ABSTRACTION_H

#include "hal_can.hpp"
#include <cstdint>
#include <cstring>

static const std::size_t max_dlc_size = 8;

struct can_rx_message
{
  can_rx_message(CAN_HandleTypeDef &hcan, uint32_t RxFifo)
      : header{0}, data{0}
  {
    this->status =
        HAL_CAN_GetRxMessage(&hcan, RxFifo, &this->header, this->data);
  }

  CAN_RxHeaderTypeDef header;
  uint8_t data[max_dlc_size];
  HAL_StatusTypeDef status;
};

template <typename T>
struct can_tx_message
{
  can_tx_message(const T &data, const CAN_TxHeaderTypeDef &message_header)
      : header{message_header}
  {
    static_assert(std::is_trivially_constructible<T>(),
                  "Object must by C like struct");
    static_assert(std::is_class<T>(), "Object must by C like struct");
    std::memcpy(this->buff, &data, sizeof(T));
  }

  uint8_t buff[max_dlc_size];
  CAN_TxHeaderTypeDef header;
  HAL_StatusTypeDef send(CAN_HandleTypeDef &hcan, uint32_t *pTxMailbox)
  {
    return HAL_CAN_AddTxMessage(&hcan, &this->header, this->buff, pTxMailbox);
  }
};

class device_base
{
public:
  const uint32_t IDE;
  const uint32_t DLC;
  constexpr device_base(uint32_t ide, uint32_t dlc) : IDE{ide}, DLC{dlc} {}
  virtual void set_data(const can_rx_message &m) = 0;
};

template <typename T>
class device : public device_base
{
public:
  explicit constexpr device(uint32_t ide)
      : device_base(ide, sizeof(T)), data{0} {};

  T data;

  void set_data(const can_rx_message &m) override
  {
    std::memcpy(&data, m.data, sizeof(T));
  }
};

void print_can_message(const can_rx_message &m)
{
  printf("IDE: %d \n", (int)m.header.IDE);
  printf("DLC: %d \n", (int)m.header.DLC);
  for (std::size_t i = 0; i < max_dlc_size; ++i)
  {
    printf("data [%d] = %d \n", (int)i, (int)m.data[i]);
  }
  printf("status %d \n\n", m.status);
}

#endif