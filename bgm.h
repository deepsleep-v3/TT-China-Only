#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include "encoding-convert.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

bool PlayMusic(const char* filePath, bool loop = false) {
    char command[256];
    
    // 打开音乐文件
    sprintf_s(command, "open \"%s\" type mpegvideo alias bgm", filePath);
    if (mciSendString(GBKToWide(command).c_str(), NULL, 0, NULL) != 0) {
        cerr << "无法打开音乐文件!" << std::endl;
        return false;
    }
    
    // 播放音乐 (可选循环)
    sprintf_s(command, "play bgm %s", loop ? " repeat" : "");
	if (mciSendString(GBKToWide(command).c_str(), NULL, 0, NULL) != 0) {
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