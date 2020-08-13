#include "highcall.h"
#include <intrin.h>

static CONST ULONG __cpuid_value_list[] = { 0, 7, 4, 0x80000008, 0x80000007, 0x80000005, 0x80000006, 0x80000001, 0x80000000 };

DECL_EXTERN_API(LPSTR, UniqueHardwareId)
{
	LPSTR lpCpuID = HcStringAllocA(256);
	ULONG dIndex = 0;

	for (ULONG i = 0; i < __crt_countof(__cpuid_value_list); i++)
	{
		int cpuinfo[4] = { 0, 0, 0, 0 };
		__cpuid(cpuinfo, __cpuid_value_list[i]);

		LPBYTE blockInfo = (LPBYTE) cpuinfo;

		for (DWORD block = 0; block < 16; block++)
		{
			HcStringUInt32ToHexStringA((ULONG) blockInfo[block], &lpCpuID[dIndex]);
			dIndex += 1;
		}
	}

	CHAR serialNumber[256];
	HcDriveGetSerialNumber(0, serialNumber);

	CHAR saltedSerialNumber[512];
	HcStringAppendExA(saltedSerialNumber, serialNumber);
	HcStringAppendExA(saltedSerialNumber, lpCpuID);
	
	// SHA256(HDDSERIAL+CPUID)
	LPSTR lpDataHashed = HcHashSha256A(saltedSerialNumber, HcStringLenA(saltedSerialNumber));

	HcFree(lpCpuID);
	return lpDataHashed;
}