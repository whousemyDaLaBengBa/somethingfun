#include <cstdio>
#include <cstring>
#include <iostream>
#include <windows.h>

bool check_disk();

int main()
{
	check_disk();
	getchar();
	return 0;
}

bool check_disk()
{
	char diskPath[5] = { 0 };
	DWORD allDisk = GetLogicalDrives();  //����һ��32λ����������ת���ɶ����ƺ󣬱�ʾ����,���λΪA��  ���緵��00011�ͱ�ʾ��a�̺�b��

	if (allDisk != 0)
	{
		for (int i = 1;i<11;i++)     //�ٶ������10������
		{
			if ((allDisk & 1) == 1)		//����д���i
			{
				printf("%d\n", i);
				/*if (GetDriveType(diskPath) == DRIVE_REMOVABLE)
				{
					//AfxMessageBox( "��⵽U��", MB_OK );
					//AfxMessageBox( diskPath, MB_OK );

					if (GetVolumeInformation(diskPath, 0, 0, 0, 0, 0, 0, 0))  //�ж������Ƿ�׼������
					{
						printf("U�̾���\n");
						break;
					}
				}*/
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