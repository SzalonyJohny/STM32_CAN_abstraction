#include<array>
#include<algorithm>
#include<numeric>
#include<span>
#include<stdio.h>
#include <stdio.h>
#include <string.h>
#include <cstring>

#include <array>
#include <memory>
#include <stdio.h>


typedef struct {
  uint32_t StdId; /*!< Specifies the standard identifier.
                       This parameter must be a number between Min_Data = 0 and
                     Max_Data = 0x7FF. */

  uint32_t ExtId; /*!< Specifies the extended identifier.
                       This parameter must be a number between Min_Data = 0 and
                     Max_Data = 0x1FFFFFFF. */

  uint32_t IDE; /*!< Specifies the type of identifier for the message that will
                   be transmitted. This parameter can be a value of @ref
                   CAN_identifier_type */

  uint32_t RTR; /*!< Specifies the type of frame for the message that will be
                   transmitted. This parameter can be a value of @ref
                   CAN_remote_transmission_request */

  uint32_t DLC; /*!< Specifies the length of the frame that will be transmitted.
                     This parameter must be a number between Min_Data = 0 and
                   Max_Data = 8. */

  uint32_t Timestamp; /*!< Specifies the timestamp counter value captured on
                         start of frame reception.
                          @note: Time Triggered Communication Mode must be
                         enabled. This parameter must be a number between
                         Min_Data = 0 and Max_Data = 0xFFFF. */

  uint32_t FilterMatchIndex; /*!< Specifies the index of matching acceptance
                          filter element. This parameter must be a number
                          between Min_Data = 0 and Max_Data = 0xFF. */

} CAN_RxHeaderTypeDef;

typedef enum { DISABLE = 0, ENABLE = !DISABLE } FunctionalState;

/**
 * @brief  CAN Tx message header structure definition
 */
typedef struct {
  uint32_t StdId; /*!< Specifies the standard identifier.
                       This parameter must be a number between Min_Data = 0 and
                     Max_Data = 0x7FF. */

  uint32_t ExtId; /*!< Specifies the extended identifier.
                       This parameter must be a number between Min_Data = 0 and
                     Max_Data = 0x1FFFFFFF. */

  uint32_t IDE; /*!< Specifies the type of identifier for the message that will
                   be transmitted. This parameter can be a value of @ref
                   CAN_identifier_type */

  uint32_t RTR; /*!< Specifies the type of frame for the message that will be
                   transmitted. This parameter can be a value of @ref
                   CAN_remote_transmission_request */

  uint32_t DLC; /*!< Specifies the length of the frame that will be transmitted.
                     This parameter must be a number between Min_Data = 0 and
                   Max_Data = 8. */

  FunctionalState
      TransmitGlobalTime; /*!< Specifies whether the timestamp counter value
              captured on start of frame transmission, is sent in DATA6 and
              DATA7 replacing pData[6] and pData[7].
              @note: Time Triggered Communication Mode must be enabled.
              @note: DLC must be programmed as 8 bytes, in order these 2 bytes
              are sent. This parameter can be set to ENABLE or DISABLE. */

} CAN_TxHeaderTypeDef;

typedef enum {
  HAL_OK = 0x00U,
  HAL_ERROR = 0x01U,
  HAL_BUSY = 0x02U,
  HAL_TIMEOUT = 0x03U
} HAL_StatusTypeDef;

typedef struct {
} CAN_HandleTypeDef;

HAL_StatusTypeDef HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, uint32_t RxFifo,
                                       CAN_RxHeaderTypeDef *pHeader,
                                       uint8_t aData[]) {
  // test senario
  aData[0] = rand()%123;
  aData[1] = 2;
  aData[2] = rand()%123;
  aData[3] = rand()%123;
  aData[4] = rand()%123;
  aData[5] = rand()%123;
  aData[6] = rand()%123;
  pHeader->IDE = rand()%5 + 1;
  pHeader->DLC = rand()%5 + 1;
  return HAL_StatusTypeDef::HAL_OK;
}

HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan,
                                       CAN_TxHeaderTypeDef *pHeader,
                                       uint8_t aData[], uint32_t *pTxMailbox) {
  return HAL_StatusTypeDef::HAL_OK;
}

#define CAN_RTR_DATA (0x00000000U)   /*!< Data frame   */
#define CAN_RTR_REMOTE (0x00000002U) /*!< Remote frame */

#define CAN_ID_STD (0x00000000U) /*!< Standard Id */
#define CAN_ID_EXT (0x00000004U)



static const std::size_t max_dlc_size = 8;

struct can_rx_message {
  can_rx_message(CAN_HandleTypeDef *hcan, uint32_t RxFifo)
      : header{0}, data{0} {
    this->status =
        HAL_CAN_GetRxMessage(hcan, RxFifo, &this->header, this->data);
  }

  CAN_RxHeaderTypeDef header;
  uint8_t data[max_dlc_size];
  HAL_StatusTypeDef status;
};

template <typename T> struct can_tx_message {
  can_tx_message(T data, CAN_TxHeaderTypeDef message_header)
      : header{message_header} {
    static_assert(std::is_trivially_constructible<T>(),
                  "Object must by C like struct");
    static_assert(std::is_class<T>(), "Object must by C like struct");
    std::memcpy(this->buff, &data, sizeof(T));
  }

  uint8_t buff[max_dlc_size];
  CAN_TxHeaderTypeDef header;
  HAL_StatusTypeDef send(CAN_HandleTypeDef *hcan, uint32_t *pTxMailbox) {
    return HAL_CAN_AddTxMessage(hcan, &this->header, this->buff, pTxMailbox);
  }
};

class device_base {
public:
  const uint32_t IDE;
  const uint32_t DLC;
  constexpr device_base(uint32_t ide, uint32_t dlc) : IDE{ide}, DLC{dlc} {}
  virtual void set_data(can_rx_message &m) = 0;
};

enum struct apps_status_struct : uint8_t {
  ALL_OK,
  SENSOR_IMPLOSIBILITY,
  SUPPLY_VOLTAGE_INCORECT,
};

struct __attribute__((packed)) apps_data {
  uint16_t apps_value;
  int16_t d_apps_dt;
  apps_status_struct apps_status;
};

class apps_c : public device_base {
public:
  constexpr apps_c(uint32_t ide, uint32_t dlc)
      : device_base(ide, dlc), data{0} {};

  apps_data data;

  void set_data(can_rx_message &m) override {
    std::memcpy(&data, &m.data[0], sizeof(apps_data));
  }
};

namespace apps_const {
const int APPS_CAN_ID = 0x0A;
const int APPS_CAN_DLC = sizeof(apps_data);
const CAN_TxHeaderTypeDef can_tx_header_apps{
    APPS_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, APPS_CAN_DLC, DISABLE};
}


enum struct acquisition_card_status_struct : uint8_t {
  ALL_OK,
  COS_SIE_rozwalilo,
  SUPPLY_VOLTAGE_INCORECT,
};

struct __attribute__((packed)) acquisition_card_data {
  uint32_t wheel_time_interval_left;
  uint32_t wheel_time_interval_right;
  acquisition_card_status_struct apps_status =
      acquisition_card_status_struct::ALL_OK;
};

class acquisition_card_c : public device_base {
public:
  constexpr acquisition_card_c(uint32_t ide, uint32_t dlc)
      : device_base(ide, dlc), data{0} {};

  acquisition_card_data data;

  void set_data(can_rx_message &m) override {
    std::memcpy(&data, &m.data[0], sizeof(acquisition_card_data));
  }
};

namespace new_can {

class can_interface {

  apps_c apps{1, 3};
  acquisition_card_c ac{2, 4};

  apps_c apps2{3, 3};
  acquisition_card_c ac2{4, 4};
  
  apps_c apps3{5, 3};
  acquisition_card_c ac3{6, 4};


  std::array<device_base *, 8> device_array = {&apps, &ac, &apps2, &ac2, &apps3, &ac3};

public:
  void disp() {
    printf("Apps IDE: %d \n", (int)apps.IDE);
    printf("Apps status: %d \n", (int)apps.data.apps_status);
    printf("Apps value: %d \n", apps.data.apps_value);
    printf("Apps d_dt: %d \n\n", apps.data.d_apps_dt);
  }

  void get_message(can_rx_message &m) {
    for (auto &dev : device_array) {
      if (dev->IDE == m.header.IDE) {
        dev->set_data(m);
        return; // to exit void
      }
    }
  }

  void get_message_2(can_rx_message &m) {
      if(apps.IDE == m.header.IDE){
        apps.set_data(m);
        return;
      }
      else if(ac.IDE == m.header.IDE){
        ac.set_data(m);
        return;
      }
      if(apps2.IDE == m.header.IDE){
        apps2.set_data(m);
        return;
      }
      else if(ac2.IDE == m.header.IDE){
        ac2.set_data(m);
        return;
      }
      if(apps3.IDE == m.header.IDE){
        apps3.set_data(m);
        return;
      }
      else if(ac3.IDE == m.header.IDE){
        ac3.set_data(m);
        return;
      }



  }

  apps_data get_apps_data() { return apps.data; }

  acquisition_card_data get_acquisition_card_data() { return ac.data; }
};

} // namespace new_can




static void get_message(benchmark::State& state) {

  // global HAL CUBE_MX initialized data
  CAN_HandleTypeDef hcan1;

  // global can interface handle
  new_can::can_interface can;
  // Code inside this loop is measured repeatedly
  for (auto _ : state) {
    can_rx_message rx{&hcan1, 1};
    if (rx.status == HAL_StatusTypeDef::HAL_OK) {
      can.get_message(rx);
    } else {
    // Error_Handeler("Error in reciving data from can");
  }
    benchmark::DoNotOptimize(can);
  }
}
// Register the function as a benchmark
BENCHMARK(get_message);

static void get_message_2(benchmark::State& state) {

  // global HAL CUBE_MX initialized data
  CAN_HandleTypeDef hcan1;

  // global can interface handle
  new_can::can_interface can;

  for (auto _ : state) {
    can_rx_message rx{&hcan1, 1};
    if (rx.status == HAL_StatusTypeDef::HAL_OK) {
      can.get_message_2(rx);
    } else {
      // Error_Handeler("Error in reciving data from can");
  }
      benchmark::DoNotOptimize(can);
  }
}
BENCHMARK(get_message_2);

