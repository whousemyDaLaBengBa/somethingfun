#include <cstdio>
#include <cstring>
#include <iostream>
#include <windows.h>
#include <wchar.h>

bool check_disk();
bool check_file(WCHAR* Driver_Path);

int main()
{
	check_disk();
	getchar();
	return 0;
}

bool check_file(WCHAR* Driver_Path)
{}

bool check_disk()
{
	DWORD allDisk = GetLogicalDrives();  //����һ��32λ����������ת���ɶ����ƺ󣬱�ʾ����,���λΪA��  ���緵��00011�ͱ�ʾ��a�̺�b��
	WCHAR Driver_Path[4]=TEXT("C:\\");
	if (allDisk != 0)
	{
		for (int i = 1;i<11;i++)     //�ٶ������10������
		{
			if ((allDisk & 1) == 1)		//����д���i
			{
				
				Driver_Path[0] = 'C' + i - 3;
				if (GetDriveType(Driver_Path) == DRIVE_REMOVABLE)
					if (check_file(Driver_Path))
						return 1;
			}
			allDisk = allDisk >> 1;
		}
	}
	return 0;
}

//��������˼·�ǿ���������Ȼ���ж�u�����Ƿ�����ض��ļ������ļ�
//��������رճ���
//����������ػ�
//����˼·��Դ��֪��������