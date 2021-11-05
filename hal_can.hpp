#ifndef HAL_CAN_H
#define HAL_CAN_H

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
  aData[0] = 28;
  aData[1] = 2;
  aData[2] = 13;
  aData[3] = 0;
  aData[4] = 1;
  pHeader->IDE = 1;
  pHeader->DLC = 4;
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

#endif