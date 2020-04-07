/*
 * Multimeter.c
 *
 * Created: 3/26/2020 10:58:36 PM
 * Author : Ahmed Hassan
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"
#include "dio.h"
#include "ohmmeter.h"
#include "dcvoltmeter.h"
#include "acvoltmeter.h"
#include "dcameter.h"
#define OHM 1
#define DCV 2
#define ACV 3
#define DCA 4
#define ACA 5
int main(void)
{
	u8 operation = 0;
	lcd_vid_init();
	lcd_vid_write_string(" Open OHM1-DCV2");
	lcd_vid_set_position(1,0);
	lcd_vid_write_string(" ACV3-DCA4-ACA5");
	dio_vid_set_port_direction(B,0);
    while (!operation) {
		u8 i;
		for (i=0; i<5; i++) {
			if(dio_u8_read_pin_value(B,i)) {
				operation = i+1;
				break;
			}
		}
	}
	switch (operation)
	{
		case OHM:
		run_ohmmeter();
		break;
		case DCV:
		run_dcvoltmeter();
		break;
		case ACV:
		run_acvoltmeter();
		break;
		case DCA:
		run_dcameter();
		break;
		case ACA:
		run_acameter();
		break;
	}
}

