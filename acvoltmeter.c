/*
 * ACVoltmeter.c
 *
 * Created: 3/26/2020 2:30:53 PM
 * Author : Ahmed Hassan
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"

u16 get_max() {
	u16 max_v = 0;
	u8 i;
	for(i = 0; i < 100; i++) {
		u16 r;
		while (!(adc_u8_get_result(&r))) {}
		if(max_v < r) max_v = r;
		_delay_us(200);
	}
	return max_v;
}

void run_acvoltmeter (void)
{
	u32 v;
	lcd_vid_init();
	adc_vid_init(2);
	lcd_vid_write_string(" AC Voltage:");
	while (1) {
		v = get_max();
		v = (v*5000)/1023;
		lcd_vid_set_position(1,0);
		lcd_vid_write_number(v);
		lcd_vid_write_string(" V      ");
		_delay_ms(500);
	}    
}
