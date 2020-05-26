﻿/*
 * mcu_os.c
 *
 * Created: 24.01.2020 14:34:49
 *  Author: Dinar Talibullin
 */

#include "mcu_os.h"

static void (*task_p[MCU_OS_TASKS_COUNT])(void);
volatile static uint16_t task_c[MCU_OS_TASKS_COUNT];
volatile static uint16_t task_cc[MCU_OS_TASKS_COUNT]={0};
volatile static uint8_t task_cnt=0;
volatile static uint8_t GlobalShedulerFlags = 0;
volatile static uint16_t counter = 0;

void mcu_os_loop(void)
{
	for (int i=0; i<task_cnt; i++)
	{
		if (GlobalShedulerFlags&(1<<i))
		{
			task_p[i]();
			GlobalShedulerFlags&=~(1<<i);
		}
	}	
}

void mcu_os_init(void)
{
	mcu_os_timer_init();
	while (1)
	{
		mcu_os_loop();
	}	
}

int mcu_os_add_task(void (*pt2Func)(void), uint16_t period)
{
	task_p[task_cnt]=pt2Func;
	task_c[task_cnt]=period;
	task_cc[task_cnt]=counter;
	task_cnt++;
	if (task_cnt<=MCU_OS_TASKS_COUNT)
	{
		return task_cnt;
	}
	else
	{
		task_cnt=MCU_OS_TASKS_COUNT-1;
		return -1;
	}
}

int mcu_os_remove_last_task(void)
{
	if (task_cnt)
	{
		task_cnt--;
		return task_cnt;
	}
	else
	{
		return -1;
	}
}

void one_ms_callback(void)
{
	counter++;
	for (int i=0; i<task_cnt; i++)
	{
		if (counter-task_cc[i] == task_c[i])
		{
			task_cc[i]=counter;
			GlobalShedulerFlags|=(1<<i);
		}			
	}	
}