#include <iostream>
#include <Windows.h>
#include <CommCtrl.h>
#include "resource1.h"
//��ʽ���������
void println(LPCWSTR format, ...)
{
	WCHAR wchar_buff[100]{ 0 };
	va_list args;	//�����б�����args������
	va_start(args, format);	//��������б�
	wvsprintfW(wchar_buff, format, args);		//��ʽ�������wchar_buff
	va_end(args);	//������
	OutputDebugStringW(wchar_buff);		//���ݷ��͵�Debug���е���
}

//ö���Ӵ���
BOOL CALLBACK EnumChildProc(
	HWND hwnd,
	LPARAM lparam
)
{
	WCHAR wchar_buff[100]{ 0 };
	GetWindowText(hwnd, wchar_buff, 100);
	println(L"�Ӵ���: %s\n", wchar_buff);
	return TRUE;
}

LRESULT CALLBACK Wndproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	static HINSTANCE hInstance = GetModuleHandleW(NULL);	//��ȡ��ǰ���ھ��
	switch (uMsg)
	{
		case WM_CREATE:
			CreateWindowW(WC_BUTTON, L"�ı�ͼ��͹��", WS_CHILD | WS_VISIBLE, 50, 420, 200, 50, hwnd, (HMENU)0x107, hInstance, NULL);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			PostQuitMessage(NULL);
			break;
		case WM_RBUTTONDOWN:
		{
			/*
			�Ҽ���ʾ�Ӳ˵�
			*/
			/*WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			p.x = x;
			p.y = y;*/

			POINT p{ 0 };
			//�ѻ�ȡ���������ת��Ϊʵ�ʵĴ�������
			//ClientToScreen(hwnd, &p);
			
			GetCursorPos(&p);			//ֱ�ӻ�ȡ�����ڵĹ��λ��
			//��ȡ���˵�
			HMENU menu1 = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));
			//�����˵���ȡ�Ӳ˵�
			HMENU hSubMenu = GetSubMenu(menu1, 0);
			//�������ʾ�Ӳ˵�
			TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, p.x, p.y, 0, hwnd, 0);
			break;
		}
		case WM_COMMAND:
		{
			WORD Controlid = LOWORD(wParam);
			switch (Controlid)
			{
				case 0x107:
				{
					//����ͼ��
					HICON icon1 = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
					SetClassLongW(hwnd, GCL_HICON, (LONG)icon1);
					//���Ĺ��
					HCURSOR cursor1 = LoadCursorW(hInstance, MAKEINTRESOURCEW(IDC_CURSOR1));
					SetClassLongW(hwnd, GCL_HCURSOR, (LONG)cursor1);
					//���ò˵�
					HMENU menu1 = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));
					SetMenu(hwnd, menu1);
					break;
				}
				case ID_40001:
				{
					/*
					����Ӳ˵�����Ϣ����
					*/
					MessageBox(0, 0, 0, 0);
					break;
				}
			}
			break;
		}
		
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	//1. ����������
	WNDCLASSW myClassWindow{ 0 };
	myClassWindow.lpszClassName = L"ylh";
	myClassWindow.lpfnWndProc = Wndproc;	//�ص�����
	myClassWindow.hbrBackground = CreateSolidBrush(RGB(205, 156, 29));
	//�ı�ͼ��
	myClassWindow.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));	//�Լ�������ͼ��
	//myClassWindow.hIcon = LoadIcon(NULL, IDI_ERROR);		//ϵͳ�Դ�ͼ��
	myClassWindow.hCursor = LoadCursor(NULL, IDC_HELP);
	//��Ӳ˵�
	//myClassWindow.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);

	//2. ע�ᴰ�� 
	RegisterClassW(&myClassWindow);

	//3. ��������
	//HMENU menu1=LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));	//�ڴ˴����˵�
	HWND hWIndow = CreateWindowW(
		myClassWindow.lpszClassName,
		L"������",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		NULL,	//�˵�
		hInstance,
		NULL
	);

	//4. ��ʾ����
	ShowWindow(hWIndow, SW_SHOWNORMAL);

	//5. ������Ϣ�¼�
	MSG msg{ 0 };
	while (GetMessageW(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
