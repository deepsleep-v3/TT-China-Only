#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;


bool PlayMusic(const wchar_t* filePath, bool loop = false) {
    wchar_t command[256];
    
    // 打开音乐文件
    swprintf_s(command, L"open \"%s\" type mpegvideo alias bgm", filePath);
    if (mciSendStringW(command, NULL, 0, NULL) != 0) {
        cerr << "无法打开音乐文件!" << std::endl;
        return false;
    }
    
    // 播放音乐 (可选循环)
    swprintf_s(command, L"play bgm %s", loop ? L" repeat" : L"");
    if (mciSendStringW(command, NULL, 0, NULL) != 0) {
        cerr << "无法播放音乐!" << std::endl;
        return false;
    }
    
    return true;
}

// 停止音乐函数
void StopMusic() {
    mciSendString(L"stop bgm", NULL, 0, NULL);
    mciSendString(L"close bgm", NULL, 0, NULL);
}