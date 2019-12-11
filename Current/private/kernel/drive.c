#include <highcall.h>

typedef enum _STORAGE_PROPERTY_ID {
	StorageDeviceProperty,
	StorageAdapterProperty,
	StorageDeviceIdProperty,
	StorageDeviceUniqueIdProperty,
	StorageDeviceWriteCacheProperty,
	StorageMiniportProperty,
	StorageAccessAlignmentProperty,
	StorageDeviceSeekPenaltyProperty,
	StorageDeviceTrimProperty,
	StorageDeviceWriteAggregationProperty,
	StorageDeviceDeviceTelemetryProperty,
	StorageDeviceLBProvisioningProperty,
	StorageDevicePowerProperty,
	StorageDeviceCopyOffloadProperty,
	StorageDeviceResiliencyProperty,
	StorageDeviceMediumProductType,
	StorageAdapterRpmbProperty,
	StorageAdapterCryptoProperty,
	StorageDeviceIoCapabilityProperty,
	StorageAdapterProtocolSpecificProperty,
	StorageDeviceProtocolSpecificProperty,
	StorageAdapterTemperatureProperty,
	StorageDeviceTemperatureProperty,
	StorageAdapterPhysicalTopologyProperty,
	StorageDevicePhysicalTopologyProperty,
	StorageDeviceAttributesProperty,
	StorageDeviceManagementStatus,
	StorageAdapterSerialNumberProperty,
	StorageDeviceLocationProperty,
	StorageDeviceNumaProperty,
	StorageDeviceZonedDeviceProperty,
	StorageDeviceUnsafeShutdownCount,
	StorageDeviceEnduranceProperty
} STORAGE_PROPERTY_ID, * PSTORAGE_PROPERTY_ID;

typedef enum _STORAGE_QUERY_TYPE {
	PropertyStandardQuery,
	PropertyExistsQuery,
	PropertyMaskQuery,
	PropertyQueryMaxDefined
} STORAGE_QUERY_TYPE, * PSTORAGE_QUERY_TYPE;

typedef struct _STORAGE_PROPERTY_QUERY {
	STORAGE_PROPERTY_ID PropertyId;
	STORAGE_QUERY_TYPE  QueryType;
	BYTE                AdditionalParameters[1];
} STORAGE_PROPERTY_QUERY, * PSTORAGE_PROPERTY_QUERY;

// Used in conjunction with the IOCTL_STORAGE_QUERY_PROPERTY control code to retrieve the properties of a storage device or adapter.
typedef struct _STORAGE_DESCRIPTOR_HEADER {
	DWORD Version;
	DWORD Size;
} STORAGE_DESCRIPTOR_HEADER, * PSTORAGE_DESCRIPTOR_HEADER;

typedef enum _STORAGE_BUS_TYPE {
	BusTypeUnknown,
	BusTypeScsi,
	BusTypeAtapi,
	BusTypeAta,
	BusType1394,
	BusTypeSsa,
	BusTypeFibre,
	BusTypeUsb,
	BusTypeRAID,
	BusTypeiScsi,
	BusTypeSas,
	BusTypeSata,
	BusTypeSd,
	BusTypeMmc,
	BusTypeVirtual,
	BusTypeFileBackedVirtual,
	BusTypeSpaces,
	BusTypeNvme,
	BusTypeSCM,
	BusTypeUfs,
	BusTypeMax,
	BusTypeMaxReserved
} STORAGE_BUS_TYPE, * PSTORAGE_BUS_TYPE;

typedef struct _STORAGE_DEVICE_DESCRIPTOR {
	DWORD            Version;
	DWORD            Size;
	BYTE             DeviceType;
	BYTE             DeviceTypeModifier;
	BOOLEAN          RemovableMedia;
	BOOLEAN          CommandQueueing;
	DWORD            VendorIdOffset;
	DWORD            ProductIdOffset;
	DWORD            ProductRevisionOffset;
	DWORD            SerialNumberOffset;
	STORAGE_BUS_TYPE BusType;
	DWORD            RawPropertiesLength;
	BYTE             RawDeviceProperties[1];
} STORAGE_DEVICE_DESCRIPTOR, * PSTORAGE_DEVICE_DESCRIPTOR;

#define IOCTL_STORAGE_BASE FILE_DEVICE_MASS_STORAGE
#define IOCTL_STORAGE_QUERY_PROPERTY                CTL_CODE(IOCTL_STORAGE_BASE, 0x0500, METHOD_BUFFERED, FILE_ANY_ACCESS)

DECL_EXTERN_API(DWORD, DriveGetSerialNumber, UINT DriveNumber, LPSTR SerialNumber)
{
#pragma region Obfuscation
	// Obfuscated to make it harder to reverse engineer
	// https://zerosum0x0.blogspot.com/2017/08/obfuscatedencrypted-cc-online-string.html

	// \\.\PhysicalDrive%u
	unsigned char Format[] =
	{
		0xaa, 0xa5, 0xf9, 0xa3, 0xd9, 0x85, 0x97, 0x96,
		0xb5, 0xb4, 0xa3, 0xbb, 0xd5, 0xb3, 0xcf, 0x81,
		0xd1, 0x13, 0x9f, 0x58
	};

	for (unsigned int m = 0; m < sizeof(Format); ++m)
	{
		unsigned char c = Format[m];
		c ^= m;
		c = ~c;
		c += 0x73;
		c = ~c;
		c -= m;
		c = (c >> 0x3) | (c << 0x5);
		c += 0xd7;
		c ^= 0xec;
		c = -c;
		c = (c >> 0x5) | (c << 0x3);
		c = ~c;
		c = -c;
		c -= m;
		c ^= 0x77;
		c -= 0xad;
		Format[m] = c;
	}
#pragma endregion

	CHAR DriveName[32];
	wsprintfA(DriveName, Format, DriveNumber);

	HANDLE DeviceHandle = HcFileOpenA(DriveName, OPEN_EXISTING, 0);
	if (DeviceHandle == INVALID_HANDLE_VALUE)
	{
		return HcErrorGetDosError();
	}

	STORAGE_PROPERTY_QUERY StoragePropertyQuery;
	HcInternalZero(&StoragePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
	StoragePropertyQuery.PropertyId = StorageDeviceProperty;
	StoragePropertyQuery.QueryType = PropertyStandardQuery;

	STORAGE_DESCRIPTOR_HEADER StorageDescriptorHeader = { 0 };

	DWORD BytesReturned = 0;
	if (!HcDeviceIoControl(DeviceHandle, IOCTL_STORAGE_QUERY_PROPERTY,
		&StoragePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
		&StorageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
		&BytesReturned, NULL))
	{
		HcClose(DeviceHandle);
		return HcErrorGetDosError();
	}

	CONST DWORD OutBufferSize = StorageDescriptorHeader.Size;
	BYTE* OutBuffer = (BYTE*)HcAlloc(OutBufferSize);
	HcInternalZero(OutBuffer, OutBufferSize);

	if (!HcDeviceIoControl(DeviceHandle, IOCTL_STORAGE_QUERY_PROPERTY,
		&StoragePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
		OutBuffer, OutBufferSize,
		&BytesReturned, NULL))
	{
		HcFree(OutBuffer);
		HcClose(DeviceHandle);
		return HcErrorGetDosError();
	}

	STORAGE_DEVICE_DESCRIPTOR* DeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)OutBuffer;
	CONST DWORD SerialNumberOffset = DeviceDescriptor->SerialNumberOffset;
	if (SerialNumberOffset != 0)
	{
		HcStringCopyExA(SerialNumber, OutBuffer + SerialNumberOffset);
	}

	HcFree(OutBuffer);
	HcClose(DeviceHandle);

	return ERROR_SUCCESS;
}