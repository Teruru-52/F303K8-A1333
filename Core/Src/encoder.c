#include "encoder.h"

uint16_t read_angle()
{
    uint8_t rx_data[2];
    uint8_t tx_data[2];
     tx_data[0] = 0x3F;
//    tx_data[0] = 0xEF; // 何故か読める
    tx_data[1] = 0xFF;
    // uint8_t tx_data = 0xFF;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 2, 10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

     int16_t data = (int16_t)((int16_t)(rx_data[0] | (0x3F & rx_data[1]) << 8));
//    int16_t data = (int16_t)((int16_t)(rx_data[0] << 8) | rx_data[1]);
    return data;
}

uint16_t read_flag(){
    uint8_t rx_data[2];
    uint8_t tx_data[2];
    tx_data[0] = 0x3F;
    tx_data[1] = 0xFD;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, tx_data, rx_data, 2, 10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

    int16_t data = (int16_t)((int16_t)(rx_data[0] << 8) | rx_data[1]);
    data &= 0x0FFF;

    // uint16_t rx_data;
    // uint16_t tx_data;
    // tx_data = 0x3FFD;

    // Write_GPIO(SPI1_CS, GPIO_PIN_RESET);
    // HAL_SPI_TransmitReceive(&hspi1, (uint8_t*)(tx_data), (uint8_t*)(rx_data), 2, 10);
    // Write_GPIO(SPI1_CS, GPIO_PIN_SET);

    // uint16_t data = rx_data & 0x0FFF;

    return data;
}

uint16_t ReadEncoder()
{
    int16_t angle_raw;

    // angle_raw = read_angle();
//    angle_raw = read_angle() & 0x3FFF; // AS5048A
    angle_raw = read_angle() & 0x7FFC; // AS5055A
    return angle_raw;

    // float angle = (float)(angle_raw) / 16384.0 * 2 * M_PI; // [rad]
    // return angle;
}
