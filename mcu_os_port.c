/*
 * mcu_os_port.c
 *
 * Created: 27.01.2020 16:24:39
 * Author: Dinar Talibullin
 */ 

#include <asf.h>
#include "mcu_os.h"

static uint16_t period;

void mcu_os_timer_init(void)
{
	//init timer for simple sheduler
	tc_enable(&TCC0);
	tc_set_overflow_interrupt_callback(&TCC0, one_ms_callback);
	tc_set_wgm(&TCC0, TC_WG_NORMAL);
	uint32_t per = sysclk_get_cpu_hz();
	per/=1000;
	per--;
	period=per;
	tc_write_period(&TCC0, period);
	tc_set_overflow_interrupt_level(&TCC0, TC_INT_LVL_LO);
	tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1_gc);
}

void mcu_os_delay_ticks(uint16_t ticks)
{
	uint16_t curr = TCC0.CNT;
	uint16_t end = (ticks + curr)%period;
	if (end > curr)
	{
		while (TCC0.CNT<end){}
	}
	else
	{
		while (TCC0.CNT>end){}
		while (TCC0.CNT<end){}
	}
}