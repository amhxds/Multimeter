/*
 * ohmmeter.c
 *
 * Created: 3/26/2020 11:04:43 PM
 *  Author: Ahmed Hassan
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"
#include "dio.h"
const u32 res_table[5] = {100, 1000, 10000, 100000, 2000000};
u32 res;
void run_ohmmeter (void)
{

	u16 volt_image;
	u8 ch_number=4;
	dio_vid_set_port_direction(C,255);
	lcd_vid_init();
	adc_vid_init(4);
	lcd_vid_write_string(" Resistance:           ");
	ch_select(ch_number);
	
	while (1) {
		while (!(adc_u8_get_result(&volt_image))) {}
		if(volt_image >= 550 && ch_number < 4) {
			ch_number++;
			ch_select(ch_number);
			_delay_ms(50);
			continue;
		}
		if(volt_image <= 90 && ch_number > 0) {
			ch_number--;
			ch_select(ch_number);
			_delay_ms(50);
			continue;
		}
		lcd_vid_set_position(1,0);
		if(volt_image < 900) {
			u32 value = volt_image*res/(1023 - volt_image);
			if (value>1000) {
				lcd_vid_write_number(value/1000);
				lcd_vid_write_string(".");
				lcd_vid_write_number(value%1000);
				lcd_vid_write_string(" kohm          ");
			}
			else {
				lcd_vid_write_number(value%1000);
				lcd_vid_write_string(" ohm          ");
			}
		}
		
		else
		lcd_vid_write_string("INFINITY              ");
		_delay_ms(500);
	}
}

void ch_select(u8 n) {
	switch(n) {
		case 0:
		dio_vid_set_pin_value(C,0,0);
		dio_vid_set_pin_value(C,1,1);
		dio_vid_set_pin_value(C,2,1);
		dio_vid_set_pin_value(C,3,1);
		dio_vid_set_pin_value(C,4,1);
		break;
		case 1:
		dio_vid_set_pin_value(C,0,1);
		dio_vid_set_pin_value(C,1,0);
		dio_vid_set_pin_value(C,2,1);
		dio_vid_set_pin_value(C,3,1);
		dio_vid_set_pin_value(C,4,1);
		break;
		case 2:
		dio_vid_set_pin_value(C,0,1);
		dio_vid_set_pin_value(C,1,1);
		dio_vid_set_pin_value(C,2,0);
		dio_vid_set_pin_value(C,3,1);
		dio_vid_set_pin_value(C,4,1);
		break;
		case 3:
		dio_vid_set_pin_value(C,0,1);
		dio_vid_set_pin_value(C,1,1);
		dio_vid_set_pin_value(C,2,1);
		dio_vid_set_pin_value(C,3,0);
		dio_vid_set_pin_value(C,4,1);
		break;
		case 4:
		dio_vid_set_pin_value(C,0,1);
		dio_vid_set_pin_value(C,1,1);
		dio_vid_set_pin_value(C,2,1);
		dio_vid_set_pin_value(C,3,1);
		dio_vid_set_pin_value(C,4,0);
	}
	res = res_table[n];
}