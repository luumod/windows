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
//	//���߳̽����������̲߳������
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
//	//�ȴ��̴߳��ڼ���̬
//	WaitForSingleObject(hTread, INFINITE);	//�ȴ����߳̽����ͽ���
//
//	//���߳̽�����ȫ���̶߳�����
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
	//���������߳�
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
				//SuspendThread(dstHandle);	//��ͣ�߳�
				//ResumeThread(dstHandle);	//�ָ��߳�
				CloseHandle(dstHandle);
			}
			printf("�߳�ID��%d\n", threadEntry32.th32ThreadID);
		} while (Thread32Next(hThread, &threadEntry32));
	}
	return 0;
}