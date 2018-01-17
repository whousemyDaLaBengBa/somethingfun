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
	// ��ȡ���̿���
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot (of processes) ʧ��\n");
		return 0;
	}
	// ��������������ṹ�Ĵ�С
	pe32.dwSize = sizeof(PROCESSENTRY32);

	// ��ʼ�оٽ�����Ϣ
	if (!Process32First(hSnapshot, &pe32))
	{
		printf("Process32First() ʧ��\n");
		CloseHandle(hSnapshot); // �رվ��
		return 0;
	}

	printf("����ID	������	�߳���	���ȼ�	������\n"); // �������ȼ�
	do
	{
		if (check(pe32.szExeFile, Program_Name))// ��ӡ���������Ϣ
		{
			printf("%u", pe32.th32ProcessID);    // ����id �������PID��
			printf("	%u", pe32.th32ParentProcessID);  // ������id
			printf("	%d", pe32.cntThreads);       // �߳���
			printf("	%d", pe32.pcPriClassBase);   // �������ȼ�
			printf("	%ws\n", pe32.szExeFile);      // ������������������Ǽ򵥵�%s���������%ws
			printf("%d\n", kill(pe32.th32ProcessID));
		}

	} while (Process32Next(hSnapshot, &pe32));

	CloseHandle(hSnapshot);   //�رվ��
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
	// ��ȡ���̾��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)ProcessID);
	// ��ֹ����
	return TerminateProcess(hProcess, 0);
}

