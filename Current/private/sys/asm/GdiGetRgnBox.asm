; Hc/NtGdiGetRgnBox
; This file was automatically generated by Highcall's syscall generator.

IFDEF RAX
; 64bit

EXTERNDEF sciGdiGetRgnBox:DWORD

.DATA
.CODE

HcGdiGetRgnBox PROC
	mov r10, rcx
	mov eax, sciGdiGetRgnBox
	syscall
	ret
HcGdiGetRgnBox ENDP

ELSE
; 32bit

EXTERNDEF C sciGdiGetRgnBox:DWORD

.586			  
.MODEL FLAT, C   
.STACK
.DATA
.CODE

ASSUME FS:NOTHING

HcGdiGetRgnBox PROC
	mov eax, sciGdiGetRgnBox
	mov ecx, fs:[0c0h]
	test ecx, ecx
	jne _wow64
	lea edx, [esp + 4]
	INT 02eh
	ret
	_wow64:
	xor ecx, ecx
	lea edx, [esp + 4h]
	call dword ptr fs:[0c0h]
	ret
HcGdiGetRgnBox ENDP

ENDIF

END