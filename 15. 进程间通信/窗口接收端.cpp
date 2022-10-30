#include <Windows.h>
#include "resource.h"

INT_PTR CALLBACK Dlgproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM uParam,
	LPARAM lParam
)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{		
			break;
		}
		case WM_COPYDATA:
		{
			PCOPYDATASTRUCT CopyData = (PCOPYDATASTRUCT)lParam;
			MessageBoxW(hwnd, (LPCWSTR)CopyData->lpData, L"接收消息", MB_OK);
			break;
		}
		case WM_CLOSE:
		{
			EndDialog(hwnd, 0);
			break;
		}
		default:
			return FALSE;
			break;
	}

	return TRUE;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPreInstance,
	LPSTR lpCmdLine,
	int nShowCmd
)
{
	DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);
	return 0;
}