#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;


bool PlayMusic(const wchar_t* filePath, bool loop = false) {
    wchar_t command[256];
    
    // �������ļ�
    swprintf_s(command, L"open \"%s\" type mpegvideo alias bgm", filePath);
    if (mciSendStringW(command, NULL, 0, NULL) != 0) {
        cerr << "�޷��������ļ�!" << std::endl;
        return false;
    }
    
    // �������� (��ѡѭ��)
    swprintf_s(command, L"play bgm %s", loop ? L" repeat" : L"");
    if (mciSendStringW(command, NULL, 0, NULL) != 0) {
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