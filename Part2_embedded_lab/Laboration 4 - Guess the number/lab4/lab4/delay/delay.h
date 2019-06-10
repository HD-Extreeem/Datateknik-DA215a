/*
 * delay.h
 * 
 * These delay functions are external assembly subroutines.
 * See 'delay_asm.s' for details.
 *
 * Author:	Hadi Deknache
 *
 * Date:	2015-12-01
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

extern void delay_1_micros(void);
extern void delay_micros(uint8_t);
extern void delay_ms(uint8_t);
extern void delay_s(uint8_t);

#endif /* DELAY_H_ */