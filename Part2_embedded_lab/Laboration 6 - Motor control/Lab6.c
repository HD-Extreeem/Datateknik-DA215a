/*
 * Lab6.c
 *
 * Created: 2015-12-18 09:56:14
 *  Author: Hadi Deknache
 *
 * Denna fil använder sig av en subrutin som går igenom varje tillstånd
 * Dem olika tillitånden som kan uppstå är motor_off,motor_on och motor_running
 * Värdet pŒ hastigheten sätas genom motor.c filen
 * 
 */ 
#include <stdio.h>
#include <avr/io.h>
#include "hmi/hmi.h"
#include "delay/delay.h"
#include "numkey/numkey.h"
#include "lcd/lcd.h"
#include "common.h"
#include "regulator/regulator.h"
#include "motor/motor.h"

enum state {			//Definierar dem olika tillstånden vi använder oss av
	MOTOR_OFF,
	MOTOR_ON,
	MOTOR_RUNNING
};


typedef enum state state_t; //Dessa typdefinieras till ett state_t objekt

int main(void){
	
	hmi_init();
	regulator_init();
	motor_init();
	
	char regulator_str [17]; //skapar en temp sträng med 16 tomma och en för cursorn
	
	uint16_t key;			//Skapar key

    state_t current_state= MOTOR_OFF;	//anger den nuvarande tillståndet till MOTOR_OFF för att börja i det som standard
    state_t next_state= MOTOR_OFF;		//anger nästa tillståndet till MOTOR_OFF för att börja i det som standard
	
	
while (1){	
		key= numkey_read();				//läser in kanppen till key
		
	switch (current_state){				//Bytar state beroende på vad current_state är
			
		case MOTOR_OFF:
			
			if (key =='2')											//Om key 2 är nedtryckt
			{
				next_state=MOTOR_ON;								//Isåfall är nästa state motor_on
			}
				output_msg("Motor is off!","",0);					//Skriver ut meddelandet på lcdn
				motor_set_speed(0);									//Sätter hastigheten vid off till 0 eftersom den ej ska snurra då
				break;
				
		case MOTOR_ON:
		
			if (key=='1')											//Kollar ifall knappen 1 är nedtryckt
			{
				next_state=MOTOR_OFF;								//Isådanafall så är nästa state motor_off
			}
			else if (regulator()>0)									//Annars om hastigheten är störren än 0 så körs motor_running
			{
				next_state = MOTOR_RUNNING;							//Nästa state blir motor running
			}
				sprintf(regulator_str, "%u%%", regulator());		//Använder sprintf för att skriva ut temp strängen+ tecknet och läser tempen till temp_str
				motor_set_speed(0);									//Sätter hastigheten vid off till 0 eftersom den ej ska snurra då
				output_msg("Motor is on!", regulator_str,0);		//Skriver ut meddelandet på lcdn med värdet i regulator
				break;												//avbryter hela case satsen
		case MOTOR_RUNNING:
		
			if (key=='1')											//Om key är 1 så...		
			{
				next_state=MOTOR_OFF;								//Nästa state är då motor_off
			}
				sprintf(regulator_str, "%u%%", regulator());		//Använder sprintf för att skriva ut temp strängen+ tecknet och läser tempen till temp_str
				output_msg("Motor running:", regulator_str,0);		//Skriver ut meddelandet på lcdn med värdet i regulator
				motor_set_speed(regulator()*2.55);					//Sätter hastigheten till värdet i regulator*255 eftersom värdet är 0-100 men vi vill ha 0-255 till speed
				break;
			}
		current_state = next_state;									//Nästa är samma som nuvarande tillstånd för att loopa igenom tills ny knapp trycks ner 						
	}	

}