/*
 * Lab6.c
 *
 * Created: 2015-12-18 09:56:14
 *  Author: Hadi Deknache
 *
 * Denna fil anv�nder sig av en subrutin som g�r igenom varje tillst�nd
 * Dem olika tillit�nden som kan uppst� �r motor_off,motor_on och motor_running
 * V�rdet p� hastigheten s�tas genom motor.c filen
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

enum state {			//Definierar dem olika tillst�nden vi anv�nder oss av
	MOTOR_OFF,
	MOTOR_ON,
	MOTOR_RUNNING
};


typedef enum state state_t; //Dessa typdefinieras till ett state_t objekt

int main(void){
	
	hmi_init();
	regulator_init();
	motor_init();
	
	char regulator_str [17]; //skapar en temp str�ng med 16 tomma och en f�r cursorn
	
	uint16_t key;			//Skapar key

    state_t current_state= MOTOR_OFF;	//anger den nuvarande tillst�ndet till MOTOR_OFF f�r att b�rja i det som standard
    state_t next_state= MOTOR_OFF;		//anger n�sta tillst�ndet till MOTOR_OFF f�r att b�rja i det som standard
	
	
while (1){	
		key= numkey_read();				//l�ser in kanppen till key
		
	switch (current_state){				//Bytar state beroende p� vad current_state �r
			
		case MOTOR_OFF:
			
			if (key =='2')											//Om key 2 �r nedtryckt
			{
				next_state=MOTOR_ON;								//Is�fall �r n�sta state motor_on
			}
				output_msg("Motor is off!","",0);					//Skriver ut meddelandet p� lcdn
				motor_set_speed(0);									//S�tter hastigheten vid off till 0 eftersom den ej ska snurra d�
				break;
				
		case MOTOR_ON:
		
			if (key=='1')											//Kollar ifall knappen 1 �r nedtryckt
			{
				next_state=MOTOR_OFF;								//Is�danafall s� �r n�sta state motor_off
			}
			else if (regulator()>0)									//Annars om hastigheten �r st�rren �n 0 s� k�rs motor_running
			{
				next_state = MOTOR_RUNNING;							//N�sta state blir motor running
			}
				sprintf(regulator_str, "%u%%", regulator());		//Anv�nder sprintf f�r att skriva ut temp str�ngen+ tecknet och l�ser tempen till temp_str
				motor_set_speed(0);									//S�tter hastigheten vid off till 0 eftersom den ej ska snurra d�
				output_msg("Motor is on!", regulator_str,0);		//Skriver ut meddelandet p� lcdn med v�rdet i regulator
				break;												//avbryter hela case satsen
		case MOTOR_RUNNING:
		
			if (key=='1')											//Om key �r 1 s�...		
			{
				next_state=MOTOR_OFF;								//N�sta state �r d� motor_off
			}
				sprintf(regulator_str, "%u%%", regulator());		//Anv�nder sprintf f�r att skriva ut temp str�ngen+ tecknet och l�ser tempen till temp_str
				output_msg("Motor running:", regulator_str,0);		//Skriver ut meddelandet p� lcdn med v�rdet i regulator
				motor_set_speed(regulator()*2.55);					//S�tter hastigheten till v�rdet i regulator*255 eftersom v�rdet �r 0-100 men vi vill ha 0-255 till speed
				break;
			}
		current_state = next_state;									//N�sta �r samma som nuvarande tillst�nd f�r att loopa igenom tills ny knapp trycks ner 						
	}	

}