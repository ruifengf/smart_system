#include "delay.h"

void Delay_Init(void)
{
    SysTick_Config(SystemCoreClock / 1000);
}

void Delay_ms(uint16_t time)
{
    while (time--)
    {
        SysTick->CTRL = 0;
        SysTick->LOAD = (168000)-1;
        SysTick->VAL = 0;
        SysTick->CTRL = 5;
        while (1)
        {
            if (SysTick->CTRL & 0x00010000)
            {
                break;
            }

            if ((SysTick->CTRL & 0x1) == 0)
            {
                return;
            }
             
        }
                
    }
    SysTick->CTRL = 0;
}

void Delay_us(uint16_t time)
{
    while (time--)
    {
        SysTick->CTRL = 0;
        SysTick->LOAD = (168)-1;
        SysTick->VAL = 0;
        SysTick->CTRL = 5;
        while (1)
        {
            if (SysTick->CTRL & 0x00010000)
            {
                break;
            }

            if ((SysTick->CTRL & 0x1) == 0)
            {
                return;
            }
             
        }
                
    }
    SysTick->CTRL = 0;
}
/*
void SysTick_Handler(void)
{
    static uint32_t counter = 0;
    counter++;

    if(counter > 500)
    {
        counter = 0;
        PAout(6) ^= 1;
    }
}
*/
