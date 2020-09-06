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
		printf("��⵽��δ�������������ļ�����ΪWindowsϵͳ\n");
		printf("���������ڼ�¼һ���ļ�������ʱini�����ļ���\n��������һ��%d�����ڵĴ�Ӣ�ĺ����ֹ��ɵ��ļ���\n", MAXLEN);
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
		//����C11��׼������buffer��ȫ������
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
			//			;//��һ���Ϸ����ַ�//This letter is a legal input
			//		}
			//		else
			//		{
			//			//�ǷǷ�����//This is illeagl input
			//			flag_illegal = 1;
			//			POS = i;
			//			CHR = FileName[i];
			//			break;
			//		}
			//	}
			//	else
			//	{
			//		//�ǷǷ�����//This is illeagl input
			//		flag_illegal = 1;
			//		POS = i;
			//		CHR = FileName[i];
			//		break;
			//	}
			//}
			//else
			//{
			//	//�ǷǷ�����//This is illeagl input
			//	flag_illegal = 1;
			//	POS = i;
			//	CHR = FileName[i];
			//	break;
			//}
			
			//��֮ǰ���еĴַ����ƽ��������������������÷�Χ��ͬʱ����������ַ����ᱨ���BUG
			//��ѧBUGֻ�ܿ��ع���Fix

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
				//������Windows��������\/:*?"<>|һ��9���ַ�
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
				//������Linux�������ˣ�* $&/һ��6���ַ�
            #endif // SYSTEM_LINUX

            #ifdef SYSTEM_OTHERS
				��
            #endif // SYSTEM_OTHERS
			//���°��ղ�ͬ����ϵͳ��������ֱ��������ε����ַ�
		}
		if (flag_illegal == 1)
		{
			#ifdef zh_CN
				printf("����%dλ�õ�%c������Ƿ��������������������ַ���\n",POS+1,CHR);
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