/*
 * time.h
 *
 *  Created on: May 13, 2023
 *      Author: M.Furkan Eren
 */

#ifndef TIME_H_
#define TIME_H_


void tim2_1Hz_init(void);
void tim4_PD12_CCM_init(void);
void tim3_PB4_CCM_init(void);
#define TIM3_SR_CC1IF		(1U<<1)

#endif /* TIME_H_ */
