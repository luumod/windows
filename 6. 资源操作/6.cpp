#include <iostream>
#include <Windows.h>
#include <CommCtrl.h>
#include "resource1.h"
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

//枚举子窗口
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
			CreateWindowW(WC_BUTTON, L"改变图标和光标", WS_CHILD | WS_VISIBLE, 50, 420, 200, 50, hwnd, (HMENU)0x107, hInstance, NULL);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			PostQuitMessage(NULL);
			break;
		case WM_RBUTTONDOWN:
		{
			/*
			右键显示子菜单
			*/
			/*WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			p.x = x;
			p.y = y;*/

			POINT p{ 0 };
			//把获取的鼠标坐标转换为实际的窗口坐标
			//ClientToScreen(hwnd, &p);
			
			GetCursorPos(&p);			//直接获取窗口内的光标位置
			//获取主菜单
			HMENU menu1 = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));
			//从主菜单获取子菜单
			HMENU hSubMenu = GetSubMenu(menu1, 0);
			//左对齐显示子菜单
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
					//更改图标
					HICON icon1 = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));
					SetClassLongW(hwnd, GCL_HICON, (LONG)icon1);
					//更改光标
					HCURSOR cursor1 = LoadCursorW(hInstance, MAKEINTRESOURCEW(IDC_CURSOR1));
					SetClassLongW(hwnd, GCL_HCURSOR, (LONG)cursor1);
					//设置菜单
					HMENU menu1 = LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));
					SetMenu(hwnd, menu1);
					break;
				}
				case ID_40001:
				{
					/*
					点击子菜单的消息处理
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
	//1. 创建窗口类
	WNDCLASSW myClassWindow{ 0 };
	myClassWindow.lpszClassName = L"ylh";
	myClassWindow.lpfnWndProc = Wndproc;	//回调函数
	myClassWindow.hbrBackground = CreateSolidBrush(RGB(205, 156, 29));
	//改变图标
	myClassWindow.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_ICON1));	//自己创建的图标
	//myClassWindow.hIcon = LoadIcon(NULL, IDI_ERROR);		//系统自带图标
	myClassWindow.hCursor = LoadCursor(NULL, IDC_HELP);
	//添加菜单
	//myClassWindow.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);

	//2. 注册窗口 
	RegisterClassW(&myClassWindow);

	//3. 创建窗口
	//HMENU menu1=LoadMenuW(hInstance, MAKEINTRESOURCEW(IDR_MENU1));	//在此创建菜单
	HWND hWIndow = CreateWindowW(
		myClassWindow.lpszClassName,
		L"于良浩",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		NULL,
		NULL,	//菜单
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
