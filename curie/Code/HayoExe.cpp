#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){
	int input = argv[1][0]-'0';
	if(input==1)
		PlaySound("C:/Users/Blackrental/eclipse-workspace/WeCane/Sound/fail-buzzer-01.wav",NULL,SND_FILENAME);
	if(input==2)
		PlaySound("C:/Users/Blackrental/eclipse-workspace/WeCane/Sound/Warning.wav",NULL,SND_FILENAME);
    return 0;
}
