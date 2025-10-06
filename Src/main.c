#include "stm32f4xx.h"
#include "hcsr04.h"
#include "uart.h"
#include "timing.h"
#include "buzz.h"
#include <stdio.h>

// Define the duration of each beep in milliseconds
#define BEEP_DURATION_MS 50

int main(void)
{
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
    uart2_tx_init();
    HCSR04_Init();
    DWT_Delay_Init();
    buzzer_init();

    RCC->AHB1ENR |= (1U << 0);
    GPIOA->MODER |= (1U << 10) | (1U << 12) | (1U << 14); // Set PA5, PA6, PA7 as output

    int32_t distance;

    while(1)
    {
        distance = HCSR04_ReadDistance_cm_x100(30);

        if(distance > 0)
        {
            printf("Distance: %d.%02d cm\r\n", distance / 100, distance % 100);
        }
        else
        {
            printf("Distance: Out of range\r\n");
        }

        if(distance > 0 && distance < 1000)
        {
            GPIOA->ODR = (1 << 5); // Red ON, others OFF
        }
        else if(distance >= 1000 && distance < 3000 )
        {
        	GPIOA->ODR = (1 << 6); // Yellow ON, others OFF
        }
        else if(distance >= 3000 )
        {
            GPIOA->ODR = (1 << 7); // Green ON, others OFF
        }
        else
        {
            GPIOA->ODR &= ~((1 << 5) | (1 << 6) | (1 << 7)); // All OFF
        }

        if (distance > 0 && distance <= 3000)
        {
            // Map distance (1-3000) to a beep interval
            const uint32_t INTERVAL_MAX_MS = 500; // Delay at 30cm
            const uint32_t INTERVAL_MIN_MS = 65;  // Delay at <1cm
            const uint32_t D_MAX_VAL = 3000;

            // Calculate the delay between the start of one beep and the start of the next
            uint32_t beep_interval_ms = INTERVAL_MIN_MS + (((uint64_t)distance * (INTERVAL_MAX_MS - INTERVAL_MIN_MS)) / D_MAX_VAL);

            // Turn the beep on
            buzzer_on();
            delay_us(BEEP_DURATION_MS * 1000); // Beep for a fixed duration

            // Turn the beep off
            buzzer_off();

            // Wait for the rest of the interval before the next beep
            if (beep_interval_ms > BEEP_DURATION_MS)
            {
                delay_us((beep_interval_ms - BEEP_DURATION_MS) * 1000);
            }
        }
        else
        {
            // If out of range, just wait a bit to keep the loop from running too fast
            delay_us(50000); // 50ms delay
        }
    }
}
