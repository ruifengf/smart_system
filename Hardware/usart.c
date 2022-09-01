#pragma import(__use_no_semihosting_swi)
#include <stdio.h>
#include "usart.h"
#include "led.h"

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return ch;
    
}
void _sys_exit(int return_code) {
label: goto label; /* endless loop */
}

void Usart1_Init(u32 BaudRate)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


    GPIO_InitStructure.GPIO_Pin = TX1_PIN | RX1_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(USART1_PORT, &GPIO_InitStructure);

    GPIO_PinAFConfig(USART1_PORT, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(USART1_PORT, GPIO_PinSource10, GPIO_AF_USART1);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
    USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
}
void USART1_IRQHandler(void)
{
   
    u8 data;
    u8 usart1_flag = 0xff;
    usart1_flag = USART_GetITStatus(USART1, USART_IT_RXNE);
    if (SET == usart1_flag)
    {
        data = USART_ReceiveData(USART1);
        if (0x01 == data)
        {
            LED_D3 ^= 1;
        }

        USART_SendData(USART1, data);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }

}                                        

void show_str(const char* str)
{
    while(*str != '\0')
	{		
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
        USART_SendData(USART1, *str);			
		str++;	
	}
}


