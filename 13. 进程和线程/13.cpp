#include <Windows.h>

int main()
{
	STARTUPINFOW sw{ 0 };
	PROCESS_INFORMATION pInfo{ 0 };
	BOOL Procerss = CreateProcessW(
		/*要执行的模块名称*/L"F:\\windows编程\\1. 简单的窗口\\Debug\\1. 简单的窗口.exe",
		/*要执行的命令行*/NULL,
		/*可否由子进程继承*/NULL,
		/*可否由子进程继承*/NULL,
		/*是否可被继承*/FALSE,					
		/*进程创建标志*/0,
		/*指向新进程的环境块的指针*/NULL,
		/*指定驱动器与工作目录*/NULL,
		&sw,			//进程启动信息
		&pInfo	//进程运行信息
	);

	CloseHandle(pInfo.hThread);
	CloseHandle(pInfo.hProcess);
	return 0;
}