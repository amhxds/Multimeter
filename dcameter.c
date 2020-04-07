/*
 * dcameter.c
 *
 * Created: 3/26/2020 6:40:25 PM
 * Author : Ahmed Hassan
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"

void run_dcameter(void)
{
	u16 output = 0;
	u16 analog_volt = 0;
	f32 voltage_diffrence=0;
    lcd_vid_init();
	adc_vid_init(16);
	lcd_vid_write_string(" DC Current:");
	while(1)
	{		
		while (!(adc_u8_get_result(&analog_volt))) {}
		voltage_diffrence = (analog_volt)*5000.0 / 1023;
		output = voltage_diffrence / 0.5;
		lcd_vid_set_position(1,0);
		if (output>1000) {
			lcd_vid_write_number(output/1000);
			lcd_vid_write_string(".");
			lcd_vid_write_number(output%1000);
			lcd_vid_write_string(" A          ");
		}
		else {
			lcd_vid_write_number(output);
			lcd_vid_write_string(" mA          ");
		}
	}
}

