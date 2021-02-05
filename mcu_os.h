/*
 * mcu_os.h
 *
 * Created: 24.01.2020 14:31:48
 * Author: Dinar Talibullin
 */ 


#ifndef MCU_OS_H_
#define MCU_OS_H_

#include "stdint.h"

#define MCU_OS_TASKS_COUNT 8

void mcu_os_timer_init(void);

void one_ms_callback(void);
void mcu_os_loop(void);
void mcu_os_init(void);
int mcu_os_add_task(void (*pt2Func)(void), uint16_t period);
int mcu_os_remove_last_task(void);
inline void mcu_os_delay_ticks(uint16_t ticks) __attribute__((always_inline));
inline void mcu_os_delay_ticks(uint16_t ticks)
{
	while (ticks--) asm(""); //1 tick = 9 CPU cycles
}

void mcu_os_sleep_init(void);
void mcu_os_sleep(void);

#endif /* MCU_OS_H_ */