#include <Windows.h>
#include <iostream>

LONG num;
//critical_selction
CRITICAL_SECTION CriticalSelect{ 0 };
DWORD WINAPI ThreadProc1(
	LPVOID lpParameter
)
{
	for (int i = 0; i < 100000; ++i)
	{
		// 原子操作
		//InterlockedIncrement(&num);

		//到临界区执行
		EnterCriticalSection(&CriticalSelect);
		num++;  
		LeaveCriticalSection(&CriticalSelect);
	}
	return 1;
}

DWORD WINAPI ThreadProc2(
	LPVOID lpParameter
)
{
	for (int i = 0; i < 100000; ++i)
	{
		//到临界区执行
		EnterCriticalSection(&CriticalSelect);
		num++;
		LeaveCriticalSection(&CriticalSelect);
	}
	return 1;
}

int main()
{
	//创建临界区
	InitializeCriticalSection(&CriticalSelect);
	HANDLE Handle1=CreateThread(NULL, NULL, ThreadProc1, NULL, NULL, NULL);
	HANDLE Handle2=CreateThread(NULL, NULL, ThreadProc2, NULL, NULL, NULL);
	WaitForSingleObject(Handle1, -1);
	WaitForSingleObject(Handle2, -1);
	printf("num: %ld\n", num);
	CloseHandle(Handle1);
	CloseHandle(Handle2);
	DeleteCriticalSection(&CriticalSelect);
	return 0;
}