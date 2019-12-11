#include <highcall.h>

typedef enum _SYSTEM_FIRMWARE_TABLE_ACTION {
	SystemFirmwareTable_Enumerate,
	SystemFirmwareTable_Get
} SYSTEM_FIRMWARE_TABLE_ACTION;

typedef struct _SYSTEM_FIRMWARE_TABLE_INFORMATION {
	ULONG ProviderSignature;
	SYSTEM_FIRMWARE_TABLE_ACTION Action;
	ULONG TableID;
	ULONG TableBufferLength;
	UCHAR TableBuffer[ANYSIZE_ARRAY];
} SYSTEM_FIRMWARE_TABLE_INFORMATION, * PSYSTEM_FIRMWARE_TABLE_INFORMATION;

static UINT BaseQuerySystemFirmware(IN DWORD FirmwareTableProviderSignature, IN DWORD FirmwareTableID, OUT PVOID pFirmwareTableBuffer, IN DWORD BufferSize, IN SYSTEM_FIRMWARE_TABLE_ACTION Action)
{
	SYSTEM_FIRMWARE_TABLE_INFORMATION* SysFirmwareInfo;
	ULONG Result = 0, ReturnedSize;
	ULONG TotalSize = BufferSize + sizeof(SYSTEM_FIRMWARE_TABLE_INFORMATION);
	NTSTATUS Status;

	SysFirmwareInfo = HcAlloc(TotalSize);
	if (!SysFirmwareInfo)
	{
		HcErrorSetDosError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	SysFirmwareInfo->ProviderSignature = FirmwareTableProviderSignature;
	SysFirmwareInfo->TableID = FirmwareTableID;
	SysFirmwareInfo->Action = Action;
	SysFirmwareInfo->TableBufferLength = BufferSize;

	Status = HcQuerySystemInformation(SystemFirmwareTableInformation, SysFirmwareInfo, TotalSize, &ReturnedSize);

	if (NT_SUCCESS(Status) || Status == STATUS_BUFFER_TOO_SMALL)
		Result = SysFirmwareInfo->TableBufferLength;

	if (NT_SUCCESS(Status) && pFirmwareTableBuffer)
	{
		HcInternalCopy(pFirmwareTableBuffer, SysFirmwareInfo->TableBuffer, SysFirmwareInfo->TableBufferLength);
	}

	HcFree(SysFirmwareInfo);

	HcErrorSetNtStatus(Status);
	return Result;
}

DECL_EXTERN_API(UINT, EnumSystemFirmwareTables, IN DWORD FirmwareTableProviderSignature, OUT PVOID pFirmwareTableBuffer, IN DWORD BufferSize)
{
	return BaseQuerySystemFirmware(FirmwareTableProviderSignature, 0, pFirmwareTableBuffer, BufferSize, SystemFirmwareTable_Enumerate);
}

DECL_EXTERN_API(UINT, GetSystemFirmwareTable, IN DWORD FirmwareTableProviderSignature, IN DWORD FirmwareTableID, OUT PVOID pFirmwareTableBuffer, IN DWORD BufferSize)
{
	return BaseQuerySystemFirmware(FirmwareTableProviderSignature, FirmwareTableID, pFirmwareTableBuffer, BufferSize, SystemFirmwareTable_Get);
}
