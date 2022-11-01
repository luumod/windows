#include <Windows.h>
#include <iostream>
#if 1
DWORD WINAPI ThreadProc(
	LPVOID lpParameter
)
{
	FILETIME CreationTime{ 0 };
	FILETIME ExitTime{ 0 };
	FILETIME KerneTime{ 0 };
	FILETIME UserTime{ 0 };
	FILETIME LocalTime{ 0 };
	SYSTEMTIME sysTime{ 0 };
	GetThreadTimes(lpParameter, &CreationTime, &ExitTime, &KerneTime, &UserTime);
	FileTimeToLocalFileTime(&CreationTime, &LocalTime);
	FileTimeToSystemTime(&LocalTime, &sysTime);
	return 0;
}

int main()
{
	//获取主程序线程
	HANDLE MyWindowThread = GetCurrentThread();

	FILETIME CreationTime{ 0 };
	FILETIME ExitTime{ 0 };
	FILETIME KerneTime{ 0 };
	FILETIME UserTime{ 0 };
	FILETIME LocalTime{ 0 };
	SYSTEMTIME sysTime{ 0 };
	SYSTEMTIME sysTimeKerneTime{ 0 };
	GetThreadTimes(MyWindowThread, &CreationTime, &ExitTime, &KerneTime, &UserTime);
	//转换时间为本地文件时间
	FileTimeToLocalFileTime(&CreationTime,&LocalTime);
	//转换时间为系统时间
	FileTimeToSystemTime(&LocalTime, &sysTime);

	/*
	获取线程的拷贝，是同一个线程
	*/
	/*HANDLE TargetHandle;
	DuplicateHandle(
		GetCurrentProcess(),
		MyWindowThread,
		GetCurrentProcess(),
		&TargetHandle,
		NULL,
		NULL,
		DUPLICATE_SAME_ACCESS
	);*/
	//创建子线程
	HANDLE hThread=CreateThread(NULL, NULL, ThreadProc, MyWindowThread/*TargetHandle*/ , NULL, NULL);
	WaitForSingleObject(hThread, -1);

	
	return 0;
}
#else

int g_number = 0;
DWORD WINAPI ThreadProc(
	LPVOID lpParameter
)
{
	for (int i = 0; i < 100; i++)
	{
		g_number++;
	}
	printf("g_number: %d\n", g_number);
	return 0;
}

int main()
{
	int i = 0;
	HANDLE FirstThread =  CreateThread(NULL,
		NULL,
		ThreadProc,
		NULL,
		CREATE_SUSPENDED,
		NULL
	);
	ResumeThread(FirstThread);
	WaitForSingleObject(FirstThread, -1);
	return  0;
}

#endif