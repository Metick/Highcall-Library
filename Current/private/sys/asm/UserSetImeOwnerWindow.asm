; Hc/NtUserSetImeOwnerWindow
; This file was automatically generated by Highcall's syscall generator.

IFDEF RAX
; 64bit

EXTERNDEF sciUserSetImeOwnerWindow:DWORD

.DATA
.CODE

HcUserSetImeOwnerWindow PROC
	mov r10, rcx
	mov eax, sciUserSetImeOwnerWindow
	syscall
	ret
HcUserSetImeOwnerWindow ENDP

ELSE
; 32bit

EXTERNDEF C sciUserSetImeOwnerWindow:DWORD

.586			  
.MODEL FLAT, C   
.STACK
.DATA
.CODE

ASSUME FS:NOTHING

HcUserSetImeOwnerWindow PROC
	mov eax, sciUserSetImeOwnerWindow
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
HcUserSetImeOwnerWindow ENDP

ENDIF

END