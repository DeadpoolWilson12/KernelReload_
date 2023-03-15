/*
	�ȿ�:����ֱ���޸��ض�λ��Ϊ���ں�ƫ�ƣ��ض�λ��Ҫ����Ϊ���ں�ƫ�ƣ��ٰ�SSDT���溯����ַ����Ϊ���ں˵�
	ԭ��:����ֻ�����ں˵ĺ�����ȫ�ֱ������������ں˵�
*/

#ifndef NTKRNLPARELOAD
#define NTKRNLPARELOAD

#include <ntddk.h>
#include <windef.h>
#include <ntimage.h>

#define FILEPATH L"\\??\\C:\\WINDOWS\\system32\\ntkrnlpa.exe"
#define PROTECTPROCESS "cheatengine-i38"   // cheatengine-i38, notepad.exe

typedef struct _LDR_DATA_TABLE_ENTRY32
{
	LIST_ENTRY32 InLoadOrderLinks;
	LIST_ENTRY32 InMemoryOrderLinks;
	LIST_ENTRY32 InInitializationOrderLinks;
	ULONG DllBase;
	ULONG EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING32 FullDllName;
	UNICODE_STRING32 BaseDllName;
	ULONG Flags;
	USHORT LoadCount;
	USHORT TlsIndex;
	LIST_ENTRY32 HashLinks;
	ULONG SectionPointer;
	ULONG CheckSum;
	ULONG TimeDateStamp;
	ULONG LoadedImports;
	ULONG EntryPointActivationContext;
	ULONG PatchInformation;
	LIST_ENTRY32 ForwarderLinks;
	LIST_ENTRY32 ServiceTagLinks;
	LIST_ENTRY32 StaticLinks;
	ULONG ContextInformation;
	ULONG OriginalBase;
	LARGE_INTEGER LoadTime;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _KSYSTEM_SERVICE_TABLE
{
	PULONG  ServiceTableBase;								// ��������ַ���ַ  
	PULONG  ServiceCounterTableBase;						// SSDT���������õĴ���
	ULONG   NumberOfService;								// �������ĸ���  
	PULONG   ParamTableBase;								// �������������ַ   
} KSYSTEM_SERVICE_TABLE, *PKSYSTEM_SERVICE_TABLE;

typedef struct _KSERVICE_TABLE_DESCRIPTOR
{
	KSYSTEM_SERVICE_TABLE   ntoskrnl;                       // ntoskrnl.exe �ķ�����  
	KSYSTEM_SERVICE_TABLE   win32k;                         // win32k.sys �ķ�����(GDI32.dll/User32.dll ���ں�֧��)  
	KSYSTEM_SERVICE_TABLE   notUsed1;
	KSYSTEM_SERVICE_TABLE   notUsed2;
}KSERVICE_TABLE_DESCRIPTOR, *PKSERVICE_TABLE_DESCRIPTOR;

typedef VOID(*PORIGINALCOMD)();

// KeServiceDescriptorTable �� ntoskrnl.exe ��������ȫ�ֱ���
extern PKSERVICE_TABLE_DESCRIPTOR KeServiceDescriptorTable;

extern DWORD								FileSize;
extern PVOID								pFileBuffer;
extern DWORD                                OrignImage;
extern PVOID								pImageBuffer;
extern PVOID                                pNewImageBase;
extern PIMAGE_DOS_HEADER					pDosHeader;
extern PIMAGE_NT_HEADERS					pNTHeader;
extern PIMAGE_FILE_HEADER					pFileHeader;
extern PIMAGE_OPTIONAL_HEADER32				pOptionalHeader;
extern PIMAGE_SECTION_HEADER				pSectionHeader;
extern PIMAGE_BASE_RELOCATION				pReloactionDirectory;
extern PIMAGE_THUNK_DATA					pIATDirectory;

VOID PageProtectOn();

VOID PageProtectOff();

DWORD32 SSDTfilter(DWORD ServiceTableBase, DWORD FuncIndex, DWORD32 OrigFuncAddress);

DWORD Align(int x, DWORD Alignment);

DWORD RVA_TO_FOA(DWORD dwRva);

DWORD FOA_TO_RVA(DWORD dwFoa);

NTSTATUS LoadNtkrnlpa();

NTSTATUS FixRelocTable(DWORD OrignalImageBase);

NTSTATUS FixIATTable();

NTSTATUS CopyFileBufferToImageBuffer(_In_ LPVOID pFilebuffer_, _Out_ LPVOID* pImageBuffer_);

NTSTATUS GetNtkrnlpaOrinalImage(PDRIVER_OBJECT pDriver);

NTSTATUS SetNewSSDT(DWORD NewImageBase);

NTSTATUS HookKiFastCallEntry();

NTSTATUS ReloadKernel(PDRIVER_OBJECT pDriver);

NTSTATUS UnHookKiFastCallEntry();

#endif // !NTKRNLPARELOAD

