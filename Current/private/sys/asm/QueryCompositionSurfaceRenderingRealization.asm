; Hc/NtQueryCompositionSurfaceRenderingRealization
; This file was automatically generated by Highcall's syscall generator.

IFDEF RAX
; 64bit

EXTERNDEF sciQueryCompositionSurfaceRenderingRealization:DWORD

.DATA
.CODE

HcQueryCompositionSurfaceRenderingRealization PROC
	mov r10, rcx
	mov eax, sciQueryCompositionSurfaceRenderingRealization
	syscall
	ret
HcQueryCompositionSurfaceRenderingRealization ENDP

ELSE
; 32bit

EXTERNDEF C sciQueryCompositionSurfaceRenderingRealization:DWORD

.586			  
.MODEL FLAT, C   
.STACK
.DATA
.CODE

ASSUME FS:NOTHING

HcQueryCompositionSurfaceRenderingRealization PROC
	mov eax, sciQueryCompositionSurfaceRenderingRealization
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
HcQueryCompositionSurfaceRenderingRealization ENDP

ENDIF

END