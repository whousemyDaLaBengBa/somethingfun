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
	DWORD allDisk = GetLogicalDrives();  //返回一个32位整数，将他转换成二进制后，表示磁盘,最低位为A盘  比如返回00011就表示有a盘和b盘

	if (allDisk != 0)
	{
		for (int i = 1;i<11;i++)     //假定最多有10个磁盘
		{
			if ((allDisk & 1) == 1)		//如果有磁盘i
			{
				printf("%d\n", i);
				/*if (GetDriveType(diskPath) == DRIVE_REMOVABLE)
				{
					//AfxMessageBox( "检测到U盘", MB_OK );
					//AfxMessageBox( diskPath, MB_OK );

					if (GetVolumeInformation(diskPath, 0, 0, 0, 0, 0, 0, 0))  //判断驱动是否准备就绪
					{
						printf("U盘就绪\n");
						break;
					}
				}*/
			}

			allDisk = allDisk >> 1;
		}
	}
	return 0;
}

//这个程序的思路是开机启动，然后判断u盘中是否存在特定文件名的文件
//若存在则关闭程序
//若不存在则关机
//程序思路来源与知乎评论区