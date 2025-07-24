#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "encoding-convert.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

bool PlayMusic(const char* filePath, bool loop = false) {
    char command[256];
    
    // �������ļ�
    sprintf_s(command, "open \"%s\" type mpegvideo alias bgm", filePath);
    if (mciSendString(GBKToWide(command).c_str(), NULL, 0, NULL) != 0) {
        cerr << "�޷��������ļ�!" << std::endl;
        return false;
    }
    
    // �������� (��ѡѭ��)
    sprintf_s(command, "play bgm %s", loop ? " repeat" : "");
	if (mciSendString(GBKToWide(command).c_str(), NULL, 0, NULL) != 0) {
        cerr << "�޷���������!" << std::endl;
        return false;
    }
    
    return true;
}

// ֹͣ���ֺ���
void StopMusic() {
    mciSendString(L"stop bgm", NULL, 0, NULL);
    mciSendString(L"close bgm", NULL, 0, NULL);
}