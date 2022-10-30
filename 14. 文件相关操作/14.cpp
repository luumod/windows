#include <windows.h>
#include <iostream>

BOOL myWriteFileFunc()
{
	//4. 创建或打开文件
	HANDLE hFile = CreateFile(
		L"F:/新建/123.txt", 
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL,
		OPEN_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	DWORD size; 
	//5. 往文件写入内容
	/*WriteFile(hFile, L"Hello World", sizeof(L"Hello World"), &size, NULL);*/
	WCHAR str[] = L"Hello World";
	DWORD CurSize = 0;
	WriteFile(hFile,
		str,
		sizeof(str),
		&CurSize,
		NULL);
	CloseHandle(hFile);
	return TRUE;
}

#if 1
int main()
{
	setlocale(LC_ALL, "chs");
	//1. 删除文件
	//DeleteFileW(L"F:/1.txt");
	//2. 复制一个文件
	//CopyFile(L"F:/123.txt", L"F:/新建/dst.txt",FALSE);
	//3. 移动文件(剪切)
	//MoveFile(L"F:/123.txt", L"F:/新建/剪切.txt");
	
	// ...
	WIN32_FIND_DATAW FindData{ 0 };
	HANDLE findHandle = FindFirstFileW(L"F:/新建/*", &FindData);
	FILETIME ReturnFileTime{ 0 };
	SYSTEMTIME systemTime{ 0 };
	//转换成我们认识的时间
	FileTimeToLocalFileTime(&FindData.ftCreationTime, &ReturnFileTime);
	FileTimeToSystemTime(&ReturnFileTime, &systemTime);
	printf("时间: %d %d %d -- %d %d %d\n", systemTime.wYear, systemTime.wMonth, systemTime.wDay,
		systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
	if (findHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			printf("%ls", FindData.cFileName);
			if (FindData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
			{	
				printf("是否隐藏：是\n");
			}
			else
			{
				printf("是否隐藏：否\n");
			}
		} while (FindNextFileW(findHandle, &FindData));
	}
	FindClose(findHandle);
	return 0;
}
#else
int main()
{
	setlocale(LC_ALL, "chs");
	WIN32_FIND_DATA win32_find_data{ 0 };
	HANDLE FileHandle =  FindFirstFileW(L"F:/新建/*", &win32_find_data);
	if (FileHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			printf("文件名:%ls ", win32_find_data.cFileName);
			if (win32_find_data.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
			{
				printf("是否隐藏（是）\n");
			}
			else
			{
				printf("是否隐藏（否）\n");
			}
		} while (FindNextFileW(FileHandle, &win32_find_data));
	}
	myWriteFileFunc();
	FindClose(FileHandle);
	return 0;
}

#endif
