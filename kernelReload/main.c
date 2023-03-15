/*
	�ȿ�:����ֱ���޸��ض�λ��Ϊ���ں�ƫ�ƣ��ض�λ��Ҫ����Ϊ���ں�ƫ�ƣ��ٰ�SSDT���溯����ַ����Ϊ���ں˵�
	ԭ��:����ֻ�����ں˵ĺ�����ȫ�ֱ������������ں˵� 
*/

#include <ntddk.h>
#include <ntstatus.h>
#include "ntkrnlpaReload.h"


VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver); // �����п���, ���߱������Ѿ�ʹ���˱������ؾ���
	UnHookKiFastCallEntry();

	DbgPrint("DriverUnload...\n");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING reg_path)
{
	DbgPrint("Driver is installed...\n");
	NTSTATUS status = STATUS_SUCCESS;
	pDriver->DriverUnload = DriverUnload;
	
	status = ReloadKernel(pDriver);
	if (!NT_SUCCESS(status))
	{
		DbgPrint("----- ReloadKernel Falied -----\n");
	}

	return STATUS_SUCCESS;
}