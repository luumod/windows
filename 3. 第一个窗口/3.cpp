#include <Windows.h>

//�û��Զ�����Ϣ
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
		MessageBoxW(hwnd, L"���ڴ�����", L"��ʾ", MB_OK);
		break;
	case WM_CLOSE:
		MessageBoxW(hwnd, L"���ڹر���", L"��ʾ", MB_OK);
		DestroyWindow(hwnd);
		PostQuitMessage(NULL);
		break;
	case WM_MOUSEMOVE:
	{
		WORD x = LOWORD(lParam);
		WORD y = HIWORD(lParam);
		print(L"����ƶ���! x=%d,y=%d\n", x, y);
		break;
	}
	case WM_LBUTTONDOWN:
		print(L"����������\n");
		SendMessageW(hwnd, WM_USERMSG, NULL, NULL);
		break;
	case WM_USERMSG:
		print(L"�Զ�������\n");
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
	//1. ����һ��������
	WNDCLASSW myclass{ 0 };
	myclass.lpszClassName = L"������";
	myclass.lpfnWndProc = WindowProc;		//����һ������ָ�룬���ܴ��ڻص�����
	//2. ע�ᴰ����
	RegisterClassW(&myclass);
	//3. ��������
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
	//4. ��ʾ����
	ShowWindow(hWindow, SW_SHOWNORMAL);
	UpdateWindow(hWindow);
	//5. ��ȡ��Ϣ
	MSG msg{ 0 };
	while (GetMessageW(&msg, NULL, NULL, NULL))
	{	//��ȡ������Ϣ

		//�ַ���Ϣ����Ϣ������
		DispatchMessageW(&msg);
	}
	return 0;
}




