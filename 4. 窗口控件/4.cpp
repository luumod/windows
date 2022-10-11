#include <Windows.h>
#include <CommCtrl.h>

LRESULT CALLBACK Wndproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	//获取主窗口的实例句柄
	static HINSTANCE hInstance = GetModuleHandleW(NULL);
	switch (uMsg)
	{
	case WM_CREATE:
		//添加控件
		CreateWindowW(WC_BUTTON, L"按钮1", WS_CHILD | WS_VISIBLE, 50, 50, 100, 30, hwnd, (HMENU)0x100, hInstance,0);
		CreateWindowW(WC_BUTTON, L"按钮2", WS_CHILD | WS_VISIBLE, 50, 100, 100, 30, hwnd, (HMENU)0x101, hInstance, 0);
		CreateWindowW(WC_BUTTON, L"按钮2", WS_CHILD | WS_VISIBLE,450, 100, 100, 30, hwnd, (HMENU)0x101, hInstance, 0);

		CreateWindowW(WC_EDIT, L"文本编辑框", WS_CHILD | WS_BORDER| WS_VISIBLE, 50, 200, 100, 50, hwnd, (HMENU)0x102, hInstance, 0);
		//MessageBoxW(hwnd, L"窗口创建了", L"提示", MB_OK);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(NULL);
		break;
	case WM_COMMAND:
	{
		WORD Controlid = LOWORD(wParam);	//WParam低两个存储按钮的标识符
		if (Controlid == 0x100)
		{
			MessageBoxW(hwnd, L"按钮1被点击了", L"提示", MB_OK);
		}
		else if (Controlid==0x101)
		{
			MessageBoxW(hwnd, L"按钮2被点击了", L"提示", MB_OK);

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