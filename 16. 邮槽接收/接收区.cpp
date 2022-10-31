#include <windows.h>

int main()
{
#if 0
	HANDLE Mailsolt = CreateMailslotW(L"\\\\.\\mailslot\\于良浩", NULL, MAILSLOT_WAIT_FOREVER, NULL);
	if (Mailsolt == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(NULL, L"创建邮槽失败", L"提示", MB_OK);
	}
	WCHAR buff[100]{ 0 };
	DWORD size;
	ReadFile(Mailsolt, buff, 100, &size, NULL);
	MessageBoxW(NULL, buff, L"接收消息", MB_OK);
	CloseHandle(Mailsolt);
#else
	HANDLE MailslotHandle =  CreateMailslotW(L"//./mailslot/dst", NULL, MAILSLOT_WAIT_FOREVER, NULL);
	if (MailslotHandle == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(NULL, L"创建邮槽失败!", L"提示", MB_OK);
	}	
	WCHAR lpBuff[100]{ 0 };
	DWORD CurSize = 0;
	while (1)
	{
		if (ReadFile(MailslotHandle, (LPVOID)lpBuff, 100, &CurSize, NULL))
		{
			MessageBoxW(NULL, lpBuff, L"接收消息", MB_OK);
		}
		memset(lpBuff, 0, sizeof(lpBuff));
		CurSize = 0;
	} ;
	CloseHandle(MailslotHandle);
#endif
	return 0;
}