#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <TlHelp32.h>

#define Program_Name "360AP.exe"

bool check(WCHAR *p, char *t);
const wchar_t *GetWC(const char *c);
bool kill(unsigned int PID);


int main()
{
	HANDLE hSnapshot;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	// 获取进程快照
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot (of processes) 失败\n");
		return 0;
	}
	// 设置输入参数，结构的大小
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// 开始列举进程信息
	if (!Process32First(hSnapshot, &pe32))
	{
		printf("Process32First() 失败\n");
		CloseHandle(hSnapshot); // 关闭句柄
		return 0;
	}

	printf("进程ID	父进程	线程数	优先级	进程名\n"); // 基本优先级
	do
	{
		if (check(pe32.szExeFile, Program_Name))// 打印进程相关信息
		{
			printf("%u", pe32.th32ProcessID);    // 进程id 这个就是PID了
			printf("	%u", pe32.th32ParentProcessID);  // 父进程id
			printf("	%d", pe32.cntThreads);       // 线程数
			printf("	%d", pe32.pcPriClassBase);   // 基本优先级
			printf("	%ws\n", pe32.szExeFile);      // 进程名这里输出不能是简单的%s，这里得用%ws
			printf("%d\n", kill(pe32.th32ProcessID));
		}

	} while (Process32Next(hSnapshot, &pe32));

	CloseHandle(hSnapshot);   //关闭句柄
	return 0;
}

WCHAR * charToWchar(char *s)
{
	int w_nlen = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	WCHAR *ret;
	ret = (WCHAR*)malloc(sizeof(WCHAR)*w_nlen);
	memset(ret, 0, sizeof(ret));
	MultiByteToWideChar(CP_ACP, 0, s, -1, ret, w_nlen);
	return ret;
}

bool check(WCHAR *p, char *t)
{
	WCHAR *tt = charToWchar(t);
	int lenp = wcslen(p);
	int lent = wcslen(tt);
	if (lenp == lent)
	{
		for (int k = 0;k < lenp;k++)
			if (p[k] != tt[k])
				return 0;
		return 1;
	}
	else
		return 0;

}

bool kill(unsigned int PID)
{
	int ProcessID = PID;
	// 获取进程句柄
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)ProcessID);
	// 终止进程
	return TerminateProcess(hProcess, 0);
}

