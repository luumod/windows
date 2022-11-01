//#include <Windows.h>
//#include <iostream>
//
//
//DWORD WINAPI ThreadProc2(
//	LPVOID lpParameter
//)
//{
//	while (true)
//	{
//		printf("6666666\n");
//	}
//
//	return 0;
//}
//
//
//DWORD WINAPI ThreadProc1(
//	LPVOID lpParameter
//)
//{
//	HANDLE hTread = CreateThread(
//		NULL,
//		NULL,
//		ThreadProc2,
//		0,
//		0,
//		NULL
//	);
//	int i = 0;
//	//子线程结束，其他线程不会结束
//	while (i<10000)
//	{
//		printf("22222\n");
//		++i;
//	}
//
//	return 0;
//}
//
//int main()
//{
//	HANDLE hTread = CreateThread(
//		NULL,
//		NULL,
//		ThreadProc1,
//		0,
//		0,
//		NULL
//	);
//	//等待线程处于激发态
//	WaitForSingleObject(hTread, INFINITE);	//等待子线程结束就结束
//
//	//主线程结束，全部线程都结束
//	//Sleep(5000);
//	/*while (true)
//	{
//		printf("1\n");
//	}*/
//
//	return 0;
//}

#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>

int main()
{
	//遍历所有线程
	HANDLE hThread = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
	THREADENTRY32 threadEntry32{ sizeof(THREADENTRY32)};
	BOOL isSucess = Thread32First(hThread, &threadEntry32);
	if (isSucess)
	{
		do
		{
			if (threadEntry32.th32OwnerProcessID == 17500)
			{
				HANDLE dstHandle = OpenThread(THREAD_ALL_ACCESS, NULL, threadEntry32.th32ThreadID);
				//SuspendThread(dstHandle);	//暂停线程
				//ResumeThread(dstHandle);	//恢复线程
				CloseHandle(dstHandle);
			}
			printf("线程ID：%d\n", threadEntry32.th32ThreadID);
		} while (Thread32Next(hThread, &threadEntry32));
	}
	return 0;
}