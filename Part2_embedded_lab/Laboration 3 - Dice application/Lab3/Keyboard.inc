/*
 * Keyboard.inc
 *
 *	Detta programm kollar efter knapptrykning p� telefontangentbor
 *	Ifall tryckt s� omvandlas det till det talet genom convert och visas p� sk�rm	
 *
 *  Created: 2015-11-24 13:51:44
 *   Author: Hadi Deknache
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
map_table: 
	.DB "147*2580369#"			; knapparna representerar telefontangentbordet

;==============================================================================
; Kyeboard main
;==============================================================================
 keyboard:
	CALL scan_keyboard		; kallar p� scan keyboard f�r att avl�sa tryck
	CALL read_keyboard
	RJMP keyboard			; B�rjar om hela processen igen...


 ;----------------------------------------------------------------------------
 ; Scan_keybaord
 ; Parameter IN :	CHOICE: R18 �r valet som lagrats
 ;					RESET : NOLLST�LLS					
 ;----------------------------------------------------------------------------
scan_keyboard:
	LDI CHOICE, RESET		; nollst�ller R18 ingen knapp tryckt)
	RET



 ;----------------------------------------------------------------------------
 ; read keyboard
 ; Parameter IN :	R19 r�knare p� t�rningen
 ;	
 ;					
 ;	Begr�nsningar: Om talet �r under 0 och �ver 6				
 ;----------------------------------------------------------------------------	


read_keyboard:
	RCALL delay_1_micros	; skapar en delay f�r att f� alla funktioner att funger
	SBIC PINE, 6			; k�nner av ifall knapp 1 trycks
	RET						; Knapp nedtryckt, s� hoppar vi in i pressed och v�ntar tills knapp sl�pps
	RJMP read_keyboard		; b�rjar om att kontrollera ifall knapp �r tryckt


load:	
	LDI R19, 6				; laddat talet 6 f�r att r�kna ner och vissa talet p� sk�rmen
Down_pressed:
	RCALL delay_micros			
	SBIS PINE, 6			; Kollar om kanppen fortfarande �r nedtryckt 
	RET						; Ifall den �r s� g�r vi till give number och skriver ut den 
	DEC R19					; minskar R19 �r talet som ska visas p� sk�rm efter�t
	BREQ load				; kollar ifall load blir dess angivna v�rde
	RJMP Down_pressed

 ;----------------------------------------------------------------------------
 ; Write_key
 ; Parameter IN :	R19 r�knare p� t�rningen
 ;	
 ;					
 ;----------------------------------------------------------------------------	

Write_key:
	CHECK R19				; anv�nder macro CHOICE f�r att skriva ut siffran p� sk�rmen
	RCALL Delay_s			; Delay f�r att skriva ut l�ngsammare
	RET

/*Convert:
	LDI ZH, high(map_table<<1)	; Laddar zh med h�ga delen i maptable 
	LDI ZL, low(map_table<<1)	; laddar zl med l�ga delen i maptable f�r 
	ADD ZL, R21					;L�gger till r21 med ZL f�r att f� det t�nkta tecknet
	LDI R21, 0x00				; nollst�ller r21 f�r att anv�ndas i n�sta steg
	ADC ZH, R21					; l�gger till carry med r21 i zh
	LPM R24, Z					; l�gger d�r z pekar i r24 vilket represetera talet
	RET
	*/

	
	

