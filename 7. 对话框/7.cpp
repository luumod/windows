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
//			MessageBoxW(hwnd, L"�����Ѵ���", L"Warning", MB_OK);
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
//	return TRUE;	//��Ϣ��û�д���
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
	//������ģ̬�Ի��򴰿�
	//HWND hwnd = CreateDialogW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);

	//����ģ̬�Ի���
	DialogBoxW(hInstance, MAKEINTRESOURCEW(IDD_DIALOG1), NULL, Dlgproc);

	////��ʾ����
	//ShowWindow(hwnd,SW_SHOWNORMAL);

	//MSG msg{ 0 };
	//while (GetMessage(&msg, NULL, NULL, NULL))
	//{
	//	TranslateMessage(&msg);	//ת����Ϣ
	//	DispatchMessageW(&msg);	//�ַ���Ϣ
	//}
	return 0;
}