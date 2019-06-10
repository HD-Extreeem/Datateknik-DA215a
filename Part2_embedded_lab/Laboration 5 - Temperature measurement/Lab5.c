/*
 * Lab5.c
 *	Denna fil används för att kolla dem olika tillstånden
 *  Det finns 3 olika tillstånd som kollas(Celsius, farenheit och Celsius/farenheit)
 *	När användaren knappar in en ny knapp byts tillståndet till det andra
 *	Medan användaren inte knappar in någon knapp körs en oändligt loop och uppdateras värdet
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




enum state {							//Definierar dem olika tillstånden vi använder oss av
	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF
	};
	
	
typedef enum state state_t;				//Dessa typdefinieras till ett state_t objekt


int main(void)
{
	
	hmi_init();
	temp_init();
	char temp_str [17];					//skapar en temp sträng med 16 tomma och en för cursorn
	
	uint16_t key;						//skapar en int av key för att lagra det tryckta kanppen
	
	state_t current_state=SHOW_TEMP_C;	//anger den nuvarande tillståndet till Celsius för att börja i det som standard
	state_t next_state= SHOW_TEMP_C;	//anger nästa tillståndet till Celsius för att börja i det som standard
    

   
while (1){
	key= numkey_read();					//läser in kanppen till key
	if ((key=='1')){					//kollar ifall vi tryckt in en 1 på telefontangentbordet så...
		next_state = SHOW_TEMP_C;		// Nästa tillstånd blír celsius
		
	}
	
	else if ((key =='2')){				//Annars om den tryckta tangenten är 2...
		next_state = SHOW_TEMP_F;		// nästa tillstånd blir farenheit
		
	}
	
	else if ((key=='3')){				// Annars om den tryckta tangenten är 3...
		next_state = SHOW_TEMP_CF;		// Så blir nästa tillstånd Celsius,farenheit
	}
	
	switch (current_state){				// Switch state för att byta varje gång vi trycker ner en ny knapp


		case SHOW_TEMP_C:				
				sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);	//Använder sprintf för att skriva ut temp strängen+ tecknet och läser tempen till temp_str
				output_msg("Temperature:", temp_str,0);					//Skriver ut dem på skärmen med outputmessage
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

	current_state = next_state;		//Nästa är samma som nuvarande tillstånd för att loopa igenom tills ny knapp trycks ner 

	}

}   

   
   
   
   
   
   
   
   
   
   
   
   
