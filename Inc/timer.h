/*
 * timer.h
 *
 *  Created on: Nov 3, 2023
 *      Author: User
 */

#ifndef TIMER_H_
#define TIMER_H_

void tim2_1hz_init(void);
void tim2_PA5_output_compare(void);
void tim3_input_capture(void);

#define SR_UIF		(1U<<0)
#define SR_CC1IF	(1U<<1)
#endif /* TIMER_H_ */
