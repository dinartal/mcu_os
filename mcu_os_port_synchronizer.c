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
	period=600; //800Hz
	PR.PRPF&=~(PR_TC0_bm|PR_HIRES_bm); //enable power
	TCF0.CTRLB = 0;
	TCF0.PER = period;
	TCF0.INTCTRLA = TC_OVFINTLVL_LO_gc;
	TCF0.CTRLA = TC_CLKSEL_DIV64_gc;
}

ISR(TCF0_OVF_vect)
{
	one_ms_callback();
}

/*
	volatile static uint32_t counter, counter_1, counter_2, counter_3 = 0;
	
	counter++;
	
	if (counter-counter_1 == 80)
	{
		GlobalShedulerFlags|=(1<<0);
		counter_1=counter;
	}
	
	if (counter-counter_2 == 1)
	{
		GlobalShedulerFlags|=(1<<1);
		counter_2=counter;
	}

	if (counter-counter_3 == 800)
	{
		GlobalShedulerFlags|=(1<<2);
		counter_3=counter;
	}
	
*/