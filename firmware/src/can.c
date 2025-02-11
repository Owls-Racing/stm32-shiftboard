#include "can.h"

CAN_HandleTypeDef hcan;
CAN_TxHeaderTypeDef shift_tx_header;
uint32_t can_mailbox;

static uint8_t gear = 0;
static uint16_t rpm = 0;
static uint16_t speed = 0;
static uint8_t ath = 0;

void can_init(void) {
    __HAL_RCC_CAN1_CLK_ENABLE();

    hcan.Instance = CAN1;
    hcan.Init.Prescaler = 16;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
    hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
    hcan.Init.TimeTriggeredMode = DISABLE;
    hcan.Init.AutoBusOff = ENABLE;
    hcan.Init.AutoWakeUp = ENABLE;
    hcan.Init.AutoRetransmission = ENABLE;
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = ENABLE;

    if (HAL_CAN_Init(&hcan) != HAL_OK) {
        error_handler();
    }

    shift_tx_header.StdId = 0x555;
    shift_tx_header.ExtId = 0;
    shift_tx_header.IDE = CAN_ID_STD;
    shift_tx_header.RTR = CAN_RTR_DATA;
    shift_tx_header.DLC = 2;
    shift_tx_header.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_Start(&hcan) != HAL_OK) {
        error_handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        error_handler();
    }
}

void can_handle(void) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t data[8];

    if (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) > 0) {
        if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &rx_header, data) == HAL_OK) {
            can_receive_callback(rx_header.StdId, data, rx_header.DLC);
        }
    }
}

void can_receive_callback(uint8_t message_id, uint8_t* data, uint8_t length) {
    if (message_id == 0x100) {
        gear = data[0];
    } else if (message_id == 0x200) {
        rpm = (data[0] << 8) | data[1];
    } else if (message_id == 0x300) {
        speed = (data[0] << 8) | data[1];
    } else if (message_id == 0x400) {
        ath = data[0];
    }
}

uint8_t can_get_gear(void) { return gear; }
uint16_t can_get_rpm(void) { return rpm; }
uint16_t can_get_speed(void) { return speed; }
uint8_t can_get_ath(void) { return ath; }

void can_send_shift_event(uint8_t upshift) {
    uint8_t shift_message[2];
    shift_message[0] = upshift ? 1 : 0;
    shift_message[1] = gear;

    if (HAL_CAN_AddTxMessage(&hcan, &shift_tx_header, shift_message, &can_mailbox) != HAL_OK) {
        error_handler();
    }
}
