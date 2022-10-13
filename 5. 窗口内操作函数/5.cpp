#include <iostream>
#include <Windows.h>
#include <CommCtrl.h>

//格式化输出函数
void println(LPCWSTR format, ...)
{
	WCHAR wchar_buff[100]{ 0 };
	va_list args;	//参数列表拷贝到args变量中
	va_start(args, format);	//保存参数列表
	wvsprintfW(wchar_buff, format, args);		//格式化输出到wchar_buff
	va_end(args);	//清理工作
	OutputDebugStringW(wchar_buff);		//内容发送到Debug进行调试
}

//枚举子窗口的回调函数
BOOL CALLBACK EnumChildProc(
	HWND hwnd,
	LPARAM lparam
)
{
	WCHAR wchar_buff[100]{ 0 };
	GetWindowText(hwnd, wchar_buff, 100);
	println(L"子窗口: %s\n", wchar_buff);
	return TRUE;
}

LRESULT CALLBACK Wndproc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	static HINSTANCE hInstance = GetModuleHandleW(NULL);	//获取当前窗口句柄
	switch (uMsg)
	{
	case WM_CREATE:
		CreateWindowW(WC_BUTTON, L"移动按钮", WS_CHILD | WS_VISIBLE, 50, 20, 200, 50,hwnd, (HMENU)0x100, hInstance, NULL);
		CreateWindowW(WC_BUTTON, L"获取文本框内容", WS_CHILD | WS_VISIBLE, 50, 100, 200, 50, hwnd, (HMENU)0x101, hInstance, NULL);
		CreateWindowW(WC_BUTTON, L"设置文本框内容", WS_CHILD | WS_VISIBLE, 50, 160, 200, 50, hwnd, (HMENU)0x102, hInstance, NULL);
		CreateWindowW(WC_BUTTON, L"设置父窗口", WS_CHILD | WS_VISIBLE, 50, 220, 200, 50, hwnd, (HMENU)0x103, hInstance, NULL);
		CreateWindowW(WC_BUTTON, L"枚举所有窗口", WS_CHILD | WS_VISIBLE, 350, 300, 200, 50, hwnd, (HMENU)0x105, hInstance, NULL);
		CreateWindowW(WC_EDIT, L"文本编辑框", WS_CHILD | WS_BORDER | WS_VISIBLE, 50, 300, 200, 50, hwnd, (HMENU)0x104, hInstance, NULL);
		CreateWindowW(WC_EDIT, L"文本输入框", WS_CHILD | WS_BORDER | WS_VISIBLE, 50, 360, 200, 50, hwnd, (HMENU)0x106, hInstance, NULL);

		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		PostQuitMessage(NULL);
		break;
	case WM_COMMAND:
	{
		WORD Controlid = LOWORD(wParam);
		switch (Controlid)
		{
		case 0x100:
		{
			//随机获取坐标: 来一个区间范围
			RECT rect{ 0 };
			GetClientRect(hwnd, &rect);
			int x = rand() % (rect.right - 200);
			int y = rand() % (rect.bottom - 50);
			MoveWindow((HWND)lParam, x, y, 200, 50, TRUE);
			break;
		}
		case 0x101:
		{
			/*
			获取文本框的内容
			*/
			WCHAR str_dst[100]{ 0 };
			HWND hedit=GetDlgItem(hwnd,0x104);		//首先获取文本框窗口的句柄
			GetDlgItemTextW(hwnd, 0x104, str_dst, 100);
			//GetWindowTextW(hedit, str_dst, 100);	//根据得到的子窗口的句柄得到字符串并且放入一个字符数组中
			MessageBoxW(hwnd, str_dst, L"提示", MB_OK);	//读取文本框的内容
			break;
		}
		case 0x102:
		{
			/*
			根据读取的文本框的内容再复制到另一个文本框
			*/
			WCHAR wchar_buff[100]{ 0 };
			//获取文本框的句柄
			HWND handle=GetDlgItem(hwnd, 0x104);		//获取目标编辑框句柄
			GetWindowTextW(handle, wchar_buff,100);	//获取读入的内容
			SetDlgItemTextW(hwnd, 0x106, wchar_buff);

			//HWND dst_HWND = GetDlgItem(hwnd, 0x106);
			//SetWindowTextW(dst_HWND, wchar_buff);
			break;
		}
		case 0x103:
		{
			HWND handle=FindWindowW(NULL, L"无标题 - 记事本");
			SetParent((HWND)lParam, handle);	//原窗口句柄和新的父窗口句柄
			break;
		}
		case 0x105: 
		{
			EnumChildWindows(hwnd, EnumChildProc, 0);
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
	//1. 创建窗口类
	WNDCLASSW myClassWindow{ 0 };
	myClassWindow.lpszClassName = L"ylh";
	myClassWindow.lpfnWndProc = Wndproc;	//回调函数
	myClassWindow.hbrBackground = CreateSolidBrush(RGB(205, 156, 29));

	//2. 注册窗口 
	RegisterClassW(&myClassWindow);

	//3. 创建窗口
	HWND hWIndow = CreateWindowW(
		myClassWindow.lpszClassName,
		L"dasd",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//4. 显示窗口
	ShowWindow(hWIndow, SW_SHOWNORMAL);

	//5. 处理消息事件
	MSG msg{ 0 };
	while (GetMessageW(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}