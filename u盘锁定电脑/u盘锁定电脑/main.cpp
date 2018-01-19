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
	DWORD allDisk = GetLogicalDrives();  //返回一个32位整数，将他转换成二进制后，表示磁盘,最低位为A盘  比如返回00011就表示有a盘和b盘
	WCHAR Driver_Path[4]=TEXT("C:\\");
	if (allDisk != 0)
	{
		for (int i = 1;i<11;i++)     //假定最多有10个磁盘
		{
			if ((allDisk & 1) == 1)		//如果有磁盘i
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

//这个程序的思路是开机启动，然后判断u盘中是否存在特定文件名的文件
//若存在则关闭程序
//若不存在则关机
//程序思路来源与知乎评论区