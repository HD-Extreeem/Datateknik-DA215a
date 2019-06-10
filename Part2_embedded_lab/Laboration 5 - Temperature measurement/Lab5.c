/*
 * Lab5.c
 *	Denna fil anv�nds f�r att kolla dem olika tillst�nden
 *  Det finns 3 olika tillst�nd som kollas(Celsius, farenheit och Celsius/farenheit)
 *	N�r anv�ndaren knappar in en ny knapp byts tillst�ndet till det andra
 *	Medan anv�ndaren inte knappar in n�gon knapp k�rs en o�ndligt loop och uppdateras v�rdet
 *
 * Created: 2015-12-08 16:56:12
 *  Author: Hadi Deknache
 */ 

#include <stdio.h>
#include <avr/io.h>
#include "hmi/hmi.h"
#include "delay/delay.h"
#include "numkey/numkey.h"
#include "lcd/lcd.h"
#include "common.h"
#include "temp/temp.h"




enum state {							//Definierar dem olika tillst�nden vi anv�nder oss av
	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF
	};
	
	
typedef enum state state_t;				//Dessa typdefinieras till ett state_t objekt


int main(void)
{
	
	hmi_init();
	temp_init();
	char temp_str [17];					//skapar en temp str�ng med 16 tomma och en f�r cursorn
	
	uint16_t key;						//skapar en int av key f�r att lagra det tryckta kanppen
	
	state_t current_state=SHOW_TEMP_C;	//anger den nuvarande tillst�ndet till Celsius f�r att b�rja i det som standard
	state_t next_state= SHOW_TEMP_C;	//anger n�sta tillst�ndet till Celsius f�r att b�rja i det som standard
    

   
while (1){
	key= numkey_read();					//l�ser in kanppen till key
	if ((key=='1')){					//kollar ifall vi tryckt in en 1 p� telefontangentbordet s�...
		next_state = SHOW_TEMP_C;		// N�sta tillst�nd bl�r celsius
		
	}
	
	else if ((key =='2')){				//Annars om den tryckta tangenten �r 2...
		next_state = SHOW_TEMP_F;		// n�sta tillst�nd blir farenheit
		
	}
	
	else if ((key=='3')){				// Annars om den tryckta tangenten �r 3...
		next_state = SHOW_TEMP_CF;		// S� blir n�sta tillst�nd Celsius,farenheit
	}
	
	switch (current_state){				// Switch state f�r att byta varje g�ng vi trycker ner en ny knapp


		case SHOW_TEMP_C:				
				sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);	//Anv�nder sprintf f�r att skriva ut temp str�ngen+ tecknet och l�ser tempen till temp_str
				output_msg("Temperature:", temp_str,0);					//Skriver ut dem p� sk�rmen med outputmessage
				break;
		

		case SHOW_TEMP_F:			
				sprintf(temp_str, "%u%cF", temp_read_fahrenheit(), 0xDF);
				output_msg("Temperature:", temp_str,0);			
				break;
	

		case SHOW_TEMP_CF:
				sprintf(temp_str, "%u%cC, %u%cF", temp_read_celsius(), 0xDF, temp_read_fahrenheit(), 0xDF);
				output_msg("Temperature:", temp_str,0);
				break;

		
		}

	current_state = next_state;		//N�sta �r samma som nuvarande tillst�nd f�r att loopa igenom tills ny knapp trycks ner 

	}

}   

   
   
   
   
   
   
   
   
   
   
   
   
