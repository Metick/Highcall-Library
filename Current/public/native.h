#ifndef HC_NATIVE_H
#define HC_NATIVE_H

#include "wintype.h"
#include "status.h"

#include <winuser.h>

// different architecture processes
#define PTR_64(Type) ULONGLONG
#define PTR_32(Type) ULONG

#define WOW64_CONVERT(Type) (ULONGLONG)

#define RTL_CONSTANT_STRING(s) { sizeof(s) - sizeof((s)[0]), sizeof(s), s }

#define THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER	0x00000004
#define THREAD_CREATE_FLAGS_CREATE_SUSPENDED 0x00000001
#define THREAD_CREATE_FLAGS_SKIP_THREAD_ATTACH 0x00000002
#define THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER 0x00000004
#define THREAD_CREATE_FLAGS_HAS_SECURITY_DESCRIPTOR 0x00000010
#define THREAD_CREATE_FLAGS_ACCESS_CHECK_IN_TARGET 0x00000020
#define THREAD_CREATE_FLAGS_INITIAL_THREAD 0x00000080

#define OBJ_INHERIT             0x00000002L
#define OBJ_PERMANENT           0x00000010L
#define OBJ_EXCLUSIVE           0x00000020L
#define OBJ_CASE_INSENSITIVE    0x00000040L
#define OBJ_OPENIF              0x00000080L
#define OBJ_OPENLINK            0x00000100L
#define OBJ_KERNEL_HANDLE       0x00000200L
#define OBJ_FORCE_ACCESS_CHECK  0x00000400L
#define OBJ_VALID_ATTRIBUTES    0x000007F2L

//
// MessageId: WAIT_TIMEOUT
//
// MessageText:
//
// The wait operation timed out.
//
#define WAIT_TIMEOUT        258L
#define WAIT_FAILED			((DWORD)0xFFFFFFFF)
#define WAIT_OBJECT_0       ((STATUS_WAIT_0 ) + 0 )

#define DEBUG_READ_EVENT        (0x0001)
#define DEBUG_PROCESS_ASSIGN    (0x0002)
#define DEBUG_SET_INFORMATION   (0x0004)
#define DEBUG_QUERY_INFORMATION (0x0008)
#define DEBUG_ALL_ACCESS		(STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | DEBUG_READ_EVENT | DEBUG_PROCESS_ASSIGN |\
								DEBUG_SET_INFORMATION | DEBUG_QUERY_INFORMATION)

#define RTL_ACTIVATE_ACTIVATION_CONTEXT_EX_FLAG_RELEASE_ON_STACK_DEALLOCATION   0x01
#define RTL_QUERY_ACTIVATION_CONTEXT_FLAG_USE_ACTIVE_ACTIVATION_CONTEXT         0x01
#define RTL_QUERY_ACTIVATION_CONTEXT_FLAG_IS_HMODULE                            0x02
#define RTL_QUERY_ACTIVATION_CONTEXT_FLAG_IS_ADDRESS                            0x04
#define RTL_QUERY_ACTIVATION_CONTEXT_FLAG_NO_ADDREF                             0x80000000

#define DEBUG_KILL_ON_CLOSE  (0x1)

#define ALIGN_DOWN(length, type) \
	((ULONG)(length) & ~(sizeof(type) - 1))

#define ALIGN_UP(length, type) \
	(ALIGN_DOWN(((ULONG)(length) + sizeof(type) - 1), type))

#define MAX_MODULES   0x2710

#define WH_MIN	(-1)
#define WH_MAX	14
#define WH_MINHOOK	WH_MIN
#define WH_MAXHOOK	WH_MAX
#define NB_HOOKS (WH_MAXHOOK - WH_MINHOOK + 1)

#define NtCurrentProcess() ((HANDLE)(LONG_PTR)-1)
#define NtCurrentThread() ((HANDLE)(LONG_PTR)-2)

typedef struct _CLIENTTHREADINFO
{
	DWORD CTI_flags;
	WORD fsChangeBits;
	WORD fsWakeBits;
	WORD fsWakeBitsJournal;
	WORD fsWakeMask;
	ULONG tickLastMsgChecked;
	DWORD dwcPumpHook;
} CLIENTTHREADINFO, *PCLIENTTHREADINFO;

typedef struct _CALLBACKWND {
	HWND hWnd;
	struct _WND *pWnd;
	PVOID pActCtx;
} CALLBACKWND, *PCALLBACKWND;

typedef struct _CLIENTINFO
{
	ULONG_PTR CI_flags;
	ULONG_PTR cSpins;
	DWORD dwExpWinVer;
	DWORD dwCompatFlags;
	DWORD dwCompatFlags2;
	DWORD dwTIFlags; /* ThreadInfo TIF_Xxx flags for User space. */
	VOID* pDeskInfo;
	ULONG_PTR ulClientDelta;
	VOID* phkCurrent;
	ULONG fsHooks;
	PCALLBACKWND CallbackWnd;
	DWORD dwHookCurrent;
	INT cInDDEMLCallback;
	PCLIENTTHREADINFO pClientThreadInfo;
	ULONG_PTR dwHookData;
	DWORD dwKeyCache;
	BYTE afKeyState[8];
	DWORD dwAsyncKeyCache;
	BYTE afAsyncKeyState[8];
	BYTE afAsyncKeyStateRecentDow[8];
	HKL hKL;
	USHORT CodePage;
	UCHAR achDbcsCF[2];
	MSG msgDbcsCB;
	LPDWORD lpdwRegisteredClasses;
	ULONG Win32ClientInfo3[26];
	/* It's just a pointer reference not to be used w the structure in user space. */
	struct _PROCESSINFO *ppi;
} CLIENTINFO, *PCLIENTINFO;

#define GetWin32ClientInfo() ((PCLIENTINFO)(NtCurrentTeb()->Win32ClientInfo))

#define QUERY_WINDOW_UNIQUE_PROCESS_ID 0x00
#define QUERY_WINDOW_UNIQUE_THREAD_ID  0x01
#define QUERY_WINDOW_ACTIVE            0x02
#define QUERY_WINDOW_FOCUS             0x03
#define QUERY_WINDOW_ISHUNG            0x04
#define QUERY_WINDOW_REAL_ID           0x05
#define QUERY_WINDOW_FOREGROUND        0x06

#define ASSERT(x) ((void)sizeof(x))

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );          \
    (p)->RootDirectory = r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = n;                                \
    (p)->SecurityDescriptor = s;                        \
    (p)->SecurityQualityOfService = NULL;               \
    }

#define InitializeObjectAttributesWow64( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES_WOW64 );          \
    (p)->RootDirectory = WOW64_CONVERT(HANDLE) r;                             \
    (p)->Attributes = a;                                \
    (p)->ObjectName = WOW64_CONVERT(PUNICODE_STRING64) n;                                \
    (p)->SecurityDescriptor = WOW64_CONVERT(HANDLE) s;                        \
    (p)->SecurityQualityOfService = 0;               \
    }

#define RTL_USER_PROCESS_PARAMETERS_NORMALIZED              0x01
#define RTL_USER_PROCESS_PARAMETERS_PROFILE_USER            0x02
#define RTL_USER_PROCESS_PARAMETERS_PROFILE_KERNEL          0x04
#define RTL_USER_PROCESS_PARAMETERS_PROFILE_SERVER          0x08
#define RTL_USER_PROCESS_PARAMETERS_UNKNOWN                 0x10
#define RTL_USER_PROCESS_PARAMETERS_RESERVE_1MB             0x20
#define RTL_USER_PROCESS_PARAMETERS_RESERVE_16MB            0x40
#define RTL_USER_PROCESS_PARAMETERS_CASE_SENSITIVE          0x80
#define RTL_USER_PROCESS_PARAMETERS_DISABLE_HEAP_CHECKS     0x100
#define RTL_USER_PROCESS_PARAMETERS_PROCESS_OR_1            0x200
#define RTL_USER_PROCESS_PARAMETERS_PROCESS_OR_2            0x400
#define RTL_USER_PROCESS_PARAMETERS_PRIVATE_DLL_PATH        0x1000
#define RTL_USER_PROCESS_PARAMETERS_LOCAL_DLL_PATH          0x2000
#define RTL_USER_PROCESS_PARAMETERS_IMAGE_KEY_MISSING       0x4000
#define RTL_USER_PROCESS_PARAMETERS_NX                      0x20000

#define RTL_MAX_DRIVE_LETTERS 32
#define RTL_DRIVE_LETTER_VALID (USHORT)0x0001
#define GDI_BATCH_BUFFER_SIZE 310

#define GDI_HANDLE_BUFFER_SIZE32 34
#define GDI_HANDLE_BUFFER_SIZE64 60

#ifndef _WIN64
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE32
#else
#define GDI_HANDLE_BUFFER_SIZE GDI_HANDLE_BUFFER_SIZE64
#endif

//
// Object Manager Directory Specific Access Rights.
//

#define DIRECTORY_QUERY                 (0x0001)
#define DIRECTORY_TRAVERSE              (0x0002)
#define DIRECTORY_CREATE_OBJECT         (0x0004)
#define DIRECTORY_CREATE_SUBDIRECTORY   (0x0008)

#define DIRECTORY_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0xF)

typedef enum _KTHREAD_STATE
{
	Initialized,
	Ready,
	Running,
	Standby,
	Terminated,
	Waiting,
	Transition,
	DeferredReady,
	GateWait
} KTHREAD_STATE;

typedef enum _KWAIT_REASON
{
	Executive,
	FreePage,
	PageIn,
	PoolAllocation,
	DelayExecution,
	Suspended,
	UserRequest,
	WrExecutive,
	WrFreePage,
	WrPageIn,
	WrPoolAllocation,
	WrDelayExecution,
	WrSuspended,
	WrUserRequest,
	WrEventPair,
	WrQueue,
	WrLpcReceive,
	WrLpcReply,
	WrVirtualMemory,
	WrPageOut,
	WrRendezvous,
	Spare2,
	Spare3,
	Spare4,
	Spare5,
	Spare6,
	WrKernel,
	WrResource,
	WrPushLock,
	WrMutex,
	WrQuantumEnd,
	WrDispatchInt,
	WrPreempted,
	WrYieldExecution,
	WrFastMutex,
	WrGuardedMutex,
	WrRundown,
	MaximumWaitReason
} KWAIT_REASON;

typedef enum _SECTION_INHERIT {
	ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT;

typedef struct _SYSTEM_SESSION_PROCESS_INFORMATION
{
	ULONG SessionId;
	ULONG SizeOfBuf;
	PBYTE Buffer;
} SYSTEM_SESSION_PROCESS_INFORMATION, *PSYSTEM_SESSION_PROCESS_INFORMATION;

typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION
{
	BOOLEAN KernelDebuggerEnabled;
	BOOLEAN KernelDebuggerNotPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

typedef struct _LDT_INFORMATION
{
	ULONG Start;
	ULONG Length;
	LDT_ENTRY LdtEntries[1];
} PROCESS_LDT_INFORMATION, *PPROCESS_LDT_INFORMATION;


typedef ULONG GDI_HANDLE_BUFFER[GDI_HANDLE_BUFFER_SIZE];

typedef ULONG GDI_HANDLE_BUFFER32[GDI_HANDLE_BUFFER_SIZE32];
typedef ULONG GDI_HANDLE_BUFFER64[GDI_HANDLE_BUFFER_SIZE64];

typedef LONG KPRIORITY;

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef const UNICODE_STRING* PCUNICODE_STRING;

typedef struct _STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PCHAR  Buffer;
} ANSI_STRING, *PANSI_STRING;

typedef struct _CLIENT_ID64 {
	ULONGLONG UniqueProcess;
	ULONGLONG UniqueThread;
} CLIENT_ID64, *PCLIENT_ID64;

typedef struct _STRING64 {
	USHORT Length;
	USHORT MaximumLength;
	ULONGLONG Buffer;
} STRING64, *PSTRING64;

typedef STRING64 UNICODE_STRING64, *PUNICODE_STRING64;
typedef STRING64 ANSI_STRING64, *PANSI_STRING64;

#define ConvertStringWow64(str64, str) (str64)->Length = (str)->Length; \
(str64)->MaximumLength = (str)->MaximumLength; \
(str64)->Buffer = WOW64_CONVERT(PWSTR) (str)->Buffer;

#define ConvertUnicodeStringFromWow64(str64, str) (str)->Length = (str64)->Length; \
(str)->MaximumLength = (str64)->MaximumLength; \
(str)->Buffer = POINTER32_HARDCODED(LPWSTR) (str64)->Buffer;

#define ConvertAnsiStringFromWow64(str64, str) (str)->Length = (str64)->Length; \
(str)->MaximumLength = (str64)->MaximumLength; \
(str)->Buffer = POINTER32_HARDCODED(LPSTR) (str64)->Buffer;

typedef struct _CLIENT_ID
{
	HANDLE UniqueProcess;
	HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _CLIENT_ID_WOW64 {
	PTR_64(HANDLE) UniqueProcess;
	PTR_64(HANDLE) UniqueThread;
} CLIENT_ID_WOW64, *PCLIENT_ID_WOW64;

typedef struct _SYSTEM_THREAD_INFORMATION
{
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PBYTE StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG ThreadState;
	ULONG WaitReason;
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREAD_INFORMATION;

 typedef struct _SYSTEM_PROCESS_INFORMATION
 {
     ULONG NextEntryOffset;
     ULONG NumberOfThreads;
     LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
     ULONG HardFaultCount; // since WIN7
     ULONG NumberOfThreadsHighWatermark; // since WIN7
     ULONGLONG CycleTime; // since WIN7
     LARGE_INTEGER CreateTime;
     LARGE_INTEGER UserTime;
     LARGE_INTEGER KernelTime;
     UNICODE_STRING ImageName;
     KPRIORITY BasePriority;
     HANDLE UniqueProcessId;
     HANDLE InheritedFromUniqueProcessId;
     ULONG HandleCount;
     ULONG SessionId;
     ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
     SIZE_T PeakVirtualSize;
     SIZE_T VirtualSize;
     ULONG PageFaultCount;
     SIZE_T PeakWorkingSetSize;
     SIZE_T WorkingSetSize;
     SIZE_T QuotaPeakPagedPoolUsage;
     SIZE_T QuotaPagedPoolUsage;
     SIZE_T QuotaPeakNonPagedPoolUsage;
     SIZE_T QuotaNonPagedPoolUsage;
     SIZE_T PagefileUsage;
     SIZE_T PeakPagefileUsage;
     SIZE_T PrivatePageCount;
     LARGE_INTEGER ReadOperationCount;
     LARGE_INTEGER WriteOperationCount;
     LARGE_INTEGER OtherOperationCount;
     LARGE_INTEGER ReadTransferCount;
     LARGE_INTEGER WriteTransferCount;
     LARGE_INTEGER OtherTransferCount;
     SYSTEM_THREAD_INFORMATION Threads[1];
 } SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

 typedef struct _SYSTEM_THREAD_INFORMATION_WOW64 {
	 LARGE_INTEGER KernelTime;
	 LARGE_INTEGER UserTime;
	 LARGE_INTEGER CreateTime;
	 ULONG WaitTime;
	 PTR_64(PBYTE) StartAddress;
	 CLIENT_ID_WOW64 ClientId;
	 KPRIORITY Priority;
	 LONG BasePriority;
	 ULONG ContextSwitches;
	 ULONG ThreadState;
	 KWAIT_REASON WaitReason;
 } SYSTEM_THREAD_INFORMATION_WOW64, *PSYSTEM_THREAD_INFORMATION_WOW64;

 typedef struct _SYSTEM_PROCESS_INFORMATION_WOW64 {
     ULONG NextEntryOffset;
     ULONG NumberOfThreads;
     LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
     ULONG HardFaultCount; // since WIN7
     ULONG NumberOfThreadsHighWatermark; // since WIN7
     ULONGLONG CycleTime; // since WIN7
     LARGE_INTEGER CreateTime;
     LARGE_INTEGER UserTime;
     LARGE_INTEGER KernelTime;
     UNICODE_STRING64 ImageName;
	 KPRIORITY BasePriority;
	 PTR_64(HANDLE) UniqueProcessId;
	 PTR_64(HANDLE) InheritedFromUniqueProcessId;
	 ULONG HandleCount;
	 ULONG SessionId;
	 PTR_64(ULONG_PTR) UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
	 PTR_64(SIZE_T) PeakVirtualSize;
	 PTR_64(SIZE_T) VirtualSize;
	 ULONG PageFaultCount;
	 PTR_64(SIZE_T) PeakWorkingSetSize;
	 PTR_64(SIZE_T) WorkingSetSize;
	 PTR_64(SIZE_T) QuotaPeakPagedPoolUsage;
	 PTR_64(SIZE_T) QuotaPagedPoolUsage;
	 PTR_64(SIZE_T) QuotaPeakNonPagedPoolUsage;
	 PTR_64(SIZE_T) QuotaNonPagedPoolUsage;
	 PTR_64(SIZE_T) PagefileUsage;
	 PTR_64(SIZE_T) PeakPagefileUsage;
	 PTR_64(SIZE_T) PrivatePageCount;
	 LARGE_INTEGER ReadOperationCount;
	 LARGE_INTEGER WriteOperationCount;
	 LARGE_INTEGER OtherOperationCount;
	 LARGE_INTEGER ReadTransferCount;
	 LARGE_INTEGER WriteTransferCount;
	 LARGE_INTEGER OtherTransferCount;
	 SYSTEM_THREAD_INFORMATION_WOW64 Threads[1];
 } SYSTEM_PROCESS_INFORMATION_WOW64, *PSYSTEM_PROCESS_INFORMATION_WOW64;

#define ConvertProcessBasicInformationFromWow64(o64, o) {\
(o)->ExitStatus = (o64)->ExitStatus;\
(o)->PebBaseAddress = POINTER32_HARDCODED(PPEB) ((o64)->PebBaseAddress + 0x1000);\
(o)->AffinityMask = POINTER32_HARDCODED(ULONG_PTR) (o64)->AffinityMask;\
(o)->BasePriority = (o64)->BasePriority;\
(o)->UniqueProcessId = POINTER32_HARDCODED(HANDLE) (o64)->UniqueProcessId;\
(o)->InheritedFromUniqueProcessId = POINTER32_HARDCODED(HANDLE) (o64)->InheritedFromUniqueProcessId;\
}\

typedef struct _PEB_LDR_DATA {
	ULONG Length;
	BOOLEAN Initialized;
	PBYTE SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _CURDIR
{
	UNICODE_STRING DosPath;
	HANDLE Handle;
} CURDIR, *PCURDIR;

typedef struct _RTLP_CURDIR_REF
{
	LONG RefCount;
	HANDLE Handle;
} RTLP_CURDIR_REF, *PRTLP_CURDIR_REF;

typedef struct _RTL_DRIVE_LETTER_CURDIR
{
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	UNICODE_STRING DosPath;
} RTL_DRIVE_LETTER_CURDIR, *PRTL_DRIVE_LETTER_CURDIR;

typedef struct _RTL_USER_PROCESS_PARAMETERS
{
	ULONG MaximumLength;
	ULONG Length;
	ULONG Flags;
	ULONG DebugFlags;
	HANDLE ConsoleHandle;
	ULONG ConsoleFlags;
	HANDLE StandardInput;
	HANDLE StandardOutput;
	HANDLE StandardError;
	CURDIR CurrentDirectory;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	PWSTR Environment;
	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;
	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopInfo;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
	RTL_DRIVE_LETTER_CURDIR CurrentDirectories[RTL_MAX_DRIVE_LETTERS];
#if (NTDDI_VERSION >= NTDDI_LONGHORN)
	SIZE_T EnvironmentSize;
#endif
#if (NTDDI_VERSION >= NTDDI_WIN7)
	SIZE_T EnvironmentVersion;
#endif
} RTL_USER_PROCESS_PARAMETERS, *PRTL_USER_PROCESS_PARAMETERS;

typedef struct _SECTION_IMAGE_INFORMATION
{
	PBYTE TransferAddress; //Entrypoint
	ULONG ZeroBits;
	SIZE_T MaximumStackSize;
	SIZE_T CommittedStackSize;
	ULONG SubSystemType;
	union {
		struct {
			USHORT SubSystemMinorVersion;
			USHORT SubSystemMajorVersion;
		};
		ULONG SubSystemVersion;
	};
	ULONG GpValue;
	USHORT ImageCharacteristics;
	USHORT DllCharacteristics;
	USHORT Machine;
	BOOLEAN ImageContainsCode;
	BOOLEAN Spare1;
	ULONG LoaderFlags;
	ULONG ImageFileSize;
	ULONG Reserved[1];
} SECTION_IMAGE_INFORMATION, *PSECTION_IMAGE_INFORMATION;

typedef struct _RTL_PERTHREAD_CURDIR
{
	PRTL_DRIVE_LETTER_CURDIR CurrentDirectories;
	PUNICODE_STRING ImageName;
	PVOID Environment;
} RTL_PERTHREAD_CURDIR, *PRTL_PERTHREAD_CURDIR;

typedef struct _RTL_USER_PROCESS_INFORMATION
{
	ULONG Size;
	HANDLE ProcessHandle;
	HANDLE ThreadHandle;
	CLIENT_ID ClientId;
	SECTION_IMAGE_INFORMATION ImageInformation;
} RTL_USER_PROCESS_INFORMATION, *PRTL_USER_PROCESS_INFORMATION;

typedef struct _PEB
{
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	union
	{
		BOOLEAN BitField;
		struct
		{
			BOOLEAN ImageUsesLargePages : 1;
			BOOLEAN IsProtectedProcess : 1;
			BOOLEAN IsImageDynamicallyRelocated : 1;
			BOOLEAN SkipPatchingUser32Forwarders : 1;
			BOOLEAN IsPackagedProcess : 1;
			BOOLEAN IsAppContainer : 1;
			BOOLEAN IsProtectedProcessLight : 1;
			BOOLEAN SpareBits : 1;
		};
	};
	HANDLE Mutant;

	HMODULE ImageBaseAddress;
	PPEB_LDR_DATA LoaderData;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PBYTE SubSystemData;
	PBYTE ProcessHeap;
	PRTL_CRITICAL_SECTION FastPebLock;
	PBYTE AtlThunkSListPtr;
	PBYTE IFEOKey;
	union
	{
		ULONG CrossProcessFlags;
		struct
		{
			ULONG ProcessInJob : 1;
			ULONG ProcessInitializing : 1;
			ULONG ProcessUsingVEH : 1;
			ULONG ProcessUsingVCH : 1;
			ULONG ProcessUsingFTH : 1;
			ULONG ReservedBits0 : 27;
		};
	};
	union
	{
		PBYTE KernelCallbackTable;
		PBYTE UserSharedInfoPtr;
	};
	ULONG SystemReserved[1];
	ULONG AtlThunkSListPtr32;
	PBYTE ApiSetMap;
	ULONG TlsExpansionCounter;
	PBYTE TlsBitmap;
	ULONG TlsBitmapBits[2];
	PBYTE ReadOnlySharedMemoryBase;
	PBYTE HotpatchInformation;
	PBYTE *ReadOnlyStaticServerData;
	PBYTE AnsiCodePageData;
	PBYTE OemCodePageData;
	PBYTE UnicodeCaseTableData;

	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;

	LARGE_INTEGER CriticalSectionTimeout;
	SIZE_T HeapSegmentReserve;
	SIZE_T HeapSegmentCommit;
	SIZE_T HeapDeCommitTotalFreeThreshold;
	SIZE_T HeapDeCommitFreeBlockThreshold;

	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PBYTE *ProcessHeaps;

	PBYTE GdiSharedHandleTable;
	PBYTE ProcessStarterHelper;
	ULONG GdiDCAttributeList;

	PRTL_CRITICAL_SECTION LoaderLock;

	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	USHORT OSBuildNumber;
	USHORT OSCSDVersion;
	ULONG OSPlatformId;
	ULONG ImageSubsystem;
	ULONG ImageSubsystemMajorVersion;
	ULONG ImageSubsystemMinorVersion;
	ULONG_PTR ImageProcessAffinityMask;
	GDI_HANDLE_BUFFER GdiHandleBuffer;
	PBYTE PostProcessInitRoutine;

	PBYTE TlsExpansionBitmap;
	ULONG TlsExpansionBitmapBits[32];

	ULONG SessionId;

	ULARGE_INTEGER AppCompatFlags;
	ULARGE_INTEGER AppCompatFlagsUser;
	PBYTE pShimData;
	PBYTE AppCompatInfo;

	UNICODE_STRING CSDVersion;

	PBYTE ActivationContextData;
	PBYTE ProcessAssemblyStorageMap;
	PBYTE SystemDefaultActivationContextData;
	PBYTE SystemAssemblyStorageMap;

	SIZE_T MinimumStackCommit;

	PBYTE *FlsCallback;
	LIST_ENTRY FlsListHead;
	PBYTE FlsBitmap;
	ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
	ULONG FlsHighIndex;

	PBYTE WerRegistrationData;
	PBYTE WerShipAssertPtr;
	PBYTE pContextData;
	PBYTE pImageHeaderHash;
	union
	{
		ULONG TracingFlags;
		struct
		{
			ULONG HeapTracingEnabled : 1;
			ULONG CritSecTracingEnabled : 1;
			ULONG LibLoaderTracingEnabled : 1;
			ULONG SpareTracingBits : 29;
		};
	};
	ULONGLONG CsrServerReadOnlySharedMemoryBase;
} PEB, *PPEB;

typedef struct _GDI_TEB_BATCH
{
	ULONG Offset;
	ULONG_PTR HDC;
	ULONG Buffer[310];
} GDI_TEB_BATCH, *PGDI_TEB_BATCH;

typedef struct _TEB_ACTIVE_FRAME_CONTEXT
{
	ULONG Flags;
	PSTR FrameName;
} TEB_ACTIVE_FRAME_CONTEXT, *PTEB_ACTIVE_FRAME_CONTEXT;

typedef struct _TEB_ACTIVE_FRAME
{
	ULONG Flags;
	struct _TEB_ACTIVE_FRAME *Previous;
	PTEB_ACTIVE_FRAME_CONTEXT Context;
} TEB_ACTIVE_FRAME, *PTEB_ACTIVE_FRAME;

typedef struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME
{
	struct _RTL_ACTIVATION_CONTEXT_STACK_FRAME *Previous;
	struct _ACTIVATION_CONTEXT                 *ActivationContext;
	ULONG                                       Flags;
} RTL_ACTIVATION_CONTEXT_STACK_FRAME, *PRTL_ACTIVATION_CONTEXT_STACK_FRAME;

typedef struct _ACTIVATION_CONTEXT_STACK
{
	ULONG                               Flags;
	ULONG                               NextCookieSequenceNumber;
	RTL_ACTIVATION_CONTEXT_STACK_FRAME *ActiveFrame;
	LIST_ENTRY                          FrameListCache;
} ACTIVATION_CONTEXT_STACK, *PACTIVATION_CONTEXT_STACK;

typedef struct _TEB
{
	NT_TIB NtTib;

	PBYTE EnvironmentPointer;
	CLIENT_ID ClientId;
	PBYTE ActiveRpcHandle;
	PBYTE ThreadLocalStoragePointer;
	PPEB ProcessEnvironmentBlock;

	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;
	PBYTE CsrClientThread;
	PBYTE Win32ThreadInfo;
	ULONG User32Reserved[26];
	ULONG UserReserved[5];
	PBYTE WOW32Reserved;
	LCID CurrentLocale;
	ULONG FpSoftwareStatusRegister;
	PBYTE SystemReserved1[54];
	NTSTATUS ExceptionCode;
	PACTIVATION_CONTEXT_STACK ActivationContextStackPointer;
#ifdef _WIN64
	UCHAR SpareBytes[24];
#else
	UCHAR SpareBytes[36];
#endif
	ULONG TxFsContext;

	GDI_TEB_BATCH GdiTebBatch;
	CLIENT_ID RealClientId;
	HANDLE GdiCachedProcessHandle;
	ULONG GdiClientPID;
	ULONG GdiClientTID;
	PBYTE GdiThreadLocalInfo;
	ULONG_PTR Win32ClientInfo[62];
	PBYTE glDispatchTable[233];
	ULONG_PTR glReserved1[29];
	PBYTE glReserved2;
	PBYTE glSectionInfo;
	PBYTE glSection;
	PBYTE glTable;
	PBYTE glCurrentRC;
	PBYTE glContext;

	NTSTATUS LastStatusValue;
	UNICODE_STRING StaticUnicodeString;
	WCHAR StaticUnicodeBuffer[261];

	PBYTE DeallocationStack;
	PBYTE TlsSlots[64];
	LIST_ENTRY TlsLinks;

	PBYTE Vdm;
	PBYTE ReservedForNtRpc;
	PBYTE DbgSsReserved[2];

	ULONG HardErrorMode;
#ifdef _WIN64
	PBYTE Instrumentation[11];
#else
	PVOID Instrumentation[9];
#endif
	GUID ActivityId;

	PBYTE SubProcessTag;
	PBYTE EtwLocalData;
	PBYTE EtwTraceData;
	PBYTE WinSockData;
	ULONG GdiBatchCount;

	union
	{
		PROCESSOR_NUMBER CurrentIdealProcessor;
		ULONG IdealProcessorValue;
		struct
		{
			UCHAR ReservedPad0;
			UCHAR ReservedPad1;
			UCHAR ReservedPad2;
			UCHAR IdealProcessor;
		};
	};

	ULONG GuaranteedStackBytes;
	PBYTE ReservedForPerf;
	PBYTE ReservedForOle;
	ULONG WaitingOnLoaderLock;
	PBYTE SavedPriorityState;
	ULONG_PTR SoftPatchPtr1;
	PBYTE ThreadPoolData;
	PBYTE *TlsExpansionSlots;
#ifdef _WIN64
	PBYTE DeallocationBStore;
	PBYTE BStoreLimit;
#endif
	ULONG MuiGeneration;
	ULONG IsImpersonating;
	PBYTE NlsCache;
	PBYTE pShimData;
	ULONG HeapVirtualAffinity;
	HANDLE CurrentTransactionHandle;
	PTEB_ACTIVE_FRAME ActiveFrame;
	PBYTE FlsData;

	PBYTE PreferredLanguages;
	PBYTE UserPrefLanguages;
	PBYTE MergedPrefLanguages;
	ULONG MuiImpersonation;

	union
	{
		USHORT CrossTebFlags;
		USHORT SpareCrossTebBits : 16;
	};
	union
	{
		USHORT SameTebFlags;
		struct
		{
			USHORT SafeThunkCall : 1;
			USHORT InDebugPrint : 1;
			USHORT HasFiberData : 1;
			USHORT SkipThreadAttach : 1;
			USHORT WerInShipAssertCode : 1;
			USHORT RanProcessInit : 1;
			USHORT ClonedThread : 1;
			USHORT SuppressDebugMsg : 1;
			USHORT DisableUserStackWalk : 1;
			USHORT RtlExceptionAttached : 1;
			USHORT InitialThread : 1;
			USHORT SessionAware : 1;
			USHORT SpareSameTebBits : 4;
		};
	};

	PBYTE TxnScopeEnterCallback;
	PBYTE TxnScopeExitCallback;
	PBYTE TxnScopeContext;
	ULONG LockCount;
	ULONG SpareUlong0;
	PBYTE ResourceRetValue;
	PBYTE ReservedForWdf;
} TEB, *PTEB;

typedef struct _THREAD_BASIC_INFORMATION
{
	NTSTATUS ExitStatus;
	PTEB TebBaseAddress;
	CLIENT_ID ClientId;
	ULONG_PTR AffinityMask;
	KPRIORITY Priority;
	LONG BasePriority;
} THREAD_BASIC_INFORMATION, *PTHREAD_BASIC_INFORMATION;

typedef struct _SYSTEM_BASIC_INFORMATION {
	ULONG Reserved;
	ULONG TimerResolution;
	ULONG PageSize;
	ULONG NumberOfPhysicalPages;
	ULONG LowestPhysicalPageNumber;
	ULONG HighestPhysicalPageNumber;
	ULONG AllocationGranularity;
	ULONG_PTR MinimumUserModeAddress;
	ULONG_PTR MaximumUserModeAddress;
	KAFFINITY ActiveProcessorsAffinityMask;
	CCHAR NumberOfProcessors;
} SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

FORCEINLINE PPEB NTAPI NtCurrentPeb()
{
	return (PPEB)NtCurrentTeb()->ProcessEnvironmentBlock;
}

typedef struct _PROCESS_BASIC_INFORMATION
{
	NTSTATUS ExitStatus;
	PPEB PebBaseAddress;
	ULONG_PTR AffinityMask;
	KPRIORITY BasePriority;
	HANDLE UniqueProcessId;
	HANDLE InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION, *PPROCESS_BASIC_INFORMATION;

typedef struct _PROCESS_BASIC_INFORMATION_WOW64 {
	NTSTATUS ExitStatus;
	PTR_64(PPEB) PebBaseAddress;
	PTR_64(ULONG_PTR) AffinityMask;
	KPRIORITY BasePriority;
	PTR_64(HANDLE) UniqueProcessId;
	PTR_64(HANDLE) InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION_WOW64, *PPROCESS_BASIC_INFORMATION_WOW64;

typedef struct _PROCESS_BASIC_INFORMATION32
{
	NTSTATUS ExitStatus;
	PTR_32(PPEB) PebBaseAddress;
	PTR_32(ULONG_PTR) AffinityMask;
	KPRIORITY BasePriority;
	PTR_32(HANDLE) UniqueProcessId;
	PTR_32(HANDLE) InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION32, *PPROCESS_BASIC_INFORMATION32;

typedef struct _PROCESS_BASIC_INFORMATION64
{
	NTSTATUS ExitStatus;
	PTR_64(PPEB) PebBaseAddress;
	PTR_64(ULONG_PTR) AffinityMask;
	KPRIORITY BasePriority;
	PTR_64(HANDLE) UniqueProcessId;
	PTR_64(HANDLE) InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION64, *PPROCESS_BASIC_INFORMATION64;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PVOID Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_WOW64 {
	USHORT UniqueProcessId;
	USHORT CreatorBackTraceIndex;
	UCHAR ObjectTypeIndex;
	UCHAR HandleAttributes;
	USHORT HandleValue;
	PTR_64(PVOID) Object;
	ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO_WOW64, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO_WOW64;

typedef struct _SYSTEM_HANDLE_INFORMATION_WOW64 {
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO_WOW64 Handles[1];
} SYSTEM_HANDLE_INFORMATION_WOW64, *PSYSTEM_HANDLE_INFORMATION_WOW64;

// private
typedef struct _PROCESS_HANDLE_TABLE_ENTRY_INFO {
	HANDLE HandleValue;
	ULONG_PTR HandleCount;
	ULONG_PTR PointerCount;
	ULONG GrantedAccess;
	ULONG ObjectTypeIndex;
	ULONG HandleAttributes;
	ULONG Reserved;
} PROCESS_HANDLE_TABLE_ENTRY_INFO, *PPROCESS_HANDLE_TABLE_ENTRY_INFO;

typedef struct _PROCESS_HANDLE_SNAPSHOT_INFORMATION {
	ULONG_PTR NumberOfHandles;
	ULONG_PTR Reserved;
	PROCESS_HANDLE_TABLE_ENTRY_INFO Handles[1];
} PROCESS_HANDLE_SNAPSHOT_INFORMATION, *PPROCESS_HANDLE_SNAPSHOT_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX
{
	PBYTE Object;
	ULONG_PTR UniqueProcessId;
	ULONG_PTR HandleValue;
	ULONG GrantedAccess;
	USHORT CreatorBackTraceIndex;
	USHORT ObjectTypeIndex;
	ULONG  HandleAttributes;
	ULONG  Reserved;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO_EX;

typedef enum _MEMORY_INFORMATION_CLASS
{
	MemoryBasicInformation,
	MemoryWorkingSetInformation,
	MemoryMappedFilenameInformation,	//MemorySectionName, UNICODE_STRING, Wrapper: GetMappedFileNameW
	MemoryRegionInformation,			//MemoryBasicVlmInformation, MEMORY_REGION_INFORMATION
	MemoryWorkingSetExInformation
} MEMORY_INFORMATION_CLASS;

typedef struct _SYSTEM_EXTENDED_THREAD_INFORMATION
{
	SYSTEM_THREAD_INFORMATION ThreadInfo;
	PBYTE StackBase;
	PBYTE StackLimit;
	PBYTE Win32StartAddress;
	PBYTE TebAddress; /* This is only filled in on Vista and above */
	ULONG_PTR Reserved2;
	ULONG_PTR Reserved3;
	ULONG_PTR Reserved4;
} SYSTEM_EXTENDED_THREAD_INFORMATION, *PSYSTEM_EXTENDED_THREAD_INFORMATION;

typedef struct _PROCESS_EXTENDED_BASIC_INFORMATION
{
	SIZE_T Size; // set to sizeof structure on input
	PROCESS_BASIC_INFORMATION BasicInfo;
	union
	{
		ULONG Flags;
		struct
		{
			ULONG IsProtectedProcess : 1;
			ULONG IsWow64Process : 1;
			ULONG IsProcessDeleting : 1;
			ULONG IsCrossSessionCreate : 1;
			ULONG IsFrozen : 1;
			ULONG IsBackground : 1;
			ULONG IsStronglyNamed : 1;
			ULONG SpareBits : 25;
		};
	};
} PROCESS_EXTENDED_BASIC_INFORMATION, *PPROCESS_EXTENDED_BASIC_INFORMATION;

typedef enum _DBG_STATE
{
	DbgIdle,
	DbgReplyPending,
	DbgCreateThreadStateChange,
	DbgCreateProcessStateChange,
	DbgExitThreadStateChange,
	DbgExitProcessStateChange,
	DbgExceptionStateChange,
	DbgBreakpointStateChange,
	DbgSingleStepStateChange,
	DbgLoadDllStateChange,
	DbgUnloadDllStateChange
} DBG_STATE, *PDBG_STATE;

typedef struct _DBGUI_WAIT_STATE_CHANGE
{
	DBG_STATE NewState;
	CLIENT_ID AppClientId;
	//union {
	//	DBGKM_EXCEPTION Exception;
	//	DBGUI_CREATE_THREAD CreateThread;
	//	DBGUI_CREATE_PROCESS CreateProcessInfo;
	//	DBGKM_EXIT_THREAD ExitThread;
	//	DBGKM_EXIT_PROCESS ExitProcess;
	//	DBGKM_LOAD_DLL LoadDll;
	//	DBGKM_UNLOAD_DLL UnloadDll;
	//} StateInfo;
} DBGUI_WAIT_STATE_CHANGE, *PDBGUI_WAIT_STATE_CHANGE;

typedef struct _OBJECT_ATTRIBUTES {
	ULONG Length;
	HANDLE RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PBYTE SecurityDescriptor;
	PBYTE SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef struct __declspec(align(16)) _OBJECT_ATTRIBUTES_WOW64 {
	ULONG Length;
	PTR_64(HANDLE) RootDirectory;
	PTR_64(PUNICODE_STRING64) ObjectName;
	ULONG Attributes;
	PTR_64(PBYTE) SecurityDescriptor;
	PTR_64(PBYTE) SecurityQualityOfService;
} OBJECT_ATTRIBUTES_WOW64, *POBJECT_ATTRIBUTES_WOW64;

#define ConvertObjectAttributesWow64(Obj64, Obj) { \
(Obj64)->Attributes = (Obj)->Attributes;\
(Obj64)->Length = sizeof(OBJECT_ATTRIBUTES_WOW64);\
(Obj64)->RootDirectory = WOW64_CONVERT(HANDLE) (Obj)->RootDirectory;\
(Obj64)->SecurityDescriptor = WOW64_CONVERT(PBYTE) (Obj)->SecurityDescriptor;\
(Obj64)->SecurityQualityOfService = WOW64_CONVERT(PBYTE) (Obj)->SecurityQualityOfService;\
(Obj64)->ObjectName = WOW64_CONVERT(PUNICODE_STRING64) HcAlloc(sizeof(UNICODE_STRING64));\
((PUNICODE_STRING64) (Obj64)->ObjectName)->Length = (Obj)->ObjectName->Length; \
((PUNICODE_STRING64) (Obj64)->ObjectName)->MaximumLength = (Obj)->ObjectName->MaximumLength; \
((PUNICODE_STRING64) (Obj64)->ObjectName)->Buffer = WOW64_CONVERT(PWSTR) (Obj)->ObjectName->Buffer; \
}\

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
	HANDLE Section;
	PBYTE MappedBase;
	PBYTE ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	UCHAR  FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX
{
	ULONG_PTR NumberOfHandles;
	ULONG_PTR Reserved;
	SYSTEM_HANDLE_TABLE_ENTRY_INFO_EX Handles[1];
} SYSTEM_HANDLE_INFORMATION_EX, *PSYSTEM_HANDLE_INFORMATION_EX;

typedef struct _OBJECT_BASIC_INFORMATION
{
	ULONG Attributes;
	ACCESS_MASK GrantedAccess;
	ULONG HandleCount;
	ULONG PointerCount;
	ULONG PagedPoolCharge;
	ULONG NonPagedPoolCharge;
	ULONG Reserved[3];
	ULONG NameInfoSize;
	ULONG TypeInfoSize;
	ULONG SecurityDescriptorSize;
	LARGE_INTEGER CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;

typedef struct _OBJECT_NAME_INFORMATION
{
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, *POBJECT_NAME_INFORMATION;

typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING TypeName;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccessMask;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	ULONG PoolType;
	ULONG DefaultPagedPoolCharge;
	ULONG DefaultNonPagedPoolCharge;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

typedef struct _OBJECT_TYPES_INFORMATION
{
	ULONG NumberOfTypes;
	//OBJECT_TYPE_INFORMATION TypeInformation[1];
} OBJECT_TYPES_INFORMATION, *POBJECT_TYPES_INFORMATION;

typedef struct _OBJECT_HANDLE_FLAG_INFORMATION
{
	BOOLEAN Inherit;
	BOOLEAN ProtectFromClose;
} OBJECT_HANDLE_FLAG_INFORMATION, *POBJECT_HANDLE_FLAG_INFORMATION;

typedef struct _RTL_DEBUG_INFORMATION
{
	HANDLE SectionHandleClient;
	PBYTE ViewBaseClient;
	PBYTE ViewBaseTarget;
	ULONG_PTR ViewBaseDelta;
	HANDLE EventPairClient;
	HANDLE EventPairTarget;
	HANDLE TargetProcessId;
	HANDLE TargetThreadHandle;
	ULONG Flags;
	SIZE_T OffsetFree;
	SIZE_T CommitSize;
	SIZE_T ViewSize;
	PBYTE Modules; //PRTL_PROCESS_MODULES
	PBYTE BackTraces; //PRTL_PROCESS_BACKTRACES
	PBYTE Heaps; //PRTL_PROCESS_HEAPS
	PBYTE Locks; //PRTL_PROCESS_LOCKS
	PBYTE SpecificHeap;
	HANDLE TargetProcessHandle;
	PBYTE Reserved[6];
} RTL_DEBUG_INFORMATION, *PRTL_DEBUG_INFORMATION;

typedef
VOID
(*PPS_APC_ROUTINE) (
	__in_opt PBYTE ApcArgument1,
	__in_opt PBYTE ApcArgument2,
	__in_opt PBYTE ApcArgument3
	);

typedef struct _RTLP_CURDIR_REF *PRTLP_CURDIR_REF;

typedef struct _RTL_RELATIVE_NAME_U
{
	UNICODE_STRING RelativeName;
	HANDLE ContainingDirectory;
	PRTLP_CURDIR_REF CurDirRef;
} RTL_RELATIVE_NAME_U, *PRTL_RELATIVE_NAME_U;

typedef struct _INITIAL_TEB
{
	PVOID PreviousStackBase;
	PVOID PreviousStackLimit;
	PVOID StackBase;
	PVOID StackLimit;
	PVOID AllocatedStackBase;
} INITIAL_TEB, *PINITIAL_TEB;

//0x22C FlsHighIndex, x64 0x0350
typedef struct _RTL_UNKNOWN_FLS_DATA {
	PBYTE unk2;
	PBYTE address;
	PBYTE unk3;
	PBYTE unk4;
} RTL_UNKNOWN_FLS_DATA, *PRTL_UNKNOWN_FLS_DATA;

typedef struct _FLS_CALLBACK_INFO //0x20C PEB FlsCallback, x64 0x320
{
	PBYTE unk1;
	PBYTE unk2;
	PBYTE address;
	PBYTE unk3;
	PBYTE unk4;
} FLS_CALLBACK_INFO, *PFLS_CALLBACK_INFO;

typedef struct _IO_STATUS_BLOCK {
	union {
		NTSTATUS Status;
		PBYTE Pointer;
	};

	ULONG_PTR Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef struct DECLSPEC_ALIGN(16) _IO_STATUS_BLOCK_WOW64 {
	union {
		NTSTATUS Status;
		PTR_64(PBYTE) Pointer;
	};

	PTR_64(ULONG_PTR) Information;
} IO_STATUS_BLOCK_WOW64, *PIO_STATUS_BLOCK_WOW64;

typedef
VOID
(NTAPI *PIO_APC_ROUTINE) (
	IN PBYTE ApcContext,
	IN PIO_STATUS_BLOCK IoStatusBlock,
	IN ULONG Reserved
	);

typedef
VOID
(NTAPI *PIO_APC_ROUTINE_WOW64) (
	IN PTR_64(PBYTE) ApcContext,
	IN PTR_64(PIO_STATUS_BLOCK_WOW64) IoStatusBlock,
	IN ULONG Reserved
	);

typedef struct _PS_ATTRIBUTE
{
	ULONG Attribute;
	SIZE_T Size;
	union
	{
		ULONG Value;
		PBYTE ValuePtr;
	};
	PSIZE_T ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
	SIZE_T TotalLength;
	PS_ATTRIBUTE Attributes[1];
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;

typedef enum _PROCESSINFOCLASS
{
	ProcessBasicInformation, // 0, q: PROCESS_BASIC_INFORMATION, PROCESS_EXTENDED_BASIC_INFORMATION
	ProcessQuotaLimits, // qs: QUOTA_LIMITS, QUOTA_LIMITS_EX
	ProcessIoCounters, // q: IO_COUNTERS
	ProcessVmCounters, // q: VM_COUNTERS, VM_COUNTERS_EX
	ProcessTimes, // q: KERNEL_USER_TIMES
	ProcessBasePriority, // s: KPRIORITY
	ProcessRaisePriority, // s: ULONG
	ProcessDebugPort, // q: HANDLE
	ProcessExceptionPort, // s: HANDLE
	ProcessAccessToken, // s: PROCESS_ACCESS_TOKEN
	ProcessLdtInformation, // 10
	ProcessLdtSize,
	ProcessDefaultHardErrorMode, // qs: ULONG
	ProcessIoPortHandlers, // (kernel-mode only)
	ProcessPooledUsageAndLimits, // q: POOLED_USAGE_AND_LIMITS
	ProcessWorkingSetWatch, // q: PROCESS_WS_WATCH_INFORMATION[]; s: void
	ProcessUserModeIOPL,
	ProcessEnableAlignmentFaultFixup, // s: BOOLEAN
	ProcessPriorityClass, // qs: PROCESS_PRIORITY_CLASS
	ProcessWx86Information,
	ProcessHandleCount, // 20, q: ULONG, PROCESS_HANDLE_INFORMATION
	ProcessAffinityMask, // s: KAFFINITY
	ProcessPriorityBoost, // qs: ULONG
	ProcessDeviceMap, // qs: PROCESS_DEVICEMAP_INFORMATION, PROCESS_DEVICEMAP_INFORMATION_EX
	ProcessSessionInformation, // q: PROCESS_SESSION_INFORMATION
	ProcessForegroundInformation, // s: PROCESS_FOREGROUND_BACKGROUND
	ProcessWow64Information, // q: ULONG_PTR
	ProcessImageFileName, // q: UNICODE_STRING
	ProcessLUIDDeviceMapsEnabled, // q: ULONG
	ProcessBreakOnTermination, // qs: ULONG
	ProcessDebugObjectHandle, // 30, q: HANDLE
	ProcessDebugFlags, // qs: ULONG
	ProcessHandleTracing, // q: PROCESS_HANDLE_TRACING_QUERY; s: size 0 disables, otherwise enables
	ProcessIoPriority, // qs: ULONG
	ProcessExecuteFlags, // qs: ULONG
	ProcessResourceManagement,
	ProcessCookie, // q: ULONG
	ProcessImageInformation, // q: SECTION_IMAGE_INFORMATION
	ProcessCycleTime, // q: PROCESS_CYCLE_TIME_INFORMATION // since VISTA
	ProcessPagePriority, // q: ULONG
	ProcessInstrumentationCallback, // 40
	ProcessThreadStackAllocation, // s: PROCESS_STACK_ALLOCATION_INFORMATION, PROCESS_STACK_ALLOCATION_INFORMATION_EX
	ProcessWorkingSetWatchEx, // q: PROCESS_WS_WATCH_INFORMATION_EX[]
	ProcessImageFileNameWin32, // q: UNICODE_STRING
	ProcessImageFileMapping, // q: HANDLE (input)
	ProcessAffinityUpdateMode, // qs: PROCESS_AFFINITY_UPDATE_MODE
	ProcessMemoryAllocationMode, // qs: PROCESS_MEMORY_ALLOCATION_MODE
	ProcessGroupInformation, // q: USHORT[]
	ProcessTokenVirtualizationEnabled, // s: ULONG
	ProcessConsoleHostProcess, // q: ULONG_PTR
	ProcessWindowInformation, // 50, q: PROCESS_WINDOW_INFORMATION
	ProcessHandleInformation, // q: PROCESS_HANDLE_SNAPSHOT_INFORMATION // since WIN8
	ProcessMitigationPolicy, // s: PROCESS_MITIGATION_POLICY_INFORMATION
	ProcessDynamicFunctionTableInformation,
	ProcessHandleCheckingMode,
	ProcessKeepAliveCount, // q: PROCESS_KEEPALIVE_COUNT_INFORMATION
	ProcessRevokeFileHandles, // s: PROCESS_REVOKE_FILE_HANDLES_INFORMATION
	ProcessWorkingSetControl, // s: PROCESS_WORKING_SET_CONTROL
	ProcessHandleTable, // since WINBLUE
	ProcessCheckStackExtentsMode,
	ProcessCommandLineInformation, // 60, q: UNICODE_STRING
	ProcessProtectionInformation, // q: PS_PROTECTION
	MaxProcessInfoClass
} PROCESSINFOCLASS;

typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemBasicInformation, // q: SYSTEM_BASIC_INFORMATION
	SystemProcessorInformation, // q: SYSTEM_PROCESSOR_INFORMATION
	SystemPerformanceInformation, // q: SYSTEM_PERFORMANCE_INFORMATION
	SystemTimeOfDayInformation, // q: SYSTEM_TIMEOFDAY_INFORMATION
	SystemPathInformation, // not implemented
	SystemProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
	SystemCallCountInformation, // q: SYSTEM_CALL_COUNT_INFORMATION
	SystemDeviceInformation, // q: SYSTEM_DEVICE_INFORMATION
	SystemProcessorPerformanceInformation, // q: SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION
	SystemFlagsInformation, // q: SYSTEM_FLAGS_INFORMATION
	SystemCallTimeInformation, // 10, not implemented
	SystemModuleInformation, // q: RTL_PROCESS_MODULES
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation, // not implemented
	SystemNonPagedPoolInformation, // not implemented
	SystemHandleInformation, // q: SYSTEM_HANDLE_INFORMATION
	SystemObjectInformation, // q: SYSTEM_OBJECTTYPE_INFORMATION mixed with SYSTEM_OBJECT_INFORMATION
	SystemPageFileInformation, // q: SYSTEM_PAGEFILE_INFORMATION
	SystemVdmInstemulInformation, // q
	SystemVdmBopInformation, // 20, not implemented
	SystemFileCacheInformation, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemCache)
	SystemPoolTagInformation, // q: SYSTEM_POOLTAG_INFORMATION
	SystemInterruptInformation, // q: SYSTEM_INTERRUPT_INFORMATION
	SystemDpcBehaviorInformation, // q: SYSTEM_DPC_BEHAVIOR_INFORMATION; s: SYSTEM_DPC_BEHAVIOR_INFORMATION (requires SeLoadDriverPrivilege)
	SystemFullMemoryInformation, // not implemented
	SystemLoadGdiDriverInformation, // s (kernel-mode only)
	SystemUnloadGdiDriverInformation, // s (kernel-mode only)
	SystemTimeAdjustmentInformation, // q: SYSTEM_QUERY_TIME_ADJUST_INFORMATION; s: SYSTEM_SET_TIME_ADJUST_INFORMATION (requires SeSystemtimePrivilege)
	SystemSummaryMemoryInformation, // not implemented
	SystemMirrorMemoryInformation, // 30, s (requires license value "Kernel-MemoryMirroringSupported") (requires SeShutdownPrivilege)
	SystemPerformanceTraceInformation, // s
	SystemObsolete0, // not implemented
	SystemExceptionInformation, // q: SYSTEM_EXCEPTION_INFORMATION
	SystemCrashDumpStateInformation, // s (requires SeDebugPrivilege)
	SystemKernelDebuggerInformation, // q: SYSTEM_KERNEL_DEBUGGER_INFORMATION
	SystemContextSwitchInformation, // q: SYSTEM_CONTEXT_SWITCH_INFORMATION
	SystemRegistryQuotaInformation, // q: SYSTEM_REGISTRY_QUOTA_INFORMATION; s (requires SeIncreaseQuotaPrivilege)
	SystemExtendServiceTableInformation, // s (requires SeLoadDriverPrivilege) // loads win32k only
	SystemPrioritySeperation, // s (requires SeTcbPrivilege)
	SystemVerifierAddDriverInformation, // 40, s (requires SeDebugPrivilege)
	SystemVerifierRemoveDriverInformation, // s (requires SeDebugPrivilege)
	SystemProcessorIdleInformation, // q: SYSTEM_PROCESSOR_IDLE_INFORMATION
	SystemLegacyDriverInformation, // q: SYSTEM_LEGACY_DRIVER_INFORMATION
	SystemCurrentTimeZoneInformation, // q
	SystemLookasideInformation, // q: SYSTEM_LOOKASIDE_INFORMATION
	SystemTimeSlipNotification, // s (requires SeSystemtimePrivilege)
	SystemSessionCreate, // not implemented
	SystemSessionDetach, // not implemented
	SystemSessionInformation, // not implemented
	SystemRangeStartInformation, // 50, q
	SystemVerifierInformation, // q: SYSTEM_VERIFIER_INFORMATION; s (requires SeDebugPrivilege)
	SystemVerifierThunkExtend, // s (kernel-mode only)
	SystemSessionProcessInformation, // q: SYSTEM_SESSION_PROCESS_INFORMATION
	SystemLoadGdiDriverInSystemSpace, // s (kernel-mode only) (same as SystemLoadGdiDriverInformation)
	SystemNumaProcessorMap, // q
	SystemPrefetcherInformation, // q: PREFETCHER_INFORMATION; s: PREFETCHER_INFORMATION // PfSnQueryPrefetcherInformation
	SystemExtendedProcessInformation, // q: SYSTEM_PROCESS_INFORMATION
	SystemRecommendedSharedDataAlignment, // q
	SystemComPlusPackage, // q; s
	SystemNumaAvailableMemory, // 60
	SystemProcessorPowerInformation, // q: SYSTEM_PROCESSOR_POWER_INFORMATION
	SystemEmulationBasicInformation, // q
	SystemEmulationProcessorInformation,
	SystemExtendedHandleInformation, // q: SYSTEM_HANDLE_INFORMATION_EX
	SystemLostDelayedWriteInformation, // q: ULONG
	SystemBigPoolInformation, // q: SYSTEM_BIGPOOL_INFORMATION
	SystemSessionPoolTagInformation, // q: SYSTEM_SESSION_POOLTAG_INFORMATION
	SystemSessionMappedViewInformation, // q: SYSTEM_SESSION_MAPPED_VIEW_INFORMATION
	SystemHotpatchInformation, // q; s
	SystemObjectSecurityMode, // 70, q
	SystemWatchdogTimerHandler, // s (kernel-mode only)
	SystemWatchdogTimerInformation, // q (kernel-mode only); s (kernel-mode only)
	SystemLogicalProcessorInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION
	SystemWow64SharedInformationObsolete, // not implemented
	SystemRegisterFirmwareTableInformationHandler, // s (kernel-mode only)
	SystemFirmwareTableInformation, // not implemented
	SystemModuleInformationEx, // q: RTL_PROCESS_MODULE_INFORMATION_EX
	SystemVerifierTriageInformation, // not implemented
	SystemSuperfetchInformation, // q: SUPERFETCH_INFORMATION; s: SUPERFETCH_INFORMATION // PfQuerySuperfetchInformation
	SystemMemoryListInformation, // 80, q: SYSTEM_MEMORY_LIST_INFORMATION; s: SYSTEM_MEMORY_LIST_COMMAND (requires SeProfileSingleProcessPrivilege)
	SystemFileCacheInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (same as SystemFileCacheInformation)
	SystemThreadPriorityClientIdInformation, // s: SYSTEM_THREAD_CID_PRIORITY_INFORMATION (requires SeIncreaseBasePriorityPrivilege)
	SystemProcessorIdleCycleTimeInformation, // q: SYSTEM_PROCESSOR_IDLE_CYCLE_TIME_INFORMATION[]
	SystemVerifierCancellationInformation, // not implemented // name:wow64:whNT32QuerySystemVerifierCancellationInformation
	SystemProcessorPowerInformationEx, // not implemented
	SystemRefTraceInformation, // q; s // ObQueryRefTraceInformation
	SystemSpecialPoolInformation, // q; s (requires SeDebugPrivilege) // MmSpecialPoolTag, then MmSpecialPoolCatchOverruns != 0
	SystemProcessIdInformation, // q: SYSTEM_PROCESS_ID_INFORMATION
	SystemErrorPortInformation, // s (requires SeTcbPrivilege)
	SystemBootEnvironmentInformation, // 90, q: SYSTEM_BOOT_ENVIRONMENT_INFORMATION
	SystemHypervisorInformation, // q; s (kernel-mode only)
	SystemVerifierInformationEx, // q; s
	SystemTimeZoneInformation, // s (requires SeTimeZonePrivilege)
	SystemImageFileExecutionOptionsInformation, // s: SYSTEM_IMAGE_FILE_EXECUTION_OPTIONS_INFORMATION (requires SeTcbPrivilege)
	SystemCoverageInformation, // q; s // name:wow64:whNT32QuerySystemCoverageInformation; ExpCovQueryInformation
	SystemPrefetchPatchInformation, // not implemented
	SystemVerifierFaultsInformation, // s (requires SeDebugPrivilege)
	SystemSystemPartitionInformation, // q: SYSTEM_SYSTEM_PARTITION_INFORMATION
	SystemSystemDiskInformation, // q: SYSTEM_SYSTEM_DISK_INFORMATION
	SystemProcessorPerformanceDistribution, // 100, q: SYSTEM_PROCESSOR_PERFORMANCE_DISTRIBUTION
	SystemNumaProximityNodeInformation, // q
	SystemDynamicTimeZoneInformation, // q; s (requires SeTimeZonePrivilege)
	SystemCodeIntegrityInformation, // q // SeCodeIntegrityQueryInformation
	SystemProcessorMicrocodeUpdateInformation, // s
	SystemProcessorBrandString, // q // HaliQuerySystemInformation -> HalpGetProcessorBrandString, info class 23
	SystemVirtualAddressInformation, // q: SYSTEM_VA_LIST_INFORMATION[]; s: SYSTEM_VA_LIST_INFORMATION[] (requires SeIncreaseQuotaPrivilege) // MmQuerySystemVaInformation
	SystemLogicalProcessorAndGroupInformation, // q: SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX // since WIN7 // KeQueryLogicalProcessorRelationship
	SystemProcessorCycleTimeInformation, // q: SYSTEM_PROCESSOR_CYCLE_TIME_INFORMATION[]
	SystemStoreInformation, // q; s // SmQueryStoreInformation
	SystemRegistryAppendString, // 110, s: SYSTEM_REGISTRY_APPEND_STRING_PARAMETERS
	SystemAitSamplingValue, // s: ULONG (requires SeProfileSingleProcessPrivilege)
	SystemVhdBootInformation, // q: SYSTEM_VHD_BOOT_INFORMATION
	SystemCpuQuotaInformation, // q; s // PsQueryCpuQuotaInformation
	SystemNativeBasicInformation, // not implemented
	SystemSpare1, // not implemented
	SystemLowPriorityIoInformation, // q: SYSTEM_LOW_PRIORITY_IO_INFORMATION
	SystemTpmBootEntropyInformation, // q: TPM_BOOT_ENTROPY_NT_RESULT // ExQueryTpmBootEntropyInformation
	SystemVerifierCountersInformation, // q: SYSTEM_VERIFIER_COUNTERS_INFORMATION
	SystemPagedPoolInformationEx, // q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypePagedPool)
	SystemSystemPtesInformationEx, // 120, q: SYSTEM_FILECACHE_INFORMATION; s (requires SeIncreaseQuotaPrivilege) (info for WorkingSetTypeSystemPtes)
	SystemNodeDistanceInformation, // q
	SystemAcpiAuditInformation, // q: SYSTEM_ACPI_AUDIT_INFORMATION // HaliQuerySystemInformation -> HalpAuditQueryResults, info class 26
	SystemBasicPerformanceInformation, // q: SYSTEM_BASIC_PERFORMANCE_INFORMATION // name:wow64:whNtQuerySystemInformation_SystemBasicPerformanceInformation
	SystemQueryPerformanceCounterInformation, // q: SYSTEM_QUERY_PERFORMANCE_COUNTER_INFORMATION // since WIN7 SP1
	SystemSessionBigPoolInformation, // since WIN8
	SystemBootGraphicsInformation,
	SystemScrubPhysicalMemoryInformation,
	SystemBadPageInformation,
	SystemProcessorProfileControlArea,
	SystemCombinePhysicalMemoryInformation, // 130
	SystemEntropyInterruptTimingCallback,
	SystemConsoleInformation,
	SystemPlatformBinaryInformation,
	SystemThrottleNotificationInformation,
	SystemHypervisorProcessorCountInformation,
	SystemDeviceDataInformation,
	SystemDeviceDataEnumerationInformation,
	SystemMemoryTopologyInformation,
	SystemMemoryChannelInformation,
	SystemBootLogoInformation, // 140
	SystemProcessorPerformanceInformationEx, // since WINBLUE
	SystemSpare0,
	SystemSecureBootPolicyInformation,
	SystemPageFileInformationEx,
	SystemSecureBootInformation,
	SystemEntropyInterruptTimingRawInformation,
	SystemPortableWorkspaceEfiLauncherInformation,
	SystemFullProcessInformation, // q: SYSTEM_PROCESS_INFORMATION with SYSTEM_PROCESS_INFORMATION_EXTENSION (requires admin)
	SystemKernelDebuggerInformationEx,
	SystemBootMetadataInformation, // 150
	SystemSoftRebootInformation,
	SystemElamCertificateInformation,
	SystemOfflineDumpConfigInformation,
	SystemProcessorFeaturesInformation,
	SystemRegistryReconciliationInformation,
	SystemEdidInformation,
	MaxSystemInfoClass
} SYSTEM_INFORMATION_CLASS;

typedef struct _PROCESS_WINDOW_INFORMATION
{
	ULONG WindowFlags;
	USHORT WindowTitleLength;
	WCHAR WindowTitle[1];
} PROCESS_WINDOW_INFORMATION, *PPROCESS_WINDOW_INFORMATION;

typedef enum _OBJECT_INFORMATION_CLASS
{
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectTypesInformation, //OBJECT_TYPES_INFORMATION
	ObjectHandleFlagInformation, //OBJECT_HANDLE_FLAG_INFORMATION
	ObjectSessionInformation,
	MaxObjectInfoClass  // MaxObjectInfoClass should always be the last enum
} OBJECT_INFORMATION_CLASS;

typedef enum _THREADINFOCLASS
{
	ThreadBasicInformation, // q: THREAD_BASIC_INFORMATION
	ThreadTimes, // q: KERNEL_USER_TIMES
	ThreadPriority, // s: KPRIORITY
	ThreadBasePriority, // s: LONG
	ThreadAffinityMask, // s: KAFFINITY
	ThreadImpersonationToken, // s: HANDLE
	ThreadDescriptorTableEntry,
	ThreadEnableAlignmentFaultFixup, // s: BOOLEAN
	ThreadEventPair,
	ThreadQuerySetWin32StartAddress, // q: PVOID
	ThreadZeroTlsCell, // 10
	ThreadPerformanceCount, // q: LARGE_INTEGER
	ThreadAmILastThread, // q: ULONG
	ThreadIdealProcessor, // s: ULONG
	ThreadPriorityBoost, // qs: ULONG
	ThreadSetTlsArrayAddress,
	ThreadIsIoPending, // q: ULONG
	ThreadHideFromDebugger, // s: void, BOOLEAN
	ThreadBreakOnTermination, // qs: ULONG
	ThreadSwitchLegacyState,
	ThreadIsTerminated, // 20, q: ULONG
	ThreadLastSystemCall, // q: THREAD_LAST_SYSCALL_INFORMATION
	ThreadIoPriority, // qs: ULONG
	ThreadCycleTime, // q: THREAD_CYCLE_TIME_INFORMATION
	ThreadPagePriority, // q: ULONG
	ThreadActualBasePriority,
	ThreadTebInformation, // q: THREAD_TEB_INFORMATION (requires THREAD_GET_CONTEXT + THREAD_SET_CONTEXT)
	ThreadCSwitchMon,
	ThreadCSwitchPmu,
	ThreadWow64Context, // q: WOW64_CONTEXT
	ThreadGroupInformation, // 30, q: GROUP_AFFINITY
	ThreadUmsInformation,
	ThreadCounterProfiling,
	ThreadIdealProcessorEx, // q: PROCESSOR_NUMBER
	ThreadCpuAccountingInformation, // since WIN8
	ThreadSuspendCount, // since WINBLUE
	MaxThreadInfoClass
} THREADINFOCLASS;

typedef enum _FSINFOCLASS
{
	FileFsVolumeInformation = 1,
	FileFsLabelInformation,      // 2
	FileFsSizeInformation,       // 3
	FileFsDeviceInformation,     // 4
	FileFsAttributeInformation,  // 5
	FileFsControlInformation,    // 6
	FileFsFullSizeInformation,   // 7
	FileFsObjectIdInformation,   // 8
	FileFsDriverPathInformation, // 9
	FileFsMaximumInformation
} FS_INFORMATION_CLASS, *PFS_INFORMATION_CLASS;

typedef enum _SECTION_INFORMATION_CLASS
{
	SectionBasicInformation,
	SectionImageInformation,
	SectionRelocationInformation, // name:wow64:whNtQuerySection_SectionRelocationInformation
	MaxSectionInfoClass
} SECTION_INFORMATION_CLASS;

typedef enum _KEY_INFORMATION_CLASS
{
	KeyBasicInformation,
	KeyNodeInformation,
	KeyFullInformation,
	KeyNameInformation,
	KeyCachedInformation,
	KeyFlagsInformation,
	KeyVirtualizationInformation,
	KeyHandleTagsInformation,
	KeyTrustInformation,
	MaxKeyInfoClass
} KEY_INFORMATION_CLASS;

typedef enum _KEY_VALUE_INFORMATION_CLASS
{
	KeyValueBasicInformation,
	KeyValueFullInformation,
	KeyValuePartialInformation,
	KeyValueFullInformationAlign64,
	KeyValuePartialInformationAlign64,
	MaxKeyValueInfoClass
} KEY_VALUE_INFORMATION_CLASS;

typedef enum _SYSDBG_COMMAND
{
	SysDbgQueryModuleInformation,
	SysDbgQueryTraceInformation,
	SysDbgSetTracepoint,
	SysDbgSetSpecialCall,
	SysDbgClearSpecialCalls,
	SysDbgQuerySpecialCalls,
	SysDbgBreakPoint,
	SysDbgQueryVersion,
	SysDbgReadVirtual,
	SysDbgWriteVirtual,
	SysDbgReadPhysical,
	SysDbgWritePhysical,
	SysDbgReadControlSpace,
	SysDbgWriteControlSpace,
	SysDbgReadIoSpace,
	SysDbgWriteIoSpace,
	SysDbgReadMsr,
	SysDbgWriteMsr,
	SysDbgReadBusData,
	SysDbgWriteBusData,
	SysDbgCheckLowMemory,
	SysDbgEnableKernelDebugger,
	SysDbgDisableKernelDebugger,
	SysDbgGetAutoKdEnable,
	SysDbgSetAutoKdEnable,
	SysDbgGetPrintBufferSize,
	SysDbgSetPrintBufferSize,
	SysDbgGetKdUmExceptionEnable,
	SysDbgSetKdUmExceptionEnable,
	SysDbgGetTriageDump,
	SysDbgGetKdBlockEnable,
	SysDbgSetKdBlockEnable,
} SYSDBG_COMMAND, *PSYSDBG_COMMAND;

typedef enum _DEBUGOBJECTINFOCLASS
{
	DebugObjectFlags = 1,
	MaxDebugObjectInfoClass
} DEBUGOBJECTINFOCLASS, *PDEBUGOBJECTINFOCLASS;

typedef enum _FILE_INFORMATION_CLASS
{
	FileDirectoryInformation = 1,
	FileFullDirectoryInformation,
	FileBothDirectoryInformation,
	FileBasicInformation,
	FileStandardInformation,
	FileInternalInformation,
	FileEaInformation,
	FileAccessInformation,
	FileNameInformation,
	FileRenameInformation, // 10
	FileLinkInformation,
	FileNamesInformation,
	FileDispositionInformation,
	FilePositionInformation,
	FileFullEaInformation,
	FileModeInformation,
	FileAlignmentInformation,
	FileAllInformation,
	FileAllocationInformation,
	FileEndOfFileInformation, // 20
	FileAlternateNameInformation,
	FileStreamInformation,
	FilePipeInformation,
	FilePipeLocalInformation,
	FilePipeRemoteInformation,
	FileMailslotQueryInformation,
	FileMailslotSetInformation,
	FileCompressionInformation,
	FileObjectIdInformation,
	FileCompletionInformation, // 30
	FileMoveClusterInformation,
	FileQuotaInformation,
	FileReparsePointInformation,
	FileNetworkOpenInformation,
	FileAttributeTagInformation,
	FileTrackingInformation,
	FileIdBothDirectoryInformation,
	FileIdFullDirectoryInformation,
	FileValidDataLengthInformation,
	FileShortNameInformation, // 40
	FileIoCompletionNotificationInformation,
	FileIoStatusBlockRangeInformation,
	FileIoPriorityHintInformation,
	FileSfioReserveInformation,
	FileSfioVolumeInformation,
	FileHardLinkInformation,
	FileProcessIdsUsingFileInformation,
	FileNormalizedNameInformation,
	FileNetworkPhysicalNameInformation,
	FileIdGlobalTxDirectoryInformation, // 50
	FileIsRemoteDeviceInformation,
	FileAttributeCacheInformation,
	FileNumaNodeInformation,
	FileStandardLinkInformation,
	FileRemoteProtocolInformation,
	FileRenameInformationBypassAccessCheck, // (kernel-mode only) // since WIN8
	FileLinkInformationBypassAccessCheck, // (kernel-mode only)
	FileIntegrityStreamInformation,
	FileVolumeNameInformation,
	FileIdInformation,
	FileIdExtdDirectoryInformation,
	FileReplaceCompletionInformation, // since WINBLUE
	FileHardLinkFullIdInformation,
	FileMaximumInformation
} FILE_INFORMATION_CLASS, *PFILE_INFORMATION_CLASS;


typedef struct _RTL_BUFFER {
    PWCHAR    Buffer;
    PWCHAR    StaticBuffer;
    SIZE_T    Size;
    SIZE_T    StaticSize;
    SIZE_T    ReservedForAllocatedSize; // for future doubling
    PVOID     ReservedForIMalloc; // for future pluggable growth
} RTL_BUFFER, *PRTL_BUFFER;

typedef enum _LDR_DLL_LOAD_REASON
{
	LoadReasonStaticDependency,
	LoadReasonStaticForwarderDependency,
	LoadReasonDynamicForwarderDependency,
	LoadReasonDelayloadDependency,
	LoadReasonDynamicLoad,
	LoadReasonAsImageLoad,
	LoadReasonAsDataLoad,
	LoadReasonUnknown = -1
} LDR_DLL_LOAD_REASON, *PLDR_DLL_LOAD_REASON;

typedef enum _LDR_DDAG_STATE
{
	LdrModulesMerged = -5,
	LdrModulesInitError = -4,
	LdrModulesSnapError = -3,
	LdrModulesUnloaded = -2,
	LdrModulesUnloading = -1,
	LdrModulesPlaceHolder = 0,
	LdrModulesMapping = 1,
	LdrModulesMapped = 2,
	LdrModulesWaitingForDependencies = 3,
	LdrModulesSnapping = 4,
	LdrModulesSnapped = 5,
	LdrModulesCondensed = 6,
	LdrModulesReadyToInit = 7,
	LdrModulesInitializing = 8,
	LdrModulesReadyToRun = 9
} LDR_DDAG_STATE;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	HMODULE ModuleBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullModuleName;
	UNICODE_STRING BaseModuleName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union
	{
		LIST_ENTRY HashLinks;
		struct
		{
			PBYTE SectionPointer;
			ULONG CheckSum;
		};
	};
	union
	{
		ULONG TimeDateStamp;
		PBYTE LoadedImports;
	};
	DWORD EntryPointActivationContext; //_ACTIVATION_CONTEXT * EntryPointActivationContext; 
	PBYTE PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

struct _RTL_UNICODE_STRING_BUFFER;

typedef struct _RTL_UNICODE_STRING_BUFFER {
	UNICODE_STRING String;
	RTL_BUFFER     ByteBuffer;
	UCHAR          MinimumStaticBufferForTerminalNul[sizeof(WCHAR)];
} RTL_UNICODE_STRING_BUFFER, *PRTL_UNICODE_STRING_BUFFER;

typedef enum _WINDOWINFOCLASS
{
	WindowProcess = 0, //HANDLE
	WindowRealWindowOwner = 1,
	WindowThread = 2, //HANDLE
	WindowIsHung = 5 //BOOLEAN

} WINDOWINFOCLASS;

typedef struct
{
	UNICODE_STRING SectionFileName;
	WCHAR NameBuffer[MAX_PATH];
} MEMORY_SECTION_NAME, *PMEMORY_SECTION_NAME;

typedef struct {
	UNICODE_STRING64 SectionFileName;
	WCHAR NameBuffer[MAX_PATH];
} MEMORY_SECTION_NAME_WOW64, *PMEMORY_SECTION_NAME_WOW64;

typedef struct _NtCreateThreadExBuffer {
	ULONG Size;
	ULONG Unknown1;
	ULONG Unknown2;
	PULONG Unknown3;
	ULONG Unknown4;
	ULONG Unknown5;
	ULONG Unknown6;
	PULONG Unknown7;
	ULONG Unknown8;
} NtCreateThreadExBuffer, *PNtCreateThreadExBuffer;

typedef enum _WAIT_TYPE {
	WaitAll,
	WaitAny
} WAIT_TYPE; 

typedef enum _EVENT_TYPE {
	NotificationEvent,
	SynchronizationEvent
} EVENT_TYPE;

typedef struct _FILE_EA_INFORMATION {
	ULONG EaSize;
} FILE_EA_INFORMATION, *PFILE_EA_INFORMATION;

typedef DWORD(WINAPI *PTHREAD_START_ROUTINE)(LPVOID);
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;


//
// Macro definition for defining IOCTL and FSCTL function control codes.  Note
// that function codes 0-2047 are reserved for Microsoft Corporation, and
// 2048-4095 are reserved for customers.
// 
// <winioctl.h>
//

#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)

// <winioctl.h>
#define FILE_DEVICE_BEEP                0x00000001
#define FILE_DEVICE_CD_ROM              0x00000002
#define FILE_DEVICE_CD_ROM_FILE_SYSTEM  0x00000003
#define FILE_DEVICE_CONTROLLER          0x00000004
#define FILE_DEVICE_DATALINK            0x00000005
#define FILE_DEVICE_DFS                 0x00000006
#define FILE_DEVICE_DISK                0x00000007
#define FILE_DEVICE_DISK_FILE_SYSTEM    0x00000008
#define FILE_DEVICE_FILE_SYSTEM         0x00000009
#define FILE_DEVICE_INPORT_PORT         0x0000000a
#define FILE_DEVICE_KEYBOARD            0x0000000b
#define FILE_DEVICE_MAILSLOT            0x0000000c
#define FILE_DEVICE_MIDI_IN             0x0000000d
#define FILE_DEVICE_MIDI_OUT            0x0000000e
#define FILE_DEVICE_MOUSE               0x0000000f
#define FILE_DEVICE_MULTI_UNC_PROVIDER  0x00000010
#define FILE_DEVICE_NAMED_PIPE          0x00000011
#define FILE_DEVICE_NETWORK             0x00000012
#define FILE_DEVICE_NETWORK_BROWSER     0x00000013
#define FILE_DEVICE_NETWORK_FILE_SYSTEM 0x00000014
#define FILE_DEVICE_NULL                0x00000015
#define FILE_DEVICE_PARALLEL_PORT       0x00000016
#define FILE_DEVICE_PHYSICAL_NETCARD    0x00000017
#define FILE_DEVICE_PRINTER             0x00000018
#define FILE_DEVICE_SCANNER             0x00000019
#define FILE_DEVICE_SERIAL_MOUSE_PORT   0x0000001a
#define FILE_DEVICE_SERIAL_PORT         0x0000001b
#define FILE_DEVICE_SCREEN              0x0000001c
#define FILE_DEVICE_SOUND               0x0000001d
#define FILE_DEVICE_STREAMS             0x0000001e
#define FILE_DEVICE_TAPE                0x0000001f
#define FILE_DEVICE_TAPE_FILE_SYSTEM    0x00000020
#define FILE_DEVICE_TRANSPORT           0x00000021
#define FILE_DEVICE_UNKNOWN             0x00000022
#define FILE_DEVICE_VIDEO               0x00000023
#define FILE_DEVICE_VIRTUAL_DISK        0x00000024
#define FILE_DEVICE_WAVE_IN             0x00000025
#define FILE_DEVICE_WAVE_OUT            0x00000026
#define FILE_DEVICE_8042_PORT           0x00000027
#define FILE_DEVICE_NETWORK_REDIRECTOR  0x00000028
#define FILE_DEVICE_BATTERY             0x00000029
#define FILE_DEVICE_BUS_EXTENDER        0x0000002a
#define FILE_DEVICE_MODEM               0x0000002b
#define FILE_DEVICE_VDM                 0x0000002c
#define FILE_DEVICE_MASS_STORAGE        0x0000002d
#define FILE_DEVICE_SMB                 0x0000002e
#define FILE_DEVICE_KS                  0x0000002f
#define FILE_DEVICE_CHANGER             0x00000030
#define FILE_DEVICE_SMARTCARD           0x00000031
#define FILE_DEVICE_ACPI                0x00000032
#define FILE_DEVICE_DVD                 0x00000033
#define FILE_DEVICE_FULLSCREEN_VIDEO    0x00000034
#define FILE_DEVICE_DFS_FILE_SYSTEM     0x00000035
#define FILE_DEVICE_DFS_VOLUME          0x00000036
#define FILE_DEVICE_SERENUM             0x00000037
#define FILE_DEVICE_TERMSRV             0x00000038
#define FILE_DEVICE_KSEC                0x00000039
#define FILE_DEVICE_FIPS                0x0000003A
#define FILE_DEVICE_INFINIBAND          0x0000003B
#define FILE_DEVICE_VMBUS               0x0000003E
#define FILE_DEVICE_CRYPT_PROVIDER      0x0000003F
#define FILE_DEVICE_WPD                 0x00000040
#define FILE_DEVICE_BLUETOOTH           0x00000041
#define FILE_DEVICE_MT_COMPOSITE        0x00000042
#define FILE_DEVICE_MT_TRANSPORT        0x00000043
#define FILE_DEVICE_BIOMETRIC           0x00000044
#define FILE_DEVICE_PMI                 0x00000045
#define FILE_DEVICE_EHSTOR              0x00000046
#define FILE_DEVICE_DEVAPI              0x00000047
#define FILE_DEVICE_GPIO                0x00000048
#define FILE_DEVICE_USBEX               0x00000049
#define FILE_DEVICE_CONSOLE             0x00000050
#define FILE_DEVICE_NFP                 0x00000051
#define FILE_DEVICE_SYSENV              0x00000052
#define FILE_DEVICE_VIRTUAL_BLOCK       0x00000053
#define FILE_DEVICE_POINT_OF_SERVICE    0x00000054

//
// Define the method codes for how buffers are passed for I/O and FS controls
// 
// <winioctl.h>
//

#define METHOD_BUFFERED                 0
#define METHOD_IN_DIRECT                1
#define METHOD_OUT_DIRECT               2
#define METHOD_NEITHER                  3

typedef struct _SINGLE_LIST_ENTRY32
{
	ULONG Next;
} SINGLE_LIST_ENTRY32, *PSINGLE_LIST_ENTRY32;

typedef struct _STRING32
{
	USHORT Length;
	USHORT MaximumLength;
	ULONG Buffer;
} STRING32, *PSTRING32;

typedef STRING32 UNICODE_STRING32, *PUNICODE_STRING32;
typedef STRING32 ANSI_STRING32, *PANSI_STRING32;

typedef struct _CLIENT_ID32
{
	ULONG UniqueProcess;
	ULONG UniqueThread;
} CLIENT_ID32, *PCLIENT_ID32;

// In USER_SHARED_DATA
typedef enum _WOW64_SHARED_INFORMATION
{
	SharedNtdll32LdrInitializeThunk,
	SharedNtdll32KiUserExceptionDispatcher,
	SharedNtdll32KiUserApcDispatcher,
	SharedNtdll32KiUserCallbackDispatcher,
	SharedNtdll32ExpInterlockedPopEntrySListFault,
	SharedNtdll32ExpInterlockedPopEntrySListResume,
	SharedNtdll32ExpInterlockedPopEntrySListEnd,
	SharedNtdll32RtlUserThreadStart,
	SharedNtdll32pQueryProcessDebugInformationRemote,
	SharedNtdll32BaseAddress,
	SharedNtdll32LdrSystemDllInitBlock,
	Wow64SharedPageEntriesCount
} WOW64_SHARED_INFORMATION;

typedef struct _RTL_BALANCED_NODE32
{
	union
	{
		PTR_32(struct _RTL_BALANCED_NODE *) Children[2];
		struct
		{
			PTR_32(struct _RTL_BALANCED_NODE *) Left;
			PTR_32(struct _RTL_BALANCED_NODE *) Right;
		};
	};
	union
	{
		PTR_32(UCHAR) Red : 1;
		PTR_32(UCHAR) Balance : 2;
		PTR_32(ULONG_PTR) ParentValue;
	};
} RTL_BALANCED_NODE32, *PRTL_BALANCED_NODE32;

typedef struct _RTL_RB_TREE32
{
	PTR_32(PRTL_BALANCED_NODE) Root;
	PTR_32(PRTL_BALANCED_NODE) Min;
} RTL_RB_TREE32, *PRTL_RB_TREE32;

typedef struct _PEB_LDR_DATA32
{
	ULONG Length;
	BOOLEAN Initialized;
	PTR_32(HANDLE) SsHandle;
	LIST_ENTRY32 InLoadOrderModuleList;
	LIST_ENTRY32 InMemoryOrderModuleList;
	LIST_ENTRY32 InInitializationOrderModuleList;
	PTR_32(PVOID) EntryInProgress;
	BOOLEAN ShutdownInProgress;
	PTR_32(HANDLE) ShutdownThreadId;
} PEB_LDR_DATA32, *PPEB_LDR_DATA32;

typedef struct _LDR_SERVICE_TAG_RECORD32
{
	PTR_32(struct _LDR_SERVICE_TAG_RECORD *) Next;
	ULONG ServiceTag;
} LDR_SERVICE_TAG_RECORD32, *PLDR_SERVICE_TAG_RECORD32;

typedef struct _LDRP_CSLIST32
{
	PTR_32(PSINGLE_LIST_ENTRY) Tail;
} LDRP_CSLIST32, *PLDRP_CSLIST32;

typedef struct _LDR_DDAG_NODE32
{
	LIST_ENTRY32 Modules;
	PTR_32(PLDR_SERVICE_TAG_RECORD) ServiceTagList;
	ULONG LoadCount;
	ULONG ReferenceCount;
	ULONG DependencyCount;
	union
	{
		LDRP_CSLIST32 Dependencies;
		SINGLE_LIST_ENTRY32 RemovalLink;
	};
	LDRP_CSLIST32 IncomingDependencies;
	LDR_DDAG_STATE State;
	SINGLE_LIST_ENTRY32 CondenseLink;
	ULONG PreorderNumber;
	ULONG LowestLink;
} LDR_DDAG_NODE32, *PLDR_DDAG_NODE32;

#define LDR_DATA_TABLE_ENTRY_SIZE_WINXP_32 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY32, DdagNode)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN7_32 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY32, BaseNameHashValue)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN8_32 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY32, ImplicitPathOptions)

typedef struct _LDR_DATA_TABLE_ENTRY32
{
	LIST_ENTRY32 InLoadOrderLinks;
	LIST_ENTRY32 InMemoryOrderLinks;
	union
	{
		LIST_ENTRY32 InInitializationOrderLinks;
		LIST_ENTRY32 InProgressLinks;
	};
	PTR_32(PVOID) DllBase;
	PTR_32(PVOID) EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING32 FullDllName;
	UNICODE_STRING32 BaseDllName;
	union
	{
		UCHAR FlagGroup[4];
		ULONG Flags;
		struct
		{
			ULONG PackagedBinary : 1;
			ULONG MarkedForRemoval : 1;
			ULONG ImageDll : 1;
			ULONG LoadNotificationsSent : 1;
			ULONG TelemetryEntryProcessed : 1;
			ULONG ProcessStaticImport : 1;
			ULONG InLegacyLists : 1;
			ULONG InIndexes : 1;
			ULONG ShimDll : 1;
			ULONG InExceptionTable : 1;
			ULONG ReservedFlags1 : 2;
			ULONG LoadInProgress : 1;
			ULONG LoadConfigProcessed : 1;
			ULONG EntryProcessed : 1;
			ULONG ProtectDelayLoad : 1;
			ULONG ReservedFlags3 : 2;
			ULONG DontCallForThreads : 1;
			ULONG ProcessAttachCalled : 1;
			ULONG ProcessAttachFailed : 1;
			ULONG CorDeferredValidate : 1;
			ULONG CorImage : 1;
			ULONG DontRelocate : 1;
			ULONG CorILOnly : 1;
			ULONG ReservedFlags5 : 3;
			ULONG Redirected : 1;
			ULONG ReservedFlags6 : 2;
			ULONG CompatDatabaseProcessed : 1;
		};
	};
	USHORT ObsoleteLoadCount;
	USHORT TlsIndex;
	LIST_ENTRY32 HashLinks;
	ULONG TimeDateStamp;
	PTR_32(struct _ACTIVATION_CONTEXT *) EntryPointActivationContext;
	PTR_32(PVOID) Lock;
	PTR_32(PLDR_DDAG_NODE) DdagNode;
	LIST_ENTRY32 NodeModuleLink;
	PTR_32(struct _LDRP_LOAD_CONTEXT *) LoadContext;
	PTR_32(PVOID) ParentDllBase;
	PTR_32(PVOID) SwitchBackContext;
	RTL_BALANCED_NODE32 BaseAddressIndexNode;
	RTL_BALANCED_NODE32 MappingInfoIndexNode;
	PTR_32(ULONG_PTR) OriginalBase;
	LARGE_INTEGER LoadTime;
	ULONG BaseNameHashValue;
	LDR_DLL_LOAD_REASON LoadReason;
	ULONG ImplicitPathOptions;
	ULONG ReferenceCount;
} LDR_DATA_TABLE_ENTRY32, *PLDR_DATA_TABLE_ENTRY32;

typedef struct _CURDIR32
{
	UNICODE_STRING32 DosPath;
	PTR_32(HANDLE) Handle;
} CURDIR32, *PCURDIR32;

typedef struct _RTL_DRIVE_LETTER_CURDIR32
{
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	STRING32 DosPath;
} RTL_DRIVE_LETTER_CURDIR32, *PRTL_DRIVE_LETTER_CURDIR32;

typedef struct _RTL_USER_PROCESS_PARAMETERS32
{
	ULONG MaximumLength;
	ULONG Length;

	ULONG Flags;
	ULONG DebugFlags;

	PTR_32(HANDLE) ConsoleHandle;
	ULONG ConsoleFlags;
	PTR_32(HANDLE) StandardInput;
	PTR_32(HANDLE) StandardOutput;
	PTR_32(HANDLE) StandardError;

	CURDIR32 CurrentDirectory;
	UNICODE_STRING32 DllPath;
	UNICODE_STRING32 ImagePathName;
	UNICODE_STRING32 CommandLine;
	PTR_32(PVOID) Environment;

	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;

	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING32 WindowTitle;
	UNICODE_STRING32 DesktopInfo;
	UNICODE_STRING32 ShellInfo;
	UNICODE_STRING32 RuntimeData;
	RTL_DRIVE_LETTER_CURDIR32 CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

	ULONG EnvironmentSize;
	ULONG EnvironmentVersion;
	PTR_32(PVOID) PackageDependencyData;
	ULONG ProcessGroupId;
	ULONG LoaderThreads;
} RTL_USER_PROCESS_PARAMETERS32, *PRTL_USER_PROCESS_PARAMETERS32;

typedef struct _PEB32
{
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	union
	{
		BOOLEAN BitField;
		struct
		{
			BOOLEAN ImageUsesLargePages : 1;
			BOOLEAN IsProtectedProcess : 1;
			BOOLEAN IsLegacyProcess : 1;
			BOOLEAN IsImageDynamicallyRelocated : 1;
			BOOLEAN SkipPatchingUser32Forwarders : 1;
			BOOLEAN IsPackagedProcess : 1;
			BOOLEAN IsAppContainer : 1;
			BOOLEAN SpareBits : 1;
		};
	};
	PTR_32(HANDLE) Mutant;

	PTR_32(PVOID) ImageBaseAddress;
	PTR_32(PPEB_LDR_DATA) Ldr;
	PTR_32(PRTL_USER_PROCESS_PARAMETERS) ProcessParameters;
	PTR_32(PVOID) SubSystemData;
	PTR_32(PVOID) ProcessHeap;
	PTR_32(PRTL_CRITICAL_SECTION) FastPebLock;
	PTR_32(PVOID) AtlThunkSListPtr;
	PTR_32(PVOID) IFEOKey;
	union
	{
		ULONG CrossProcessFlags;
		struct
		{
			ULONG ProcessInJob : 1;
			ULONG ProcessInitializing : 1;
			ULONG ProcessUsingVEH : 1;
			ULONG ProcessUsingVCH : 1;
			ULONG ProcessUsingFTH : 1;
			ULONG ReservedBits0 : 27;
		};
		ULONG EnvironmentUpdateCount;
	};
	union
	{
		PTR_32(PVOID) KernelCallbackTable;
		PTR_32(PVOID) UserSharedInfoPtr;
	};
	ULONG SystemReserved[1];
	ULONG AtlThunkSListPtr32;
	PTR_32(PVOID) ApiSetMap;
	ULONG TlsExpansionCounter;
	PTR_32(PVOID) TlsBitmap;
	ULONG TlsBitmapBits[2];
	PTR_32(PVOID) ReadOnlySharedMemoryBase;
	PTR_32(PVOID) HotpatchInformation;
	PTR_32(PVOID *) ReadOnlyStaticServerData;
	PTR_32(PVOID) AnsiCodePageData;
	PTR_32(PVOID) OemCodePageData;
	PTR_32(PVOID) UnicodeCaseTableData;

	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;

	LARGE_INTEGER CriticalSectionTimeout;
	PTR_32(SIZE_T) HeapSegmentReserve;
	PTR_32(SIZE_T) HeapSegmentCommit;
	PTR_32(SIZE_T) HeapDeCommitTotalFreeThreshold;
	PTR_32(SIZE_T) HeapDeCommitFreeBlockThreshold;

	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PTR_32(PVOID *) ProcessHeaps;

	PTR_32(PVOID) GdiSharedHandleTable;
	PTR_32(PVOID) ProcessStarterHelper;
	ULONG GdiDCAttributeList;

	PTR_32(PRTL_CRITICAL_SECTION) LoaderLock;

	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	USHORT OSBuildNumber;
	USHORT OSCSDVersion;
	ULONG OSPlatformId;
	ULONG ImageSubsystem;
	ULONG ImageSubsystemMajorVersion;
	ULONG ImageSubsystemMinorVersion;
	PTR_32(ULONG_PTR) ImageProcessAffinityMask;
	GDI_HANDLE_BUFFER32 GdiHandleBuffer;
	PTR_32(PVOID) PostProcessInitRoutine;

	PTR_32(PVOID) TlsExpansionBitmap;
	ULONG TlsExpansionBitmapBits[32];

	ULONG SessionId;

	ULARGE_INTEGER AppCompatFlags;
	ULARGE_INTEGER AppCompatFlagsUser;
	PTR_32(PVOID) pShimData;
	PTR_32(PVOID) AppCompatInfo;

	UNICODE_STRING32 CSDVersion;

	PTR_32(PVOID) ActivationContextData;
	PTR_32(PVOID) ProcessAssemblyStorageMap;
	PTR_32(PVOID) SystemDefaultActivationContextData;
	PTR_32(PVOID) SystemAssemblyStorageMap;

	PTR_32(SIZE_T) MinimumStackCommit;

	PTR_32(PVOID *) FlsCallback;
	LIST_ENTRY32 FlsListHead;
	PTR_32(PVOID) FlsBitmap;
	ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
	ULONG FlsHighIndex;

	PTR_32(PVOID) WerRegistrationData;
	PTR_32(PVOID) WerShipAssertPtr;
	PTR_32(PVOID) pContextData;
	PTR_32(PVOID) pImageHeaderHash;
	union
	{
		ULONG TracingFlags;
		struct
		{
			ULONG HeapTracingEnabled : 1;
			ULONG CritSecTracingEnabled : 1;
			ULONG LibLoaderTracingEnabled : 1;
			ULONG SpareTracingBits : 29;
		};
	};
	ULONGLONG CsrServerReadOnlySharedMemoryBase;
} PEB32, *PPEB32;

typedef struct _GDI_TEB_BATCH32
{
	ULONG Offset;
	PTR_32(ULONG_PTR) HDC;
	ULONG Buffer[310];
} GDI_TEB_BATCH32, *PGDI_TEB_BATCH32;

typedef struct _TEB32
{
	NT_TIB32 NtTib;

	PTR_32(PVOID) EnvironmentPointer;
	CLIENT_ID32 ClientId;
	PTR_32(PVOID) ActiveRpcHandle;
	PTR_32(PVOID) ThreadLocalStoragePointer;
	PTR_32(PPEB) ProcessEnvironmentBlock;

	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;
	PTR_32(PVOID) CsrClientThread;
	PTR_32(PVOID) Win32ThreadInfo;
	ULONG User32Reserved[26];
	ULONG UserReserved[5];
	PTR_32(PVOID) WOW32Reserved;
	LCID CurrentLocale;
	ULONG FpSoftwareStatusRegister;
	PTR_32(PVOID) SystemReserved1[54];
	NTSTATUS ExceptionCode;
	PTR_32(PVOID) ActivationContextStackPointer;
	BYTE SpareBytes[36];
	ULONG TxFsContext;

	GDI_TEB_BATCH32 GdiTebBatch;
	CLIENT_ID32 RealClientId;
	PTR_32(HANDLE) GdiCachedProcessHandle;
	ULONG GdiClientPID;
	ULONG GdiClientTID;
	PTR_32(PVOID) GdiThreadLocalInfo;
	PTR_32(ULONG_PTR) Win32ClientInfo[62];
	PTR_32(PVOID) glDispatchTable[233];
	PTR_32(ULONG_PTR) glReserved1[29];
	PTR_32(PVOID) glReserved2;
	PTR_32(PVOID) glSectionInfo;
	PTR_32(PVOID) glSection;
	PTR_32(PVOID) glTable;
	PTR_32(PVOID) glCurrentRC;
	PTR_32(PVOID) glContext;

	NTSTATUS LastStatusValue;
	UNICODE_STRING32 StaticUnicodeString;
	WCHAR StaticUnicodeBuffer[261];

	PTR_32(PVOID) DeallocationStack;
	PTR_32(PVOID) TlsSlots[64];
	LIST_ENTRY32 TlsLinks;
} TEB32, *PTEB32;

/* start 64bit definitions of above */

typedef struct _SINGLE_LIST_ENTRY64
{
	ULONG Next;
} SINGLE_LIST_ENTRY64, *PSINGLE_LIST_ENTRY64;

typedef struct _RTL_BALANCED_NODE64
{
	union
	{
		PTR_64(struct _RTL_BALANCED_NODE *) Children[2];
		struct
		{
			PTR_64(struct _RTL_BALANCED_NODE *) Left;
			PTR_64(struct _RTL_BALANCED_NODE *) Right;
		};
	};
	union
	{
		PTR_64(UCHAR) Red : 1;
		PTR_64(UCHAR) Balance : 2;
		PTR_64(ULONG_PTR) ParentValue;
	};
} RTL_BALANCED_NODE64, *PRTL_BALANCED_NODE64;

typedef struct _RTL_RB_TREE64
{
	PTR_64(PRTL_BALANCED_NODE) Root;
	PTR_64(PRTL_BALANCED_NODE) Min;
} RTL_RB_TREE64, *PRTL_RB_TREE64;

typedef struct _PEB_LDR_DATA64
{
	ULONG Length;
	BOOLEAN Initialized;
	PTR_64(HANDLE) SsHandle;
	LIST_ENTRY64 InLoadOrderModuleList;
	LIST_ENTRY64 InMemoryOrderModuleList;
	LIST_ENTRY64 InInitializationOrderModuleList;
	PTR_64(PVOID) EntryInProgress;
	BOOLEAN ShutdownInProgress;
	PTR_64(HANDLE) ShutdownThreadId;
} PEB_LDR_DATA64, *PPEB_LDR_DATA64;

typedef struct _LDR_SERVICE_TAG_RECORD64
{
	PTR_64(struct _LDR_SERVICE_TAG_RECORD *) Next;
	ULONG ServiceTag;
} LDR_SERVICE_TAG_RECORD64, *PLDR_SERVICE_TAG_RECORD64;

typedef struct _LDRP_CSLIST64
{
	PTR_64(PSINGLE_LIST_ENTRY) Tail;
} LDRP_CSLIST64, *PLDRP_CSLIST64;

typedef struct _LDR_DDAG_NODE64
{
	LIST_ENTRY64 Modules;
	PTR_64(PLDR_SERVICE_TAG_RECORD) ServiceTagList;
	ULONG LoadCount;
	ULONG ReferenceCount;
	ULONG DependencyCount;
	union
	{
		LDRP_CSLIST64 Dependencies;
		SINGLE_LIST_ENTRY64 RemovalLink;
	};
	LDRP_CSLIST64 IncomingDependencies;
	LDR_DDAG_STATE State;
	SINGLE_LIST_ENTRY64 CondenseLink;
	ULONG PreorderNumber;
	ULONG LowestLink;
} LDR_DDAG_NODE64, *PLDR_DDAG_NODE64;

#define LDR_DATA_TABLE_ENTRY_SIZE_WINXP_64 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY64, DdagNode)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN7_64 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY64, BaseNameHashValue)
#define LDR_DATA_TABLE_ENTRY_SIZE_WIN8_64 FIELD_OFFSET(LDR_DATA_TABLE_ENTRY64, ImplicitPathOptions)

typedef struct _LDR_DATA_TABLE_ENTRY64
{
	LIST_ENTRY64 InLoadOrderLinks;
	LIST_ENTRY64 InMemoryOrderLinks;
	union
	{
		LIST_ENTRY64 InInitializationOrderLinks;
		LIST_ENTRY64 InProgressLinks;
	};
	PTR_64(PVOID) DllBase;
	PTR_64(PVOID) EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING64 FullDllName;
	UNICODE_STRING64 BaseDllName;
	union
	{
		UCHAR FlagGroup[4];
		ULONG Flags;
		struct
		{
			ULONG PackagedBinary : 1;
			ULONG MarkedForRemoval : 1;
			ULONG ImageDll : 1;
			ULONG LoadNotificationsSent : 1;
			ULONG TelemetryEntryProcessed : 1;
			ULONG ProcessStaticImport : 1;
			ULONG InLegacyLists : 1;
			ULONG InIndexes : 1;
			ULONG ShimDll : 1;
			ULONG InExceptionTable : 1;
			ULONG ReservedFlags1 : 2;
			ULONG LoadInProgress : 1;
			ULONG LoadConfigProcessed : 1;
			ULONG EntryProcessed : 1;
			ULONG ProtectDelayLoad : 1;
			ULONG ReservedFlags3 : 2;
			ULONG DontCallForThreads : 1;
			ULONG ProcessAttachCalled : 1;
			ULONG ProcessAttachFailed : 1;
			ULONG CorDeferredValidate : 1;
			ULONG CorImage : 1;
			ULONG DontRelocate : 1;
			ULONG CorILOnly : 1;
			ULONG ReservedFlags5 : 3;
			ULONG Redirected : 1;
			ULONG ReservedFlags6 : 2;
			ULONG CompatDatabaseProcessed : 1;
		};
	};
	USHORT ObsoleteLoadCount;
	USHORT TlsIndex;
	LIST_ENTRY64 HashLinks;
	ULONG TimeDateStamp;
	PTR_64(struct _ACTIVATION_CONTEXT *) EntryPointActivationContext;
	PTR_64(PVOID) Lock;
	PTR_64(PLDR_DDAG_NODE) DdagNode;
	LIST_ENTRY64 NodeModuleLink;
	PTR_64(struct _LDRP_LOAD_CONTEXT *) LoadContext;
	PTR_64(PVOID) ParentDllBase;
	PTR_64(PVOID) SwitchBackContext;
	RTL_BALANCED_NODE64 BaseAddressIndexNode;
	RTL_BALANCED_NODE64 MappingInfoIndexNode;
	PTR_64(ULONG_PTR) OriginalBase;
	LARGE_INTEGER LoadTime;
	ULONG BaseNameHashValue;
	LDR_DLL_LOAD_REASON LoadReason;
	ULONG ImplicitPathOptions;
	ULONG ReferenceCount;
} LDR_DATA_TABLE_ENTRY64, *PLDR_DATA_TABLE_ENTRY64;

typedef struct _CURDIR64
{
	UNICODE_STRING64 DosPath;
	PTR_64(HANDLE) Handle;
} CURDIR64, *PCURDIR64;

typedef struct _RTL_DRIVE_LETTER_CURDIR64
{
	USHORT Flags;
	USHORT Length;
	ULONG TimeStamp;
	STRING64 DosPath;
} RTL_DRIVE_LETTER_CURDIR64, *PRTL_DRIVE_LETTER_CURDIR64;

typedef struct _RTL_USER_PROCESS_PARAMETERS64
{
	ULONG MaximumLength;
	ULONG Length;

	ULONG Flags;
	ULONG DebugFlags;

	PTR_64(HANDLE) ConsoleHandle;
	ULONG ConsoleFlags;
	PTR_64(HANDLE) StandardInput;
	PTR_64(HANDLE) StandardOutput;
	PTR_64(HANDLE) StandardError;

	CURDIR64 CurrentDirectory;
	UNICODE_STRING64 DllPath;
	UNICODE_STRING64 ImagePathName;
	UNICODE_STRING64 CommandLine;
	PTR_64(PVOID) Environment;

	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;

	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING64 WindowTitle;
	UNICODE_STRING64 DesktopInfo;
	UNICODE_STRING64 ShellInfo;
	UNICODE_STRING64 RuntimeData;
	RTL_DRIVE_LETTER_CURDIR64 CurrentDirectories[RTL_MAX_DRIVE_LETTERS];

	ULONG EnvironmentSize;
	ULONG EnvironmentVersion;
	PTR_64(PVOID) PackageDependencyData;
	ULONG ProcessGroupId;
	ULONG LoaderThreads;
} RTL_USER_PROCESS_PARAMETERS64, *PRTL_USER_PROCESS_PARAMETERS64;

typedef struct _PEB64
{
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	union
	{
		BOOLEAN BitField;
		struct
		{
			BOOLEAN ImageUsesLargePages : 1;
			BOOLEAN IsProtectedProcess : 1;
			BOOLEAN IsLegacyProcess : 1;
			BOOLEAN IsImageDynamicallyRelocated : 1;
			BOOLEAN SkipPatchingUser64Forwarders : 1;
			BOOLEAN IsPackagedProcess : 1;
			BOOLEAN IsAppContainer : 1;
			BOOLEAN SpareBits : 1;
		};
	};
	PTR_64(HANDLE) Mutant;

	PTR_64(PVOID) ImageBaseAddress;
	PTR_64(PPEB_LDR_DATA) Ldr;
	PTR_64(PRTL_USER_PROCESS_PARAMETERS) ProcessParameters;
	PTR_64(PVOID) SubSystemData;
	PTR_64(PVOID) ProcessHeap;
	PTR_64(PRTL_CRITICAL_SECTION) FastPebLock;
	PTR_64(PVOID) AtlThunkSListPtr;
	PTR_64(PVOID) IFEOKey;
	union
	{
		ULONG CrossProcessFlags;
		struct
		{
			ULONG ProcessInJob : 1;
			ULONG ProcessInitializing : 1;
			ULONG ProcessUsingVEH : 1;
			ULONG ProcessUsingVCH : 1;
			ULONG ProcessUsingFTH : 1;
			ULONG ReservedBits0 : 27;
		};
		ULONG EnvironmentUpdateCount;
	};
	union
	{
		PTR_64(PVOID) KernelCallbackTable;
		PTR_64(PVOID) UserSharedInfoPtr;
	};
	ULONG SystemReserved[1];
	ULONG AtlThunkSListPtr64;
	PTR_64(PVOID) ApiSetMap;
	ULONG TlsExpansionCounter;
	PTR_64(PVOID) TlsBitmap;
	ULONG TlsBitmapBits[2];
	PTR_64(PVOID) ReadOnlySharedMemoryBase;
	PTR_64(PVOID) HotpatchInformation;
	PTR_64(PVOID *) ReadOnlyStaticServerData;
	PTR_64(PVOID) AnsiCodePageData;
	PTR_64(PVOID) OemCodePageData;
	PTR_64(PVOID) UnicodeCaseTableData;

	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;

	LARGE_INTEGER CriticalSectionTimeout;
	PTR_64(SIZE_T) HeapSegmentReserve;
	PTR_64(SIZE_T) HeapSegmentCommit;
	PTR_64(SIZE_T) HeapDeCommitTotalFreeThreshold;
	PTR_64(SIZE_T) HeapDeCommitFreeBlockThreshold;

	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PTR_64(PVOID *) ProcessHeaps;

	PTR_64(PVOID) GdiSharedHandleTable;
	PTR_64(PVOID) ProcessStarterHelper;
	ULONG GdiDCAttributeList;

	PTR_64(PRTL_CRITICAL_SECTION) LoaderLock;

	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	USHORT OSBuildNumber;
	USHORT OSCSDVersion;
	ULONG OSPlatformId;
	ULONG ImageSubsystem;
	ULONG ImageSubsystemMajorVersion;
	ULONG ImageSubsystemMinorVersion;
	PTR_64(ULONG_PTR) ImageProcessAffinityMask;
	GDI_HANDLE_BUFFER64 GdiHandleBuffer;
	PTR_64(PVOID) PostProcessInitRoutine;

	PTR_64(PVOID) TlsExpansionBitmap;
	ULONG TlsExpansionBitmapBits[32];

	ULONG SessionId;

	ULARGE_INTEGER AppCompatFlags;
	ULARGE_INTEGER AppCompatFlagsUser;
	PTR_64(PVOID) pShimData;
	PTR_64(PVOID) AppCompatInfo;

	UNICODE_STRING64 CSDVersion;

	PTR_64(PVOID) ActivationContextData;
	PTR_64(PVOID) ProcessAssemblyStorageMap;
	PTR_64(PVOID) SystemDefaultActivationContextData;
	PTR_64(PVOID) SystemAssemblyStorageMap;

	PTR_64(SIZE_T) MinimumStackCommit;

	PTR_64(PVOID *) FlsCallback;
	LIST_ENTRY64 FlsListHead;
	PTR_64(PVOID) FlsBitmap;
	ULONG FlsBitmapBits[FLS_MAXIMUM_AVAILABLE / (sizeof(ULONG) * 8)];
	ULONG FlsHighIndex;

	PTR_64(PVOID) WerRegistrationData;
	PTR_64(PVOID) WerShipAssertPtr;
	PTR_64(PVOID) pContextData;
	PTR_64(PVOID) pImageHeaderHash;
	union
	{
		ULONG TracingFlags;
		struct
		{
			ULONG HeapTracingEnabled : 1;
			ULONG CritSecTracingEnabled : 1;
			ULONG LibLoaderTracingEnabled : 1;
			ULONG SpareTracingBits : 29;
		};
	};
	ULONGLONG CsrServerReadOnlySharedMemoryBase;
} PEB64, *PPEB64;

typedef struct _GDI_TEB_BATCH64
{
	ULONG Offset;
	PTR_64(ULONG_PTR) HDC;
	ULONG Buffer[310];
} GDI_TEB_BATCH64, *PGDI_TEB_BATCH64;

typedef struct _TEB64
{
	NT_TIB64 NtTib;

	PTR_64(PVOID) EnvironmentPointer;
	CLIENT_ID64 ClientId;
	PTR_64(PVOID) ActiveRpcHandle;
	PTR_64(PVOID) ThreadLocalStoragePointer;
	PTR_64(PPEB) ProcessEnvironmentBlock;

	ULONG LastErrorValue;
	ULONG CountOfOwnedCriticalSections;
	PTR_64(PVOID) CsrClientThread;
	PTR_64(PVOID) Win64ThreadInfo;
	ULONG User64Reserved[26];
	ULONG UserReserved[5];
	PTR_64(PVOID) WOW64Reserved;
	LCID CurrentLocale;
	ULONG FpSoftwareStatusRegister;
	PTR_64(PVOID) SystemReserved1[54];
	NTSTATUS ExceptionCode;
	PTR_64(PVOID) ActivationContextStackPointer;
	BYTE SpareBytes[36];
	ULONG TxFsContext;

	GDI_TEB_BATCH64 GdiTebBatch;
	CLIENT_ID64 RealClientId;
	PTR_64(HANDLE) GdiCachedProcessHandle;
	ULONG GdiClientPID;
	ULONG GdiClientTID;
	PTR_64(PVOID) GdiThreadLocalInfo;
	PTR_64(ULONG_PTR) Win32ClientInfo[62];
	PTR_64(PVOID) glDispatchTable[233];
	PTR_64(ULONG_PTR) glReserved1[29];
	PTR_64(PVOID) glReserved2;
	PTR_64(PVOID) glSectionInfo;
	PTR_64(PVOID) glSection;
	PTR_64(PVOID) glTable;
	PTR_64(PVOID) glCurrentRC;
	PTR_64(PVOID) glContext;

	NTSTATUS LastStatusValue;
	UNICODE_STRING64 StaticUnicodeString;
	WCHAR StaticUnicodeBuffer[261];

	PTR_64(PVOID) DeallocationStack;
	PTR_64(PVOID) TlsSlots[64];
	LIST_ENTRY64 TlsLinks;
} TEB64, *PTEB64;

//
// Object Manager Symbolic Link Specific Access Rights.
//

#define SYMBOLIC_LINK_QUERY (0x0001)
#define SYMBOLIC_LINK_ALL_ACCESS (STANDARD_RIGHTS_REQUIRED | 0x1)

typedef struct _OBJECT_DIRECTORY_INFORMATION {
	UNICODE_STRING Name;
	UNICODE_STRING TypeName;
} OBJECT_DIRECTORY_INFORMATION, *POBJECT_DIRECTORY_INFORMATION;

typedef struct  _OBJECT_DIRECTORY_INFORMATION_WOW64 {
	UNICODE_STRING64 Name;
	UNICODE_STRING64 TypeName;
} OBJECT_DIRECTORY_INFORMATION_WOW64, *POBJECT_DIRECTORY_INFORMATION_WOW64;

#define ConvertObjectDirectoryInformationWow64(o64, o) ConvertStringWow64(&((o64)->Name), &((o)->Name)); ConvertStringWow64(&((o64)->TypeName), &((o)->TypeName));
#define ConvertObjectDirectoryInformationFromWow64(o64, o) ConvertUnicodeStringFromWow64(&((o64)->Name), &((o)->Name)); ConvertUnicodeStringFromWow64(&((o64)->TypeName), &((o)->TypeName));

#define MAX_DOS_DRIVES 26

typedef struct _PROCESS_DEVICEMAP_INFORMATION {
	union {
		struct {
			ULONG DirectoryHandle;
		} Set;
		struct {
			ULONG DriveMap;
			UCHAR DriveType[32];
		} Query;
	} DUMMYUNIONNAME;
} PROCESS_DEVICEMAP_INFORMATION, *PPROCESS_DEVICEMAP_INFORMATION;

typedef struct __declspec(align(16))_PROCESS_DEVICEMAP_INFORMATION_WOW64 {
	union {
		struct {
			PTR_64(HANDLE) DirectoryHandle;
		} Set;
		struct {
			ULONG DriveMap;
			UCHAR DriveType[32];
		} Query;
	} DUMMYUNIONNAME;
} PROCESS_DEVICEMAP_INFORMATION_WOW64, *PPROCESS_DEVICEMAP_INFORMATION_WOW64;

#define ConvertProcessDeviceMapInformationFromWow64(o64, o){\
(o)->Set.DirectoryHandle = POINTER32_HARDCODED(HANDLE) ((o64)->Set.DirectoryHandle);\
(o)->Query.DriveMap = POINTER32_HARDCODED(ULONG) ((o64)->Query.DriveMap);\
HcInternalCopy((o)->Query.DriveType, (o64)->Query.DriveType, sizeof((o64)->Query.DriveType));\
}\

//
// Process priority classes
//
#define PROCESS_PRIORITY_CLASS_INVALID          0
#define PROCESS_PRIORITY_CLASS_IDLE             1
#define PROCESS_PRIORITY_CLASS_NORMAL           2
#define PROCESS_PRIORITY_CLASS_HIGH             3
#define PROCESS_PRIORITY_CLASS_REALTIME         4
#define PROCESS_PRIORITY_CLASS_BELOW_NORMAL     5
#define PROCESS_PRIORITY_CLASS_ABOVE_NORMAL     6

typedef struct _PROCESS_PRIORITY_CLASS
{
	BOOLEAN Foreground;
	UCHAR PriorityClass;
} PROCESS_PRIORITY_CLASS, *PPROCESS_PRIORITY_CLASS;

//
// Flags for NtCreateProcessEx
//
#define PROCESS_CREATE_FLAGS_BREAKAWAY              0x00000001
#define PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT       0x00000002
#define PROCESS_CREATE_FLAGS_INHERIT_HANDLES        0x00000004
#define PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE 0x00000008
#define PROCESS_CREATE_FLAGS_LARGE_PAGES            0x00000010
#define PROCESS_CREATE_FLAGS_ALL_LARGE_PAGE_FLAGS   PROCESS_CREATE_FLAGS_LARGE_PAGES
#define PROCESS_CREATE_FLAGS_LEGAL_MASKPROCESS_CREATE_FLAGS_BREAKAWAY | \
  PROCESS_CREATE_FLAGS_NO_DEBUG_INHERIT | \
  PROCESS_CREATE_FLAGS_INHERIT_HANDLES | \
  PROCESS_CREATE_FLAGS_OVERRIDE_ADDRESS_SPACE | \
  PROCESS_CREATE_FLAGS_ALL_LARGE_PAGE_FLAGS)

/* If the first isn't defined, assume none is */
#ifndef SE_MIN_WELL_KNOWN_PRIVILEGE
#define SE_MIN_WELL_KNOWN_PRIVILEGE       2L
#define SE_CREATE_TOKEN_PRIVILEGE         2L
#define SE_ASSIGNPRIMARYTOKEN_PRIVILEGE   3L
#define SE_LOCK_MEMORY_PRIVILEGE          4L
#define SE_INCREASE_QUOTA_PRIVILEGE       5L
#define SE_MACHINE_ACCOUNT_PRIVILEGE      6L
#define SE_TCB_PRIVILEGE                  7L
#define SE_SECURITY_PRIVILEGE             8L
#define SE_TAKE_OWNERSHIP_PRIVILEGE       9L
#define SE_LOAD_DRIVER_PRIVILEGE         10L
#define SE_SYSTEM_PROFILE_PRIVILEGE      11L
#define SE_SYSTEMTIME_PRIVILEGE          12L
#define SE_PROF_SINGLE_PROCESS_PRIVILEGE 13L
#define SE_INC_BASE_PRIORITY_PRIVILEGE   14L
#define SE_CREATE_PAGEFILE_PRIVILEGE     15L
#define SE_CREATE_PERMANENT_PRIVILEGE    16L
#define SE_BACKUP_PRIVILEGE              17L
#define SE_RESTORE_PRIVILEGE             18L
#define SE_SHUTDOWN_PRIVILEGE            19L
#define SE_DEBUG_PRIVILEGE               20L
#define SE_AUDIT_PRIVILEGE               21L
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE  22L
#define SE_CHANGE_NOTIFY_PRIVILEGE       23L
#define SE_REMOTE_SHUTDOWN_PRIVILEGE     24L
#define SE_UNDOCK_PRIVILEGE              25L
#define SE_SYNC_AGENT_PRIVILEGE          26L
#define SE_ENABLE_DELEGATION_PRIVILEGE   27L
#define SE_MANAGE_VOLUME_PRIVILEGE       28L
#define SE_IMPERSONATE_PRIVILEGE         29L
#define SE_CREATE_GLOBAL_PRIVILEGE       30L
#define SE_MAX_WELL_KNOWN_PRIVILEGE      SE_CREATE_GLOBAL_PRIVILEGE
#endif /* ndef SE_MIN_WELL_KNOWN_PRIVILEGE */

// KPCR Access for non-IA64 builds
//
#define K0IPCR                  ((ULONG_PTR)(KIP0PCRADDRESS))
#define PCR                     ((KPCR *)K0IPCR)
#if defined(CONFIG_SMP) || defined(NT_BUILD)
#undef  KeGetPcr
#define KeGetPcr()              ((KPCR *)__readfsdword(FIELD_OFFSET(KPCR, SelfPcr)))
#endif

//
// CPU Vendors
//
typedef enum {
	CPU_NONE = 0,
	CPU_INTEL = 1,
	CPU_AMD = 2,
	CPU_CYRIX = 3,
	CPU_TRANSMETA = 4,
	CPU_VIA = 5,
	CPU_CENTAUR = CPU_VIA,
	CPU_RISE = 6,
	CPU_UNKNOWN = 7
} CPU_VENDORS;

//
// Machine Types
//
#define MACHINE_TYPE_ISA        0x0000
#define MACHINE_TYPE_EISA       0x0001
#define MACHINE_TYPE_MCA        0x0002

//
// X86 80386 Segment Types
//
#define I386_TASK_GATE          0x5
#define I386_TSS                0x9
#define I386_ACTIVE_TSS         0xB
#define I386_CALL_GATE          0xC
#define I386_INTERRUPT_GATE     0xE
#define I386_TRAP_GATE          0xF

//
// Selector Names
//
#define RPL_MASK                0x0003
#define MODE_MASK               0x0001
#define KGDT_R0_CODE            0x8
#define KGDT_R0_DATA            0x10
#define KGDT_R3_CODE            0x18
#define KGDT_R3_DATA            0x20
#define KGDT_TSS                0x28
#define KGDT_R0_PCR             0x30
#define KGDT_R3_TEB             0x38
#define KGDT_LDT                0x48
#define KGDT_DF_TSS             0x50
#define KGDT_NMI_TSS            0x58

//
// Selector Names
//
#define KGDT64_NULL             0x0000
#define KGDT64_R0_CODE          0x0010
#define KGDT64_R0_DATA          0x0018
#define KGDT64_R3_CMCODE        0x0020
#define KGDT64_R3_DATA          0x0028
#define KGDT64_R3_CODE          0x0030
#define KGDT64_SYS_TSS          0x0040
#define KGDT64_R3_CMTEB         0x0050
#define KGDT64_R0_LDT           0x0060

//
// Define the number of GDTs that can be queried by user mode
//
#define KGDT_NUMBER             10

//
// CR4
//
#define CR4_VME                 0x1
#define CR4_PVI                 0x2
#define CR4_TSD                 0x4
#define CR4_DE                  0x8
#define CR4_PSE                 0x10
#define CR4_PAE                 0x20
#define CR4_MCE                 0x40
#define CR4_PGE                 0x80
#define CR4_FXSR                0x200
#define CR4_XMMEXCPT            0x400

//
// EFlags
//
#define EFLAGS_CF               0x01L
#define EFLAGS_ZF               0x40L
#define EFLAGS_TF               0x100L
#define EFLAGS_INTERRUPT_MASK   0x200L
#define EFLAGS_DF               0x400L
#define EFLAGS_IOPL             0x3000L
#define EFLAGS_NESTED_TASK      0x4000L
#define EFLAGS_RF               0x10000
#define EFLAGS_V86_MASK         0x20000
#define EFLAGS_ALIGN_CHECK      0x40000
#define EFLAGS_VIF              0x80000
#define EFLAGS_VIP              0x100000
#define EFLAGS_ID               0x200000
#define EFLAGS_USER_SANITIZE    0x3F4DD7
#define EFLAG_SIGN              0x8000
#define EFLAG_ZERO              0x4000

//
// Legacy floating status word bit masks.
//
#define FSW_INVALID_OPERATION   0x1
#define FSW_DENORMAL            0x2
#define FSW_ZERO_DIVIDE         0x4
#define FSW_OVERFLOW            0x8
#define FSW_UNDERFLOW           0x10
#define FSW_PRECISION           0x20
#define FSW_STACK_FAULT         0x40

//
// Machine Specific Registers
//
#define MSR_AMD_ACCESS          0x9C5A203A
#define MSR_IA32_MISC_ENABLE    0x01A0
#define MSR_EFER                0xC0000080

//
// MSR internal Values
//
#define MSR_NXE                 0x0800
#define XHF_NOEXECUTE           0x100000
#define MSR_XD_ENABLE_MASK      0xFFFFFFFB

//
// IPI Types
//
#define IPI_APC                 1
#define IPI_DPC                 2
#define IPI_FREEZE              4
#define IPI_PACKET_READY        8
#define IPI_SYNCH_REQUEST       16

//
// PRCB Flags
//
#define PRCB_MAJOR_VERSION      1
#define PRCB_BUILD_DEBUG        1
#define PRCB_BUILD_UNIPROCESSOR 2

//
// HAL Variables
//
#define INITIAL_STALL_COUNT     100
#define MM_HAL_VA_START         0xFFC00000
#define MM_HAL_VA_END           0xFFFFFFFF
#define APIC_BASE               0xFFFE0000

//
// IOPM Definitions
//
#define IOPM_COUNT              1
#define IOPM_SIZE               8192
#define IOPM_FULL_SIZE          8196
#define IO_ACCESS_MAP_NONE      0
#define IOPM_DIRECTION_MAP_SIZE 32
#define IOPM_OFFSET             FIELD_OFFSET(KTSS, IoMaps[0].IoMap)
#define KiComputeIopmOffset(MapNumber)              \
    (MapNumber == IO_ACCESS_MAP_NONE) ?             \
        (USHORT)(sizeof(KTSS)) :                    \
        (USHORT)(FIELD_OFFSET(KTSS, IoMaps[MapNumber-1].IoMap))

typedef UCHAR KIO_ACCESS_MAP[IOPM_SIZE];

typedef KIO_ACCESS_MAP *PKIO_ACCESS_MAP;

//
// Size of the XMM register save area in the FXSAVE format
//
#define SIZE_OF_FX_REGISTERS    128

//
// Static Kernel-Mode Address start (use MM_KSEG0_BASE for actual)
//
#define KSEG0_BASE              0x80000000

//
// Synchronization-level IRQL
//
#ifndef CONFIG_SMP
#define SYNCH_LEVEL             DISPATCH_LEVEL
#else
#if (NTDDI_VERSION < NTDDI_WS03)
#define SYNCH_LEVEL             (IPI_LEVEL - 1)
#else
#define SYNCH_LEVEL             (IPI_LEVEL - 2)
#endif
#endif

//
// Number of pool lookaside lists per pool in the PRCB
//
#define NUMBER_POOL_LOOKASIDE_LISTS 32

//
// Structure for CPUID
//
typedef union _CPU_INFO {
	UINT32 AsUINT32[4];
	struct {
		ULONG Eax;
		ULONG Ebx;
		ULONG Ecx;
		ULONG Edx;
	};
} CPU_INFO, *PCPU_INFO;

//
// Trap Frame Definition
//
typedef struct _KTRAP_FRAME {
	ULONG DbgEbp;
	ULONG DbgEip;
	ULONG DbgArgMark;
	ULONG DbgArgPointer;
	ULONG TempSegCs;
	ULONG TempEsp;
	ULONG Dr0;
	ULONG Dr1;
	ULONG Dr2;
	ULONG Dr3;
	ULONG Dr6;
	ULONG Dr7;
	ULONG SegGs;
	ULONG SegEs;
	ULONG SegDs;
	ULONG Edx;
	ULONG Ecx;
	ULONG Eax;
	ULONG PreviousPreviousMode;
	struct _EXCEPTION_REGISTRATION_RECORD FAR *ExceptionList;
	ULONG SegFs;
	ULONG Edi;
	ULONG Esi;
	ULONG Ebx;
	ULONG Ebp;
	ULONG ErrCode;
	ULONG Eip;
	ULONG SegCs;
	ULONG EFlags;
	ULONG HardwareEsp;
	ULONG HardwareSegSs;
	ULONG V86Es;
	ULONG V86Ds;
	ULONG V86Fs;
	ULONG V86Gs;
} KTRAP_FRAME, *PKTRAP_FRAME;

//
// Defines the Callback Stack Layout for User Mode Callbacks
//
typedef struct _KCALLOUT_FRAME {
	ULONG InitialStack;
	ULONG TrapFrame;
	ULONG CallbackStack;
	ULONG Edi;
	ULONG Esi;
	ULONG Ebx;
	ULONG Ebp;
	ULONG ReturnAddress;
	ULONG Result;
	ULONG ResultLength;
} KCALLOUT_FRAME, *PKCALLOUT_FRAME;

//
// LDT Entry Definition
//
#ifndef _LDT_ENTRY_DEFINED
#define _LDT_ENTRY_DEFINED
typedef struct _LDT_ENTRY {
	USHORT LimitLow;
	USHORT BaseLow;
	union {
		struct {
			UCHAR BaseMid;
			UCHAR Flags1;
			UCHAR Flags2;
			UCHAR BaseHi;
		} Bytes;
		struct {
			ULONG BaseMid : 8;
			ULONG Type : 5;
			ULONG Dpl : 2;
			ULONG Pres : 1;
			ULONG LimitHi : 4;
			ULONG Sys : 1;
			ULONG Reserved_0 : 1;
			ULONG Default_Big : 1;
			ULONG Granularity : 1;
			ULONG BaseHi : 8;
		} Bits;
	} HighWord;
} LDT_ENTRY, *PLDT_ENTRY, *LPLDT_ENTRY;
#endif

//
// GDT Entry Definition
//
typedef struct _KGDTENTRY {
	USHORT LimitLow;
	USHORT BaseLow;
	union {
		struct {
			UCHAR BaseMid;
			UCHAR Flags1;
			UCHAR Flags2;
			UCHAR BaseHi;
		} Bytes;
		struct {
			ULONG BaseMid : 8;
			ULONG Type : 5;
			ULONG Dpl : 2;
			ULONG Pres : 1;
			ULONG LimitHi : 4;
			ULONG Sys : 1;
			ULONG Reserved_0 : 1;
			ULONG Default_Big : 1;
			ULONG Granularity : 1;
			ULONG BaseHi : 8;
		} Bits;
	} HighWord;
} KGDTENTRY, *PKGDTENTRY;

//
// IDT Entry Access Definition
//
typedef struct _KIDT_ACCESS {
	union {
		struct {
			UCHAR Reserved;
			UCHAR SegmentType : 4;
			UCHAR SystemSegmentFlag : 1;
			UCHAR Dpl : 2;
			UCHAR Present : 1;
		};
		USHORT Value;
	};
} KIDT_ACCESS, *PKIDT_ACCESS;

//
// IDT Entry Definition
//
typedef struct _KIDTENTRY {
	USHORT Offset;
	USHORT Selector;
	USHORT Access;
	USHORT ExtendedOffset;
} KIDTENTRY, *PKIDTENTRY;

typedef struct _DESCRIPTOR {
	USHORT Pad;
	USHORT Limit;
	ULONG Base;
} KDESCRIPTOR, *PKDESCRIPTOR;

//
// FN/FX (FPU) Save Area Structures
//
typedef struct _FNSAVE_FORMAT {
	ULONG ControlWord;
	ULONG StatusWord;
	ULONG TagWord;
	ULONG ErrorOffset;
	ULONG ErrorSelector;
	ULONG DataOffset;
	ULONG DataSelector;
	UCHAR RegisterArea[80];
} FNSAVE_FORMAT, *PFNSAVE_FORMAT;

typedef struct _FXSAVE_FORMAT {
	USHORT ControlWord;
	USHORT StatusWord;
	USHORT TagWord;
	USHORT ErrorOpcode;
	ULONG ErrorOffset;
	ULONG ErrorSelector;
	ULONG DataOffset;
	ULONG DataSelector;
	ULONG MXCsr;
	ULONG MXCsrMask;
	UCHAR RegisterArea[SIZE_OF_FX_REGISTERS];
	UCHAR Reserved3[128];
	UCHAR Reserved4[224];
	UCHAR Align16Byte[8];
} FXSAVE_FORMAT, *PFXSAVE_FORMAT;

typedef struct _FX_SAVE_AREA {
	union {
		FNSAVE_FORMAT FnArea;
		FXSAVE_FORMAT FxArea;
	} U;
	ULONG NpxSavedCpu;
	ULONG Cr0NpxState;
} FX_SAVE_AREA, *PFX_SAVE_AREA;

//
// Special Registers Structure (outside of CONTEXT)
//
typedef struct _KSPECIAL_REGISTERS {
	ULONG Cr0;
	ULONG Cr2;
	ULONG Cr3;
	ULONG Cr4;
	ULONG KernelDr0;
	ULONG KernelDr1;
	ULONG KernelDr2;
	ULONG KernelDr3;
	ULONG KernelDr6;
	ULONG KernelDr7;
	KDESCRIPTOR Gdtr;
	KDESCRIPTOR Idtr;
	USHORT Tr;
	USHORT Ldtr;
	ULONG Reserved[6];
} KSPECIAL_REGISTERS, *PKSPECIAL_REGISTERS;

//
// Processor State Data
//
typedef struct _KPROCESSOR_STATE {
	CONTEXT ContextFrame;
	KSPECIAL_REGISTERS SpecialRegisters;
} KPROCESSOR_STATE, *PKPROCESSOR_STATE;

//
// TSS Definition
//
typedef struct _KiIoAccessMap {
	UCHAR DirectionMap[IOPM_DIRECTION_MAP_SIZE];
	UCHAR IoMap[IOPM_FULL_SIZE];
} KIIO_ACCESS_MAP;

typedef struct _KTSS {
	USHORT Backlink;
	USHORT Reserved0;
	ULONG Esp0;
	USHORT Ss0;
	USHORT Reserved1;
	ULONG NotUsed1[4];
	ULONG CR3;
	ULONG Eip;
	ULONG EFlags;
	ULONG Eax;
	ULONG Ecx;
	ULONG Edx;
	ULONG Ebx;
	ULONG Esp;
	ULONG Ebp;
	ULONG Esi;
	ULONG Edi;
	USHORT Es;
	USHORT Reserved2;
	USHORT Cs;
	USHORT Reserved3;
	USHORT Ss;
	USHORT Reserved4;
	USHORT Ds;
	USHORT Reserved5;
	USHORT Fs;
	USHORT Reserved6;
	USHORT Gs;
	USHORT Reserved7;
	USHORT LDT;
	USHORT Reserved8;
	USHORT Flags;
	USHORT IoMapBase;
	KIIO_ACCESS_MAP IoMaps[IOPM_COUNT];
	UCHAR IntDirectionMap[IOPM_DIRECTION_MAP_SIZE];
} KTSS, *PKTSS;

//
// i386 CPUs don't have exception frames
//
typedef struct _KEXCEPTION_FRAME KEXCEPTION_FRAME, *PKEXCEPTION_FRAME;

#endif /* NTOS_MODE_USER */