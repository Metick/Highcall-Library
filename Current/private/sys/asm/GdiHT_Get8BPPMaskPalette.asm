; Hc/NtGdiHT_Get8BPPMaskPalette
; This file was automatically generated by Highcall's syscall generator.

IFDEF RAX
; 64bit

EXTERNDEF sciGdiHT_Get8BPPMaskPalette:DWORD

.DATA
.CODE

HcGdiHT_Get8BPPMaskPalette PROC
	mov r10, rcx
	mov eax, sciGdiHT_Get8BPPMaskPalette
	syscall
	ret
HcGdiHT_Get8BPPMaskPalette ENDP

ELSE
; 32bit

EXTERNDEF C sciGdiHT_Get8BPPMaskPalette:DWORD

.586			  
.MODEL FLAT, C   
.STACK
.DATA
.CODE

ASSUME FS:NOTHING

HcGdiHT_Get8BPPMaskPalette PROC
	mov eax, sciGdiHT_Get8BPPMaskPalette
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
HcGdiHT_Get8BPPMaskPalette ENDP

ENDIF

END