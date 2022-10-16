#include <Windows.h>
#include <CommCtrl.h>
#include "resource.h"
#include <windowsx.h>

INT_PTR CALLBACK Dlgproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	HINSTANCE hInstance = GetModuleHandleW(NULL);	//获取当前程序的实例句柄
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			/*
			设置图片资源
			*/
			HBITMAP bitmap1 = LoadBitmapW(hInstance, MAKEINTRESOURCEW(IDB_BITMAP1));
			SendDlgItemMessageW(hwnd, IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap1);
			/*
			设置复选框的内容
			*/
			ComboBox_AddString(GetDlgItem(hwnd, IDC_COMBO1), L"第一张图片");
			ComboBox_AddString(GetDlgItem(hwnd, IDC_COMBO1), L"第二张图片");
			//默认选择第1个
			ComboBox_SetCurSel(GetDlgItem(hwnd, IDC_COMBO1), 0);
			break;
		}
		case WM_CLOSE:
		{
			EndDialog(hwnd, NULL);
			break;
		}
		case WM_COMMAND:
		{
			WORD controlid = LOWORD(wParam);	//控件标识符
			WORD msgType = HIWORD(wParam);		//控件通知码
			switch (controlid)
			{
				case IDC_COMBO1:
				{
					if (msgType == CBN_SELCHANGE)
					{
						//1. 获取下拉框的选项index
						int index = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_COMBO1));
						//2. 改变图片，利用Load加载图片，然后再使用Send来往静态图片句柄发送图片信息
						HBITMAP bitmap1 = LoadBitmapW(hInstance, MAKEINTRESOURCEW(IDB_BITMAP1 + index));
						SendDlgItemMessageW(hwnd, IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, (LONG)bitmap1);
					}
					break;
				}
			}
		}
		default:
		{
			return FALSE;
		}
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
	//模态对话框
	DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);
	return 0;
}