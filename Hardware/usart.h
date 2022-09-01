#ifndef USART_H
#define USART_H

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "sys.h"

#define TX1_PIN GPIO_Pin_9
#define RX1_PIN GPIO_Pin_10
#define USART1_PORT GPIOA

#define USART1_BAUDRATE 115200

void Usart1_Init(u32 BaudRate);
void show_str(const char* str);

#endif
