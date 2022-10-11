#include <Windows.h>
#include <CommCtrl.h>

LRESULT CALLBACK Wndproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	//��ȡ�����ڵ�ʵ�����
	static HINSTANCE hInstance = GetModuleHandleW(NULL);
	switch (uMsg)
	{
	case WM_CREATE:
		//��ӿؼ�
		CreateWindowW(WC_BUTTON, L"��ť1", WS_CHILD | WS_VISIBLE, 50, 50, 100, 30, hwnd, (HMENU)0x100, hInstance,0);
		CreateWindowW(WC_BUTTON, L"��ť2", WS_CHILD | WS_VISIBLE, 50, 100, 100, 30, hwnd, (HMENU)0x101, hInstance, 0);
		CreateWindowW(WC_BUTTON, L"��ť2", WS_CHILD | WS_VISIBLE,450, 100, 100, 30, hwnd, (HMENU)0x101, hInstance, 0);

		CreateWindowW(WC_EDIT, L"�ı��༭��", WS_CHILD | WS_BORDER| WS_VISIBLE, 50, 200, 100, 50, hwnd, (HMENU)0x102, hInstance, 0);
		//MessageBoxW(hwnd, L"���ڴ�����", L"��ʾ", MB_OK);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(NULL);
		break;
	case WM_COMMAND:
	{
		WORD Controlid = LOWORD(wParam);	//WParam�������洢��ť�ı�ʶ��
		if (Controlid == 0x100)
		{
			MessageBoxW(hwnd, L"��ť1�������", L"��ʾ", MB_OK);
		}
		else if (Controlid==0x101)
		{
			MessageBoxW(hwnd, L"��ť2�������", L"��ʾ", MB_OK);

		}
		break;
	}
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hinstance,
	HINSTANCE hPreinstance,
	LPSTR lpCmdline,
	int nCmdShow
)
{
	WNDCLASSW myWindow{ 0 };
	myWindow.lpszClassName = L"ylh";
	myWindow.lpfnWndProc = Wndproc;

	RegisterClass(&myWindow);

	HWND window=CreateWindowW(
		myWindow.lpszClassName,
		L"666",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		NULL,
		hinstance,
		NULL
	);
	ShowWindow(window,SW_SHOWNORMAL);
	
	MSG msg{ 0 };
	while (GetMessageW(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}