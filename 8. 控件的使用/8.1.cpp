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
		//��ȡ�ؼ��ľ��
		HWND hwndCheck1 = GetDlgItem(hwnd, IDC_CHECK1);
		//��������ڷ�����Ϣ
    	
		// ��ʽһ��
		//SendMessageW(hwndCheck1, BM_SETCHECK, BST_CHECKED, NULL);

		//��ʽ����
		//����ѡ��״̬
		SendDlgItemMessageW(hwnd, IDC_CHECK1, BM_SETCHECK, BST_CHECKED, NULL);

		//��ʽ����
		//Button_SetCheck(hwndCheck1, BST_CHECKED);
		break;
	}
	case WM_COMMAND:
	{
		// ��ȡ�ؼ��ı�ʶ��
		WORD Controlid = LOWORD(wParam);	
		switch (Controlid)
		{
		case IDOK:		//��ȡ��ѡ����Ϣ
		{
			WCHAR Dst_wchar[100]{ 0 };
			for (UINT i = IDC_CHECK1; i <= IDC_CHECK3; ++i)
			{
				//��ȡѡ��״̬
				UINT Checked = SendDlgItemMessageW(hwnd, i, BM_GETCHECK, NULL, NULL);
				if (Checked == BST_CHECKED)
				{	//��ťΪѡ��״̬
					GetDlgItemTextW(hwnd, i, Dst_wchar, 100);
					MessageBoxW(hwnd, Dst_wchar, L"��ʾ", MB_OK);
				}
			}
			break;
		}
		case IDCANCEL:	//��ȡ��ѡ����Ϣ
		{
			WCHAR Dst_wchar[100]{ 0 };
			for (UINT i = IDC_RADIO1; i <= IDC_RADIO3; ++i)
			{
				//��ȡѡ��״̬
				UINT Checked = SendDlgItemMessageW(hwnd, i, BM_GETCHECK, NULL, NULL);
				if (Checked == BST_CHECKED)
				{	//��ťΪѡ��״̬
					GetDlgItemTextW(hwnd, i, Dst_wchar, 100);
					MessageBoxW(hwnd, Dst_wchar, L"��ʾ", MB_OK);
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
	//������ģ̬�Ի���
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