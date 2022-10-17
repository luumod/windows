#include <Windows.h>
#include <CommCtrl.h>
#include <windowsx.h>
#include "resource.h"

BOOL InsertColumnw(HWND hwnd,UINT col,LPWSTR ColumName,UINT cx)
{
	LVCOLUMNW lvcolumnw = { LVCF_FMT | LVCF_WIDTH | LVCF_TEXT };
	lvcolumnw.fmt = LVCFMT_CENTER;
	lvcolumnw.cx = cx;
	lvcolumnw.pszText = ColumName;
	SendDlgItemMessageW(hwnd, IDC_LIST2, LVM_INSERTCOLUMN, col, (LPARAM)&lvcolumnw);
	return TRUE;
}

BOOL InsertRow(HWND hwnd, UINT row)
{
	LVITEMW lvitmW = { LVIF_TEXT,row };
	lvitmW.pszText = (LPWSTR)L"";
	SendDlgItemMessageW(hwnd, IDC_LIST2, LVM_INSERTITEMW, 0, (LONG)&lvitmW);
	return TRUE;
}

BOOL SetListItemText(HWND hwnd, int row, int col, LPWSTR ColumName)
{
	LVITEMW lvitmW = { LVIF_TEXT,row,col};
	lvitmW.pszText = ColumName;
	SendDlgItemMessageW(hwnd, IDC_LIST2, LVM_SETITEMTEXT, row, (LONG)&lvitmW);
	return TRUE;
}

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
		ListView_SetExtendedListViewStyle(GetDlgItem(hwnd, IDC_LIST2), LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		InsertColumnw(hwnd, 0, (LPWSTR)L"", 0);
		InsertColumnw(hwnd, 1, (LPWSTR)L"设备", 80);
		InsertColumnw(hwnd, 2, (LPWSTR)L"用户名", 100);
		InsertColumnw(hwnd, 3, (LPWSTR)L"CPU", 40);
		InsertColumnw(hwnd, 4, (LPWSTR)L"内存", 100);
		InsertColumnw(hwnd, 5, (LPWSTR)L"显存", 160);
		InsertRow(hwnd, 0);
		SetListItemText(hwnd, 0, 1, (LPWSTR)L"360安全卫士");
		SetListItemText(hwnd, 0, 2, (LPWSTR)L"3604524554");
		SetListItemText(hwnd, 0, 3, (LPWSTR)L"36024248");
		SetListItemText(hwnd, 0, 4, (LPWSTR)L"360acfac");
		SetListItemText(hwnd, 0, 5, (LPWSTR)L"asdawad");

		break;
	}
	case WM_NOTIFY:
	{
		NMHDR* pnmhdr = (NMHDR*)lParam;
		//通用控件的消息捕获
		//判断消息的来源
		//如果消息来源是list控件，那么我们的lParam指向的是一个完整的结构体指针
		NMLISTVIEW* lNmlistView = (NMLISTVIEW*)lParam;
		if (wParam == IDC_LIST2 && pnmhdr->code == (UINT)NM_CLICK && lNmlistView->iItem != -1/*不能指向空行*/)
		{
			WCHAR Dst_wchar[100]{ 0 };
			LVITEM plvitem = { 0 };
			plvitem.iSubItem = lNmlistView->iSubItem;
			plvitem.pszText = Dst_wchar;	//接收缓冲区文本
			plvitem.cchTextMax = 100;		//最大接受字符数量
			SendDlgItemMessageW(hwnd, wParam, LVM_GETITEMTEXT, lNmlistView->iItem, (LPARAM)&plvitem);
			MessageBoxW(hwnd, plvitem.pszText, L"提示", MB_OK);
		}
		else if (wParam == IDC_LIST2 && pnmhdr->code == (UINT)NM_RCLICK)
		{
			/*
			右键弹出子菜单
			*/
			POINT pos;
			GetCursorPos(&pos);
			HMENU menu1 = LoadMenuW(GetModuleHandleW(NULL), MAKEINTRESOURCE(IDR_MENU1));
			HMENU SubMenu1 = GetSubMenu(menu1, 0);
			TrackPopupMenu(SubMenu1, TPM_LEFTALIGN, pos.x, pos.y, NULL, hwnd, NULL);
		}
		break;
	}
	case WM_CLOSE:
	{
		EndDialog(hwnd, NULL);
		break;
	}
	case WM_HSCROLL:
	{
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