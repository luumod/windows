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
	HINSTANCE hInstance = GetModuleHandleW(NULL);	//��ȡ��ǰ�����ʵ�����
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			/*
			����ͼƬ��Դ
			*/
			HBITMAP bitmap1 = LoadBitmapW(hInstance, MAKEINTRESOURCEW(IDB_BITMAP1));
			SendDlgItemMessageW(hwnd, IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bitmap1);
			/*
			���ø�ѡ�������
			*/
			ComboBox_AddString(GetDlgItem(hwnd, IDC_COMBO1), L"��һ��ͼƬ");
			ComboBox_AddString(GetDlgItem(hwnd, IDC_COMBO1), L"�ڶ���ͼƬ");
			//Ĭ��ѡ���1��
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
			WORD controlid = LOWORD(wParam);	//�ؼ���ʶ��
			WORD msgType = HIWORD(wParam);		//�ؼ�֪ͨ��
			switch (controlid)
			{
				case IDC_COMBO1:
				{
					if (msgType == CBN_SELCHANGE)
					{
						//1. ��ȡ�������ѡ��index
						int index = ComboBox_GetCurSel(GetDlgItem(hwnd, IDC_COMBO1));
						//2. �ı�ͼƬ������Load����ͼƬ��Ȼ����ʹ��Send������̬ͼƬ�������ͼƬ��Ϣ
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
	//ģ̬�Ի���
	DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);
	return 0;
}