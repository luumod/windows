#include <Windows.h>
#include <iostream>

int main()
{
	HANDLE File1 = CreateFileW(L"test.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	OVERLAPPED overlapped1{ 0 };
	OVERLAPPED overlapped2{ 0 };

	overlapped1.hEvent = CreateEventW(NULL, FALSE, FALSE, L"FileEvent1");
	overlapped2.hEvent = CreateEventW(NULL, FALSE, FALSE, L"FileEvent2");

	WCHAR buff1[100]{ 0 };
	WCHAR buff2[100]{ 0 };

	ReadFile(File1, buff1, 100, NULL/*异步IO此处无意义*/, &overlapped1);
	ReadFile(File1, buff2, 100, NULL, &overlapped2);

	/*
	...
	*/

	//仍然有阻塞状态
	WaitForSingleObject(overlapped1.hEvent/*判断事件*/, -1);
	WaitForSingleObject(overlapped2.hEvent/*判断事件*/, -1);
	printf("buff1:%s\n", buff1);
	printf("buff2:%s\n", buff2);

	return 0;
}
