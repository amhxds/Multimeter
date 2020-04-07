/*
 * ADC.h
 *
 *  Created on: Oct 5, 2019
 *      Author: Ahmed Hassan
 */

#ifndef ADC_H_
#define ADC_H_
void adc_vid_init(u8 pin);
void adc_start(void);
u8 adc_u8_get_result(u16* result);
#endif /* ADC_H_ */
