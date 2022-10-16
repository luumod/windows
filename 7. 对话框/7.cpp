#include <Windows.h>
#include <CommCtrl.h>
#include "resource.h"

//INT_PTR CALLBACK Dlgproc(
//	HWND hwnd,
//	UINT uMsg,
//	WPARAM wParam,
//	LPARAM lParam
//)
//{
//	switch (uMsg)
//	{
//		case WM_INITDIALOG:
//		{
//			MessageBoxW(hwnd, L"窗口已创建", L"Warning", MB_OK);
//			break;
//		}
//		case WM_CLOSE:
//		{
//			DestroyWindow(hwnd);
//			PostQuitMessage(NULL);
//			//EndDialog(hwnd, NULL);
//			break;
//		}
//		default:
//		{
//			return FALSE;
//		}
//	}
//	return TRUE;	//消息有没有处理
//}
//
INT_PTR CALLBACK Dlgproc(	
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
		
			break;
		}
		case WM_CLOSE:
		{
			/*DestroyWindow(hwnd);
			PostQuitMessage(NULL);*/
			EndDialog(hwnd, NULL);
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
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	//创建非模态对话框窗口
	//HWND hwnd = CreateDialogW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);

	//创建模态对话框
	DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);

	////显示窗口
	//ShowWindow(hwnd,SW_SHOWNORMAL);

	//MSG msg{ 0 };
	//while (GetMessage(&msg, NULL, NULL, NULL))
	//{
	//	TranslateMessage(&msg);	//转换消息
	//	DispatchMessageW(&msg);	//分发消息
	//}
	return 0;
}