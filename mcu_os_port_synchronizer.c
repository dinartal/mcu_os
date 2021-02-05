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
	period=479; //1000Hz; 599; //800Hz
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

//sleep port:
void mcu_os_sleep_init(void)
{
	//init sleep mode
	SLEEP.CTRL = SLEEP_SMODE_IDLE_gc | (SLEEP.CTRL & ~SLEEP_SMODE_gm);
	SLEEP.CTRL |= SLEEP_SEN_bm; //sleep enable
}

void mcu_os_sleep(void)
{
	sleep_enter();
}