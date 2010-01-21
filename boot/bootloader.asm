[BITS 16]
[ORG 0x7C00]

MOV SI, HelloString
CALL PrintString
JMP $


PrintCharacter:
MOV AH, 0x0E	;Tell BIOS that we need to print one charater on screen.
MOV BH, 0x00	;Page no.
MOV BL, 0x2a	;Green-on-black

INT 0x10	;Call video interrupt
RET		;Return to calling procedure



PrintString:	;Procedure to print string on screen
	;Assume that string starting pointer is in register SI

next_character:	;Lable to fetch next character from string
MOV AL, [SI]	;Get a byte from string and store in AL register
INC SI		;Increment SI pointer
OR AL, AL	;Check if value in AL is zero (end of string)
JZ exit_function ;If end then return
CALL PrintCharacter ;Else print the character which is in AL register
JMP next_character	;Fetch next character from string
exit_function:	;End label
RET		;Return from procedure


;Data
HelloString db 'Boot posk', 0	;HelloWorld string ending with 0

TIMES 510 - ($ - $$) db 0	;Fill the rest of sector with 0
DW 0xAA55			;Add boot signature at the end of bootloader
