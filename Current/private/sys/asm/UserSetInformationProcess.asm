; Hc/NtUserSetInformationProcess
; This file was automatically generated by Highcall's syscall generator.

IFDEF RAX
; 64bit

EXTERNDEF sciUserSetInformationProcess:DWORD

.DATA
.CODE

HcUserSetInformationProcess PROC
	mov r10, rcx
	mov eax, sciUserSetInformationProcess
	syscall
	ret
HcUserSetInformationProcess ENDP

ELSE
; 32bit

EXTERNDEF C sciUserSetInformationProcess:DWORD

.586			  
.MODEL FLAT, C   
.STACK
.DATA
.CODE

ASSUME FS:NOTHING

HcUserSetInformationProcess PROC
	mov eax, sciUserSetInformationProcess
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
HcUserSetInformationProcess ENDP

ENDIF

END