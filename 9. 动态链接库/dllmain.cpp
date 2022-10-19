// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

//声明方式导出
int My_Export1(int a, int b)
{
    return a + b;
}


//文件方式导出
char My_Export2(char a, char b)
{
    return 'a';
}

BOOL APIENTRY DllMain( HMODULE hModule, //HINSTANCE
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

