#include <Windows.h>
#include <iostream>
int main()
{
	//打开一个文件
	HANDLE file1 = CreateFile(
		L"test.txt",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL
	);
	//OVERLAPPED结构体专门用来存储异步IO的内容
	OVERLAPPED overlapped{ 0 };
	CHAR buff[0x100]{ 0 };
	//读取的字节要设置为NULL
	ReadFile(file1,
		buff,
		0x100,
		NULL,
		&overlapped
	);
	/*
	........在此处可以添加其他代码..........
	*/
	//等待file1是否已经读取完，是否是有信号状态（表示线程已经结束，即读取完毕）
	WaitForSingleObject(file1, -1);	
	DWORD CurSize = 0;
	//读取是否成功
	if (GetOverlappedResult(file1, &overlapped, &CurSize, TRUE))//False：不会等待，True：一直等待
	{
		printf("文件内容: %s\n", buff);
		printf("实际读写数量: %d\n", CurSize);
	}
	CloseHandle(file1);
	return 0;
}