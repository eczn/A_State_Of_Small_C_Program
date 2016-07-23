#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
//#pragma comment(lib, "Winmm")

int main(int argc, char *argv[])
{
    //TCHAR fileName[]="D://mp3//Someone Like You.mp3"; //??????
    printf("%d\n\a\a\a\a\a",MAX_PATH);
    TCHAR fileName[]="test.mp3";
    
    TCHAR shortName[MAX_PATH];
    
    GetShortPathName(fileName,shortName,sizeof(shortName)/sizeof(TCHAR));
    
    printf("shortName = %s\n",shortName);
    
    TCHAR cmd[MAX_PATH+10];
    wsprintf(cmd,"play %s",shortName);
    
    printf("cmd = %s\n",cmd);
    mciSendString(cmd,NULL, 0, NULL);
    
    //mciSendString("play SOMEON~1.mp3",NULL, 0, NULL); //?????mp3

    Sleep(5 * 60 * 1000); //???????????????
    
	return 0;
}

