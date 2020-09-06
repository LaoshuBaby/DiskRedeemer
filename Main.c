#include"ComplierControl.h"

#ifdef DiskRedeemer_OpenMP
	//#include"DiskRedeemer_INIwriter.h"
	#include"DiskRedeemer_OpenMP.h"

	int main(int argc,char *argv[])
	{
		main_Redeemer(argc,argv);
		return 0;
	}
#endif // DiskRedeemer_OpenMP//Ö÷³ÌÐò

#ifdef DiskRedeemer_INIwriter
	#include"DiskRedeemer_INIwriter.h"
	//#include"DiskRedeemer_OpenMP.h"

	int main(void)
	{
		main_INIwriter();
		return 0;
	}
#endif // DiskRedeemer_INIwriter

