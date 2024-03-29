/*
 * delay.inc
 *
 * Author:	Hadi Deknache
 *
 * Koden anv�nds f�r att utf�ra olika l�nga delayer i lab2
 * Koden best�r av olika l�nga delayer(ms, 1 �s och x-antal �s)
 *
 * Date:	2015-11-23
 */ 

;==============================================================================
; Delay of 1 �s (including RCALL)
;==============================================================================
delay_1_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	NOP			; Delay i 1 �s
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X �s
;	LDI + RCALL = 4 cycles
; H�gsta m�jliga �r 255 �ver g�r det inte och minsta 1 �s
;==============================================================================
delay_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	DEC R24				; Minskar R24 (antal micros �nskat) tills 0
	NOP					; noppar igenom delayen f�r att skapa pausen
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP				
	NOP
	CPI R24, 0			; j�mf�r ifall R24 �r 0, ifall inte b�rjar vi om och minskar tills 0
	
	BRNE delay_micros	; kollar om 0 annars b�rja om 
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
; H�gsta m�jliga �r 255 �ver g�r det inte och minsta 1 �s
;==============================================================================
delay_ms:
	MOV R18, R24
loop_dms:
	LDI R24, 250			; laddar R24 med 250 f�r att loopa igenom en l�ngre delay
	RCALL delay_micros		; skapar delayen och b�rjar sedan om f�r att �ka delayen
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18				; Minskar R24 (antal micros �nskat) tills 0
	NOP					; noppar igenom delayen f�r att skapa pausen
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	CPI R18, 0			; j�mf�r ifall R18 �r 0, ifall inte b�rjar vi om och minskar tills 0
	BRNE loop_dms		; kollar om 0 annars b�rja om 
	RET