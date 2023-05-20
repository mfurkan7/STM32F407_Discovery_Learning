/*
 * adc.h
 *
 *  Created on: 9 May 2023
 *      Author: M.Furkan Eren
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc3_init(void);
uint32_t adc_read(void);
void adc_start_conversion(void);

#endif /* ADC_H_ */
