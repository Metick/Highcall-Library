; Hc/NtGdiGetTextFaceW
; This file was automatically generated by Highcall's syscall generator.

IFDEF RAX
; 64bit

EXTERNDEF sciGdiGetTextFaceW:DWORD

.DATA
.CODE

HcGdiGetTextFaceW PROC
	mov r10, rcx
	mov eax, sciGdiGetTextFaceW
	syscall
	ret
HcGdiGetTextFaceW ENDP

ELSE
; 32bit

EXTERNDEF C sciGdiGetTextFaceW:DWORD

.586			  
.MODEL FLAT, C   
.STACK
.DATA
.CODE

ASSUME FS:NOTHING

HcGdiGetTextFaceW PROC
	mov eax, sciGdiGetTextFaceW
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
HcGdiGetTextFaceW ENDP

ENDIF

END