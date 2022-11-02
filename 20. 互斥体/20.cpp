#include <Windows.h>
#include <iostream>

LONG num;
HANDLE MainHandle;
DWORD WINAPI ThreadProc1(
	LPVOID lpParameter
)
{
	for (int i = 0; i < 100000; ++i)
	{
		WaitForSingleObject(MainHandle, -1);
		num++;
		ReleaseMutex(MainHandle);	//解锁
	}
	return 1;
}

DWORD WINAPI ThreadProc2(
	LPVOID lpParameter
)
{
	for (int i = 0; i < 100000; ++i)
	{
		WaitForSingleObject(MainHandle, -1);
		num++;
		ReleaseMutex(MainHandle);
	}
	return 1;
}

int main()
{
	HANDLE Handle1 = CreateThread(NULL, NULL, ThreadProc1, NULL, NULL, NULL);
	HANDLE Handle2 = CreateThread(NULL, NULL, ThreadProc2, NULL, NULL, NULL);
	//创建互斥体
	MainHandle = CreateMutexW(NULL, FALSE, L"我的互斥体");
	WaitForSingleObject(Handle1, -1);
	WaitForSingleObject(Handle2, -1);
	printf("num: %ld\n", num);
	CloseHandle(Handle1);
	CloseHandle(Handle2);
	return 0;
}