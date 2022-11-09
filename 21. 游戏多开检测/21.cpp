#include <Windows.h>

int main()
{
	HANDLE Semap;
	Semap = OpenSemaphoreW(NULL, FALSE, L"ylh");
	if (!Semap)
	{
		Semap = CreateSemaphoreW(NULL, 0, 3, L"ylh");
	}
	BOOL IsSuccess = ReleaseSemaphore(Semap, 1, NULL);
	if (!IsSuccess)
	{
		MessageBoxW(NULL, L"打开数量不能超过三个!", L"警告", MB_OK);
		return 0;
	}
	system("pause");
	CloseHandle(Semap);
	return 0;
}

