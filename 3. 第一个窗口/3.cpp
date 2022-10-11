#include <Windows.h>

//用户自定义消息
const UINT WM_USERMSG = WM_USER + 1;

void print(LPCWSTR format,... )
{
	WCHAR wchar_buff[100]{ 0 };
	va_list arglist;
	va_start(arglist,format);
	wvsprintfW(wchar_buff, format, arglist);
	va_end(arglist);
	OutputDebugStringW(wchar_buff);
}

LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_CREATE:
		MessageBoxW(hwnd, L"窗口创建了", L"提示", MB_OK);
		break;
	case WM_CLOSE:
		MessageBoxW(hwnd, L"窗口关闭了", L"提示", MB_OK);
		DestroyWindow(hwnd);
		PostQuitMessage(NULL);
		break;
	case WM_MOUSEMOVE:
	{
		WORD x = LOWORD(lParam);
		WORD y = HIWORD(lParam);
		print(L"鼠标移动了! x=%d,y=%d\n", x, y);
		break;
	}
	case WM_LBUTTONDOWN:
		print(L"鼠标左键按下\n");
		SendMessageW(hwnd, WM_USERMSG, NULL, NULL);
		break;
	case WM_USERMSG:
		print(L"自定义类型\n");
		break;
	case WM_RBUTTONDOWN:
		SendMessageW((HWND)0x000208D2, WM_CLOSE, NULL, NULL);
		break;
	}
	return  DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	//1. 创建一个窗口类
	WNDCLASSW myclass{ 0 };
	myclass.lpszClassName = L"于良浩";
	myclass.lpfnWndProc = WindowProc;		//这是一个函数指针，接受窗口回调函数
	//2. 注册窗口类
	RegisterClassW(&myclass);
	//3. 创建窗口
	HWND hWindow = CreateWindowW(
		myclass.lpszClassName,
		L"ylh",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		NULL,
		hInstance,
		NULL);
	//4. 显示窗口
	ShowWindow(hWindow, SW_SHOWNORMAL);
	UpdateWindow(hWindow);
	//5. 获取消息
	MSG msg{ 0 };
	while (GetMessageW(&msg, NULL, NULL, NULL))
	{	//获取所有消息

		//分发消息给消息处理函数
		DispatchMessageW(&msg);
	}
	return 0;
}




