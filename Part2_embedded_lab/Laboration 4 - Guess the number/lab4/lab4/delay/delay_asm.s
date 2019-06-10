
 /*
 * delay_asm.s
 *
 * Author:	Hadi Deknache
 *
 * Koden används för att utföra olika länga delayer i lab4
 * Koden består av olika långa delayer(ms, 1 µs och x-antal µs och sekunder)
 *
 * Date:	2015-12-01
 */ 

 .global delay_1_micros
 .global delay_micros
 .global delay_ms
 .global delay_s

;==============================================================================
; Delay of 1 µs (including RCALL)
;==============================================================================
delay_1_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	NOP			; Delay i 1 µs
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X µs
;	LDI + RCALL = 4 cycles
; Högsta möjliga är 255 över gŒr det inte och minsta 1 µs
;==============================================================================
delay_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	DEC R24				; Minskar R24 (antal micros önskat) tills 0
	NOP					; noppar igenom delayen för att skapa pausen
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP	
	NOP			
	NOP
	NOP
	NOP
	NOP
	CPI R24, 0			; jämför ifall R24 är 0, ifall inte börjar vi om och minskar tills 0
	
	BRNE delay_micros	; kollar om 0 annars börja om 
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
; Hšgsta mšjliga Šr 255 šver gŒr det inte och minsta 1 µs
;==============================================================================
delay_ms:
	MOV R18, R24
loop_dms:
	LDI R24, 250			; laddar R24 med 250 för att loopa igenom en längre delay
	RCALL delay_micros		; skapar delayen och börjar sedan om för att öka delayen
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18				; Minskar R24 (antal micros önskat) tills 0
	CPI R18, 0			; jämför ifall R18 är 0, ifall inte börjar vi om och minskar tills 0
	BRNE loop_dms		; kollar om 0 annars börja om 
	RET



delay_s:

	LDI R24, 250			; Egen skapad delay rutin för längre delayer
	RCALL delay_ms			; Använder delay_ms för att skapa den långa delayen
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	RET

