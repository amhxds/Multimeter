/*
 * acameter.c
 *
 * Created: 3/26/2020 9:27:32 PM
 * Author : Ahmed Hassan
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "types.h"
#include "adc.h"
#include "lcd.h"
#include "dio.h"

void run_acameter (void)
{
    u8 mVperAmp = 100; /* from ic datasheet*/
    f64 voltage = 0;
    f64 v_rms = 0;
    f64 amp_rms = 0;
    u32 milli_amp_rms = 0;
	lcd_vid_init();
	adc_vid_init(5);
	lcd_vid_write_string(" AC Current:");

    while (1){
	    u16 readValue;             //value read from the sensor
	    u16 maxValue = 0;          // store max value here
	    u16 minValue = 1024;          // store min value here
	    u16 i=0;
	    while(i < 1000) {
		    i++;
		    while (!(adc_u8_get_result(&readValue))) {}
		    // see if you have a new maxValue
		    if (readValue > maxValue) {
			    /*record the maximum sensor value*/
			    maxValue = readValue;
		    }
		    if (readValue < minValue) {
			    /*record the minimum sensor value*/
			    minValue = readValue;
		    }
	    }
	    // Subtract min from max
		voltage = maxValue - minValue;

	    voltage = (voltage * 5.0)/1023.0;		
	    v_rms = (voltage/2.0) *0.707;  //root 2 is 0.707
	    amp_rms = (v_rms * 1000)/mVperAmp;
		milli_amp_rms = amp_rms*1000;
	    lcd_vid_set_position(1,0);
		if (milli_amp_rms>1000) {
			lcd_vid_write_number(milli_amp_rms/1000);
			lcd_vid_write_string(".");
			lcd_vid_write_number(milli_amp_rms%1000);
			lcd_vid_write_string(" A          ");
		}
		else {
			lcd_vid_write_number(milli_amp_rms%1000);
			lcd_vid_write_string(" mA          ");
		}
	}
}