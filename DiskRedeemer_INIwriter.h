//DiskRedeemer_INIwriter
#include"OS.h"
#include"Language.h"
#include"ScenariosControl.h"
#include"ComplierControl.h"

#include<stdio.h>
#include<string.h>

#define MAXLEN 50

int main_INIwriter(void)
{
	char FileName[MAXLEN] = { 0 };

	#ifdef zh_CN
		printf("检测到您未曾创建过配置文件，且为Windows系统\n");
		printf("本程序用于记录一个文件名到临时ini配置文件中\n请您输入一个%d长度内的纯英文和数字构成的文件名\n", MAXLEN);
	#endif // zh_CN

	#ifdef en_US
		printf("It is detected that you have not created a profile, and running this program on Windows system\n");
		printf("This program is used to record a file name into the temporary ini configuration file\nPlease enter a file name composed of pure English and numbers within the length of %d\n", MAXLEN);
	#endif // en_US

	int flag_illegal = 1;
	while (flag_illegal != 0)
	{
		flag_illegal = 0;
		//scanf("%s", FileName);
		gets_s(FileName,MAXLEN-1);
		//遵照C11标准进行了buffer安全化处理
		int i = 0;
		int POS = 0;
		char CHR = '0';
		int length = (int)strlen(FileName);
		//for (i = 0; FileName[i] != '\0'; ++i)
		for (i = 0; i<length; ++i)
		{
			//if (FileName[i] >= 'a'&&FileName[i] <= 'z')
			//{
			//	if (FileName[i] >= 'A'&&FileName[i] <= 'Z')
			//	{
			//		if (FileName[i] >= '0'&&FileName[i] <= '9')
			//		{
			//			;//是一个合法的字符//This letter is a legal input
			//		}
			//		else
			//		{
			//			//是非法输入//This is illeagl input
			//			flag_illegal = 1;
			//			POS = i;
			//			CHR = FileName[i];
			//			break;
			//		}
			//	}
			//	else
			//	{
			//		//是非法输入//This is illeagl input
			//		flag_illegal = 1;
			//		POS = i;
			//		CHR = FileName[i];
			//		break;
			//	}
			//}
			//else
			//{
			//	//是非法输入//This is illeagl input
			//	flag_illegal = 1;
			//	POS = i;
			//	CHR = FileName[i];
			//	break;
			//}
			
			//对之前进行的粗放限制进行了修正，扩充了适用范围的同时解决了所有字符均会报错的BUG
			//玄学BUG只能靠重构来Fix

			#ifdef SYSTEM_WINDOWS
				if (FileName[i] == '\\' || FileName[i] == '/' || FileName[i] == ':')
				{
					flag_illegal = 1;
					POS = i;
					CHR = FileName[i];
					break;
				}
				if (FileName[i] == '*' || FileName[i] == '?' || FileName[i] == '"')
				{
					flag_illegal = 1;
					POS = i;
					CHR = FileName[i];
					break;
				}
				if (FileName[i] == '<' || FileName[i] == '>' || FileName[i] == '|')
				{
					flag_illegal = 1;
					POS = i;
					CHR = FileName[i];
					break;
				}
				//我们在Windows下屏蔽了\/:*?"<>|一共9种字符
			#endif // SYSTEM_WINDOWS

            #ifdef SYSTEM_LINUX
				if (FileName[i] == '?' || FileName[i] == '*' || FileName[i] == ' ')
				{
					flag_illegal = 1;
					POS = i;
					CHR = FileName[i];
					break;
				}
				if (FileName[i] == '$' || FileName[i] == '&' || FileName[i] == '/')
				{
					flag_illegal = 1;
					POS = i;
					CHR = FileName[i];
					break;
				}
				//我们在Linux下屏蔽了？* $&/一共6种字符
            #endif // SYSTEM_LINUX

            #ifdef SYSTEM_OTHERS
				；
            #endif // SYSTEM_OTHERS
			//重新按照不同操作系统的情况来分别定义了屏蔽掉的字符
		}
		if (flag_illegal == 1)
		{
			#ifdef zh_CN
				printf("您在%d位置的%c的输入非法。请您重新输入整个字符串\n",POS+1,CHR);
			#endif // zh_CN

			#ifdef en_US
				printf("Your input %c at position %d is illegal. Please re-enter the entire string\n", CHR, POS+1);
			#endif // en_US
		}
	}
	FILE *ini = fopen("DiskRedeemer.ini", "w");
	int length = (int)strlen(FileName);
	fprintf(ini,"[FileName]\n");
	fprintf(ini, "Length=%d\n", length);
	fprintf(ini, "String=%s\n", FileName);
	fclose(ini);
	return 0;
}