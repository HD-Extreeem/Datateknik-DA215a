/*
 * motor.c
 *
 * Created: 2015-12-18 14:54:27
 *  Author: Hadi Deknache
 *
 * Denna drivrutinen anvŠnder timer3
 * Hastigheten som sätts hämats från regulatorn
 * Timern anväder sig av 8-bitars fast mode timer och 16/64 timer frekvens
 *
 */ 
#include <avr/io.h>
#include "motor.h"

void motor_init(void){
	
//set PC6 (digital pin 5) as output
	DDRC = 1<<6;
	
//set OC3A PC6 to be cleared on compare match channel A
 	TCCR3A|= 1<<COM3A1;
//Waveform generation mode 5, fast PWM (8-bit)
	TCCR3A|= 1<<WGM30;
 	TCCR3B|= 1<<WGM32;
//Timer Clock, 16/64 Mhz = 1/4 Mhz
 	TCCR3B|=  1<<CS31 | 1<<CS30 ;
}

void motor_set_speed(uint8_t speed){ //Funktionen som sätter hastigheten för motorn
	OCR3A = speed;					 // värdet skickas till timern för att köra igång motorn
}