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
	printf("%d\n",sizeof( chart));	//// ���ֽڣ�7 unicode��14

	printf("%s\n", charc);
	printf("%ws %ls\n", charw, charw);
	// unicode�ַ�����printf("%ws\n", chart);
	// ���ֽ��ַ����� printf("%s\n",chart);
	printf("%d\n", strlen(charc));
	printf("%d\n", wcslen(charw));
	printf("%d\n", _tcslen(chart));
	MessageBox(NULL, _T("����������"), _T("����"), MB_OK);
	MessageBoxW(NULL, L"����������", L"����", MB_OK);//WCHAR�汾
	MessageBoxA(NULL, "��������", "����", MB_OK);	  //WCHAR�汾

	return 0;
}