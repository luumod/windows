#include <Windows.h>
#include <iostream>

LONG num;
HANDLE hEvent1;
HANDLE hEvent2;
HANDLE hEvent3;
CRITICAL_SECTION critical_selction{ 0 };
HANDLE Semphore;

DWORD WINAPI ThreadProc1(
	LPVOID lpParameter
)
{
	/*if (WAIT_OBJECT_0 == WaitForSingleObject(hEvent3, -1))
	{
		printf("线程一执行了\n");
		SetEvent(hEvent1
		);
	}*/
	if (WAIT_OBJECT_0 == WaitForSingleObject(Semphore, -1))
	{
		for (int i = 0; i < 10000; i++)
		{
			num++;
		}
		if (!ReleaseSemaphore(Semphore, 1, NULL))
		{
			return 0;
		}
	}
	return 1;
}

DWORD WINAPI ThreadProc2(
	LPVOID lpParameter
)
{
	/*if (WAIT_OBJECT_0 == WaitForSingleObject(hEvent2, -1))
	{
		printf("线程二执行了\n");
		SetEvent(hEvent3);
	}*/
	if (WAIT_OBJECT_0 == WaitForSingleObject(Semphore, -1))
	{
		for (int i = 0; i < 10000; i++)
		{
			num++;
		}
		if (!ReleaseSemaphore(Semphore, 1, NULL))
		{
			return 0;
		}
	}
	return 1;
}

//DWORD WINAPI ThreadProc3(
//	LPVOID lpParameter
//)
//{
//	if (WAIT_OBJECT_0 == WaitForSingleObject(hEvent1, -1))
//	{
//		printf("线程三执行了\n");
//		SetEvent(hEvent2);
//	}
//	return 1;
//}
int main()
{
	////初始无信号状态
	//hEvent1 = CreateEventW(NULL, FALSE, TRUE, NULL);
	//hEvent2 = CreateEventW(NULL, FALSE, FALSE, NULL);
	//hEvent3 = CreateEventW(NULL, FALSE, FALSE, NULL);

	Semphore =  CreateSemaphore(NULL, 1, 1, NULL);

	HANDLE Handle[2]{NULL};

	Handle[0] = CreateThread(NULL, NULL, ThreadProc1, NULL, NULL, NULL);
	Handle[1] = CreateThread(NULL, NULL, ThreadProc2, NULL, NULL, NULL);
	/*Handle[2] = CreateThread(NULL, NULL, ThreadProc3, NULL, NULL, NULL);*/

	/*WaitForSingleObject(Handle1, -1);
	WaitForSingleObject(Handle2,-1);*/
	//WaitForSingleObject(Handle,-1);
	WaitForMultipleObjects(1, Handle, TRUE, -1);

	printf("num: %ld\n", num);
	//CloseHandle(Handle);
	CloseHandle(hEvent1);
	CloseHandle(hEvent2);
	CloseHandle(hEvent3);
	return 0;
}


//
//#include <Windows.h>
//#include <iostream>
//
//HANDLE FirstThread = NULL;
//HANDLE SecondThread = NULL;
//HANDLE ThirdHandle = NULL;
//CRITICAL_SECTION critical_selction{ 0 };
//LONG g_num1 = 0;
//HANDLE MutexHandle = NULL;
//
//HANDLE Event1 = NULL;
//HANDLE Event2 = NULL;
//HANDLE Event3 = NULL;
//
//
//DWORD WINAPI ThreadProc1(
//	LPVOID lpParameter
//)
//{
//	//等待Event1 处于激发态的时候，获得线程执行权限
//	WaitForSingleObject(Event1, -1);
//	//上锁，Event1设置为非激发态
//	printf("线程一\n");
//	//锁住一，解锁二
//	//设置Event2为激发态，解锁下一个
//	SetEvent(Event3);
//	
//	return 0;
//}
//
//DWORD WINAPI ThreadProc2(
//	LPVOID lpParameter
//)
//{
//	WaitForSingleObject(Event2, -1);
//	printf("线程二\n");
//	//锁住二，解锁三
//	SetEvent(Event1);
//	return 0;
//}
//
//DWORD WINAPI ThreadProc3(
//	LPVOID lpParameter
//)
//{
//	WaitForSingleObject(Event3, -1);
//	printf("线程三\n");
//	//锁住三，解锁一
//	//执行完一次循环后，重新设置Event1为激发态，解锁，开始下一次循环。
//	SetEvent(Event2);
//
//	return 0;
//}
//
//int main()
//{
//	Event1 = CreateEvent(NULL, FALSE, FALSE, NULL);
//	Event2 = CreateEvent(NULL, FALSE, FALSE, NULL);
//	Event3 = CreateEvent(NULL, FALSE, FALSE, NULL);
//	SetEvent(Event3);
//	//一开始，Event1 处于激发态，2和3都处于非激发态（锁住）
//	//首先会调用 Event1
//	FirstThread =  CreateThread(NULL,
//		NULL,
//		ThreadProc1,
//		NULL,
//		NULL,
//		NULL
//	);
//	SecondThread =  CreateThread(NULL,
//		NULL,
//		ThreadProc2,
//		NULL,
//		NULL,
//		NULL
//	);
//	ThirdHandle = CreateThread(NULL,
//		NULL,
//		ThreadProc3,
//		NULL,
//		NULL,
//		NULL
//	);
//	/*WaitForSingleObject(Event1, -1);
//	WaitForSingleObject(Event2, -1);
//	WaitForSingleObject(Event3, -1);*/
//
//
//
//	CloseHandle(FirstThread);
//	CloseHandle(SecondThread);
//	CloseHandle(ThirdHandle);
//	return 0;
//}