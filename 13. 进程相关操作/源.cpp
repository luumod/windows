#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int main1()
{
	setlocale(LC_ALL, "chs");		//支持中文
	//打开一个进程，获取进程句柄
	HANDLE hProcress=OpenProcess(PROCESS_ALL_ACCESS, FALSE, 59300);
	//结束进程
	TerminateProcess(hProcress, 0);

	/*
	遍历进程
	*/
	//第二个参数只有在遍历堆或者模块的时候需要指定进程的ID
#if 0
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32W ProcessEntry32W{ sizeof(PROCESSENTRY32W)};
	BOOL bSuccess = Process32FirstW(hSnapshot, &ProcessEntry32W);
	if (bSuccess)
	{
		do
		{
			printf("进程ID: %d，进程名称: %ls\n", ProcessEntry32W.th32ProcessID, ProcessEntry32W.szExeFile);
		} while (Process32NextW(hSnapshot, &ProcessEntry32W));
	}
#else
	/*
	遍历模块
	*/
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 7524);
	MODULEENTRY32W moduleEntry32W{ sizeof(MODULEENTRY32W) };
	BOOL Getmodule32 = Module32FirstW(hSnapshot, &moduleEntry32W);
	if (Getmodule32)
	{
		do
		{
			printf("模块ID: %d，模块名称: %ls\n", moduleEntry32W.th32ModuleID, moduleEntry32W.szExePath);
		} while (Module32NextW(hSnapshot, &moduleEntry32W));
	}
#endif
	return 0;
}


int main()
{
	/*
	遍历当前计算机所有线程
	*/
	setlocale(LC_ALL, "chs");
	HANDLE qqHandle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	THREADENTRY32 threadEntry32{ sizeof(THREADENTRY32) };
	BOOL IsSuccess =  Thread32First(qqHandle, &threadEntry32);
	UINT count = 0;
	if (IsSuccess)
	{
		do
		{
			if (threadEntry32.th32OwnerProcessID == 33864)
			{
				printf("线程ID：%d\n", threadEntry32.th32ThreadID);
				count++;
			}
		} while (Thread32Next(qqHandle, &threadEntry32));
	}
	printf("QQ所拥有的线程数:%d\n", count);
	CloseHandle(qqHandle);
	return 0;
}