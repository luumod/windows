#include <Windows.h>
#include <CommCtrl.h>
#include <windowsx.h>
#include "resource.h"

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
		//获取控件的句柄
		HWND hwndCheck1 = GetDlgItem(hwnd, IDC_CHECK1);
		//往句柄窗口发送消息
    	
		// 方式一：
		//SendMessageW(hwndCheck1, BM_SETCHECK, BST_CHECKED, NULL);

		//方式二：
		//设置选中状态
		SendDlgItemMessageW(hwnd, IDC_CHECK1, BM_SETCHECK, BST_CHECKED, NULL);

		//方式三：
		//Button_SetCheck(hwndCheck1, BST_CHECKED);
		break;
	}
	case WM_COMMAND:
	{
		// 获取控件的标识符
		WORD Controlid = LOWORD(wParam);	
		switch (Controlid)
		{
		case IDOK:		//获取多选框信息
		{
			WCHAR Dst_wchar[100]{ 0 };
			for (UINT i = IDC_CHECK1; i <= IDC_CHECK3; ++i)
			{
				//获取选中状态
				UINT Checked = SendDlgItemMessageW(hwnd, i, BM_GETCHECK, NULL, NULL);
				if (Checked == BST_CHECKED)
				{	//按钮为选中状态
					GetDlgItemTextW(hwnd, i, Dst_wchar, 100);
					MessageBoxW(hwnd, Dst_wchar, L"提示", MB_OK);
				}
			}
			break;
		}
		case IDCANCEL:	//获取单选框信息
		{
			WCHAR Dst_wchar[100]{ 0 };
			for (UINT i = IDC_RADIO1; i <= IDC_RADIO3; ++i)
			{
				//获取选中状态
				UINT Checked = SendDlgItemMessageW(hwnd, i, BM_GETCHECK, NULL, NULL);
				if (Checked == BST_CHECKED)
				{	//按钮为选中状态
					GetDlgItemTextW(hwnd, i, Dst_wchar, 100);
					MessageBoxW(hwnd, Dst_wchar, L"提示", MB_OK);
				}
			}
			break;
		}
		}
		
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		PostQuitMessage(NULL);
		break;
	}
	default:
	{

		return FALSE;
	}
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
	//创建非模态对话框
	HWND hwnd = CreateDialogW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);

	ShowWindow(hwnd, SW_SHOWNORMAL);

	MSG msg{ 0 };
	while (GetMessageW(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}