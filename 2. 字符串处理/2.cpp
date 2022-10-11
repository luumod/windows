#include <Windows.h>
#include <iostream>
#include <tchar.h>

int main()
{
	CHAR charc[] = "123456";
	WCHAR charw[] = L"123456";
	TCHAR chart[] = _T("123456");	
	
	printf("%d\n",sizeof( charc));
	printf("%d\n",sizeof( charw));
	printf("%d\n",sizeof( chart));	//// 多字节：7 unicode：14

	printf("%s\n", charc);
	printf("%ws %ls\n", charw, charw);
	// unicode字符集：printf("%ws\n", chart);
	// 多字节字符集： printf("%s\n",chart);
	printf("%d\n", strlen(charc));
	printf("%d\n", wcslen(charw));
	printf("%d\n", _tcslen(chart));
	MessageBox(NULL, _T("请输入文字"), _T("标题"), MB_OK);
	MessageBoxW(NULL, L"请输入文字", L"标题", MB_OK);//WCHAR版本
	MessageBoxA(NULL, "请输文字", "标题", MB_OK);	  //WCHAR版本

	return 0;
}