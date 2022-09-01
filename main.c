#include "led.h"
#include "button.h"
#include "delay.h"
#include "tim.h"
#include "usart.h"
#include "ultrasound.h"

int main(void)
{
    //u32 duty = 100;
    u32 distance_cm = 0;
    u32 distance_mm = 0;
    //u32 loop = 32;

    LED_Init();
    Button_Init();
    Tim3_Init();
	Usart1_Init(115200);
    UlSound_Init();
    printf("hello handsome boy!!!");
    while(1)
    {		
		distance_cm = UlSound_Ranging();
        distance_mm = distance_cm %10;
        distance_cm = distance_cm/10;  
		printf("distance = %d.%dcm\r\n", distance_cm,distance_mm);
		Delay_ms(500);
#if 0		
		Delay_us(500000);
		LED_D3 ^= 1;
		Delay_us(500000);
		LED_D3 ^= 1;
#endif
#if 1
		Delay_ms(500);
		LED_D3 ^= 1;
		Delay_ms(500);
		LED_D3 ^= 1;
#endif
    }
}

void EXTI3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
       PAout(7) = 0;
       PAout(7) = 1;
    }
    else
    {
        
    }
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
       PAout(6) = 0;
       PAout(6) = 1;
    }
    else
    {
        
    }
	EXTI_ClearITPendingBit(EXTI_Line4);
}

