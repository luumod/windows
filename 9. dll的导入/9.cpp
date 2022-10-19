#include "9.h"
typedef int (*func)(int,int);
int main()
{
	//显示调用Dll
	HMODULE hmodule1=LoadLibraryW(L"9. 动态链接库.dll");
	func Fun=(func)GetProcAddress(hmodule1, "My_Export1");
	printf("%d", Fun(5, 10));
	FreeLibrary(hmodule1);
	return 0;
}