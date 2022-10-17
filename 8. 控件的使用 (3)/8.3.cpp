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
			SendDlgItemMessageW(hwnd, IDC_PROGRESS1, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
			SendDlgItemMessageW(hwnd, IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELPARAM(0, 100));
			SendDlgItemMessageW(hwnd, IDC_PROGRESS1, PBM_SETPOS, 50, 0);
			SendDlgItemMessageW(hwnd, IDC_SLIDER1, TBM_SETPOS, TRUE, 80);
			break;
		}
		case WM_CLOSE:
		{
			EndDialog(hwnd, NULL);
			break;
		}
		case WM_HSCROLL:
		{
			if (GetDlgItem(hwnd, IDC_SLIDER1) == (HWND)lParam)
			{
				int pos = SendDlgItemMessageW(hwnd,IDC_SLIDER1, TBM_GETPOS, 0, 0);
				SendDlgItemMessageW(hwnd, IDC_PROGRESS1, PBM_SETPOS, pos, 0);
			}
			break;
		}
		default:
			return FALSE;
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
	DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);
	return 0;
}