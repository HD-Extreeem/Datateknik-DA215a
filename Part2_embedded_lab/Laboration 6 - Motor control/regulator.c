/*
 * temp.c
 *
 * This is the device driver for the motor.
 *
 * Author:	Hadi Deknache
 *
 * Date:	2015-12-07
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"

/*	For storage of ADC value from motor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint16_t adc = 255;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
	// read ADC value
	//Läs in ADC-värdet. Börja med att läsa av det "låga" registret, därefter det "höga" registret!
	uint8_t low,high;
	low = ADCL;
	high = ADCH;
	
	adc = (high<<8) +low;
	
}

/*
 * Initialize the ADC and ISR.
 */
void regulator_init(void)
{
	// UPPGIFT: konfigurera ADC-enheten genom ställa in ADMUX och ADCSRA enligt kommentarerna nedanför!
	ADMUX |= (1<<REFS0);				// set reference voltage (internal 5V)
	ADMUX |= (1<<MUX0);					// select diff.amp 10x on ADC1
					
	
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1)| (1<<ADPS0);		// prescaler 128
	ADCSRA |= (1<<ADATE);								// enable Auto Trigger
	ADCSRA |= (1<<ADIE);								// enable Interrupt
	ADCSRA |= (1<<ADEN);								// enable ADC

	// disable digital input on ADC1
	DIDR0 = 1;
		
	// disable USB controller (to make interrupts possible)
	USBCON = 0;	
	// enable global interrupts
	sei();

	// start initial conversion
	ADCSRA |= (1<<ADSC);				//gör så att den initiala A/D-omvandlingen sker
}

/*
 * Returns the temperature in Celsius.
 */
uint8_t regulator(void)
{
	uint16_t adc_correction = adc * 25;			//Lägger multiplicera med 25 för att skapa en 0-100 stege
	uint16_t temp = adc_correction / 255;		//Dividerar med 255
	return (uint8_t) temp;						//Returnerar talet mellan 0-100
}
