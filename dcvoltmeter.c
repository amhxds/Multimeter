/*
 * dcvoltmeter.c
 *
 * Created: 3/26/2020 10:25:26 PM
 * Author : Ahmed Hassan
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"


void run_dcvoltmeter(void)
{
	f32 input_volt = 0.0;
	f32 temp=0.0;
	f32 r1=10000.0;    //r1 value
	f32 r2=100000.0;      //r2 value
	u16 analogvalue = 0;
	u16 milli_volt = 0;
    lcd_vid_init();
	adc_vid_init(3);
	lcd_vid_write_string(" DC Volt:");
	
	while (1) {
		while (!(adc_u8_get_result(&analogvalue))) {}
		temp = (analogvalue * 5.0) / 1023.0;       // FORMULA USED TO CONVERT THE VOLTAGE
		input_volt = temp / (r2/(r1+r2));
		milli_volt = input_volt*10000;
		lcd_vid_set_position(1,0);
		if (milli_volt>1000) {
			lcd_vid_write_number(milli_volt/1000);
			lcd_vid_write_string(".");
			lcd_vid_write_number(milli_volt%1000);
			lcd_vid_write_string(" V             ");
		}
		else {
			lcd_vid_write_number(milli_volt);
			lcd_vid_write_string(" mV            ");
		}
		

	}
	
}

