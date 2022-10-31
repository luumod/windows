#include <Windows.h>

int main()
{
	//往文件写入
#if 0
	HANDLE  hMailsolt = CreateFileW(L"\\\\.\\mailslot\\于良浩", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hMailsolt == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(NULL, L"打开邮槽失败", L"提示", MB_OK);
		return 0;
	}
	WCHAR buff[] = L"6666666666666666";
	DWORD size;
	WriteFile(hMailsolt, buff, 10, &size, NULL);
	CloseHandle(hMailsolt);
#else
	HANDLE Mailslot =  CreateFileW(L"//./mailslot/dst",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (Mailslot == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(NULL, L"打开邮槽失败", L"提示", MB_OK);
		return 0;
	}
	WCHAR lpBuff[] = L"我发送消息了";
	DWORD CurSize = 0;
	WriteFile(Mailslot, (LPCVOID)lpBuff, sizeof(lpBuff), &CurSize, NULL);
	CloseHandle(Mailslot);

#endif
	return 0;
}