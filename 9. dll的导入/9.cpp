#include "9.h"
typedef int (*func)(int,int);
int main()
{
	//��ʾ����Dll
	HMODULE hmodule1=LoadLibraryW(L"9. ��̬���ӿ�.dll");
	func Fun=(func)GetProcAddress(hmodule1, "My_Export1");
	printf("%d", Fun(5, 10));
	FreeLibrary(hmodule1);
	return 0;
}