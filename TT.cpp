// TT.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <type_traits>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <Windows.h>
#include <VersionHelpers.h>
#undef max
#include <thread>
#include <string>
#include <conio.h>
#define SDL_MAIN_HANDLED
#include "packages\sdl2.2.0.5\build\native\include\SDL.h"
#include <Xinput.h>
#pragma comment(lib, TEXT("Xinput.lib"))
using namespace std;


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename _Ty>
class Range {
private:
    _Ty m_begin;
    _Ty m_end;
public:
    Range(int begin, int end) {
		static_assert(is_arithmetic<_Ty>::value, "泛型的类型“_Ty”必须是算数类型。");
        m_begin = begin;
        m_end = end;
    }

    vector<_Ty> toVector() {
        vector<_Ty> naResult;
        for (_Ty nCurrentValue = m_begin; nCurrentValue <= m_end; nCurrentValue++) {
            naResult.push_back(nCurrentValue);
        }
        return naResult;
    }
};

template<class K, class V>
class KeyValPairs {
	vector<K> Keys = {};
	vector<V> Values = {};
public:
	V get(K Key) {
		if (it = Keys.begin()) {
			auto it = find(Keys.begin(), Keys.end(), Key);
			if (it != Keys.begin()) {
				return Values[distance(Keys.begin(), it)]
			}
		}
		else {
			return null;
		}
	}
};

template<typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result = a;
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

void gotoxy(__int16 x, __int16 y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clrscr() {
    HANDLE hdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hdout, &csbi);
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y, num = 0; 
    COORD pos = { 0, 0 };
    FillConsoleOutputCharacter(hdout, ' ', size, pos, &num);
    FillConsoleOutputAttribute(hdout, csbi.wAttributes, size, pos, &num);
    SetConsoleCursorPosition(hdout, pos);
}

bool IsWindows10Build17763OrGreater() {
	// 获取操作系统版本信息
	OSVERSIONINFOEX osvi = { sizeof(OSVERSIONINFOEX) };
	DWORDLONG dwlConditionMask = 0;

	// 设置要检查的版本条件
	osvi.dwMajorVersion = 10;
	osvi.dwMinorVersion = 0;
	osvi.dwBuildNumber = 17763;  // 1809 的初始版本号

								 // 设置版本比较掩码
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_BUILDNUMBER, VER_GREATER_EQUAL);

	// 执行版本检查
	return VerifyVersionInfo(
		&osvi,
		VER_MAJORVERSION | VER_MINORVERSION | VER_BUILDNUMBER,
		dwlConditionMask
	) != FALSE;
}

string generateRandomString(mt19937& engine, size_t length) {
    // 字符集：大小写字母（共52个）
    vector<char> all_letters = Range<char>(65, 122).toVector();
    // 随机分布：从0到charset.size()-1
    uniform_int_distribution<size_t> dist(0, all_letters.size() - 1);

    string result;
    result.reserve(length); // 预分配空间
    for (size_t i = 0; i < length; ++i) {
        result += all_letters[dist(engine)]; // 随机选择字符（允许重复）
    }
    return result;
}

void easy(mt19937 &mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 21);
        cout << "请打出“" << sz << "”." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键。" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒。" << endl;
            cout << "平均每个字符用时：" << duration / sz.length() << "秒" << endl;
            break;
        }
    }
}
void upgrade(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 36);
        cout << "请打出“" << sz << "”." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键。" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒。" << endl;
            cout << "平均每个字符用时：" << duration / sz.length() << "秒" << endl;
            break;
        }
    }
}
void normal(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 50);
        cout << "请打出“" << sz << "”." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键。" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒。" << endl;
            cout << "平均每个字符用时：" << duration / sz.length() << "秒" << endl;
            break;
        }
    }
}

void advanced(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 67);
        cout << "请打出“" << sz << "”." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        time_t duration = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
        if (input != sz) {
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键。" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒。" << endl;
            cout << "平均每个字符用时：" << duration / sz.length() << "秒" << endl;
            break;
        }
    }
}

void hardcore(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 99);
        cout << "请打出“" << sz << "”." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键。" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒。" << endl;
            cout << "平均每个字符用时：" << duration / sz.length() << "秒" << endl;
            break;
        }
    }
}

int keyboard()
{
    std::random_device rd;
    unsigned int seed = rd();
    mt19937 hRndEngine(seed);
    size_t oprt = 0;
    char kbdInput = 'A';
	string _ = "";
    while (true) {
        cout << "打字测试V1.0 BY DEEPSLEEP-V3（包含21字，36字....）" << endl;
        cout << "1，简单\n2，还行（默认）\n3，普通\n4，进阶\n5，硬核\n6，帮助\n7，退出\n请输入你的选択：[ ]\n";
        gotoxy(17, 8);
        cin >> oprt;
        clrscr();
        this_thread::sleep_for(chrono::seconds(1));
        cout << "3...." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "2...." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        cout << "1...." << endl;
        this_thread::sleep_for(chrono::seconds(1));
        clrscr();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (oprt)
        {
        case 1:
            easy(hRndEngine);
            break;
        case 2:
            upgrade(hRndEngine);
            break;
        case 3:
            normal(hRndEngine);
            break;
        case 4:
            advanced(hRndEngine);
            break;
        case 5:
            hardcore(hRndEngine);
            break;
        case 6:
            clrscr();
            cout << "[esc] 退出帮助系统" << endl;
            cout << "[ 1 ] 玩法" << endl;
            while (1) {
                if (_kbhit()) {
                    kbdInput = _getch();
                    if (kbdInput == 27 || kbdInput == '1') { break; }
                }
            }
			switch(kbdInput){
			case 27:
				clrscr();
				continue;
			case '1':
				clrscr();
				cout << "你可以通过主界面选择难度，倒计时后，本软件将会生成一个随机字符串（ASCII 65至122）。" << endl;
				cout << "你需要一字不误（且区分大小写，以后可能会是选项式）打出这个字符串，当然，也不是说打错了就没有机会了，在你打错后，程序会弹出一段提示，可以让你检查，检查过后，你可以按下键盘上的一个字符，可以再试一次。" << endl;
				cout << "按下“回车”继续...." << endl;
				while (1) {
                    if (_kbhit()) {
                        kbdInput = _getch();
                        if (kbdInput == '\r') { break; }
                    }
                }
				clrscr();
				continue;
			}
            break;
		case 7:
			return 0;
        default:
            cout << "你的选択无效，倒计时后，将执行默认选项（2，还行）" << endl;
            this_thread::sleep_for(chrono::milliseconds(2500));
            clrscr();
            cout << "3...." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "2...." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            cout << "1...." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            clrscr();
            upgrade(hRndEngine);
        }
        cout << "如果要开始下一局，按下任意键。" << endl;
        system("pause");
        clrscr();
    }
}

int xbox360controller()
{
	int nChoose = MessageBox(NULL, 
		TEXT("此游戏为单人游戏，所以请不要连接多个Xbox控制器！如果你想多个人玩，那么请点击“取消”按钮！反之点击“确定”！P.S.即使连了也只会反応一个手柄的操作:)"), 
		TEXT("温馨提示awa"), 
		MB_ICONEXCLAMATION | MB_OKCANCEL);
	if (nChoose == IDCANCEL) {
		return 0;
	}
	cout << "Initializeing Xbox Controller Button Map and random engine, please wait..." << endl;
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
		cout << "SDL初始化失败: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}
	SDL_GameController* hWatermelonGamepad = SDL_GameControllerOpen(0);
	if (!hWatermelonGamepad) {
		cout << "无法打开控制器: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}
	std::random_device rd;
	unsigned int seed = rd();
	mt19937 hRndEngine(seed);
	size_t oprt = 0;
	char kbdInput = 'A';
	string _ = "";
	cout << "Checking your Device Compliant or not, please wait..." << endl;
	XINPUT_CAPABILITIES hModel;
	XInputGetCapabilities(0, 0, &hModel);
	if (hModel.SubType != XINPUT_DEVSUBTYPE_GAMEPAD) {
		cout << "Sorry, Your device 1 isn't a Gamepad, It's mean you will not be able to play this Game. You can choose \033[92mSwitch to Keyboard to Control\033[0m, or \033[96mExit Game." << endl;
	}
	clrscr();
	while (true) {
		cout << "打字测试V1.0 BY DEEPSLEEP-V3（包含21字，36字....）" << endl;
		cout << "1，简单\n2，还行（默认）\n3，普通\n4，进阶\n5，硬核\n6，帮助\n7，退出\n请输入你的选択：[ ]\n";
		gotoxy(17, 8);
		cin >> oprt;
		clrscr();
		this_thread::sleep_for(chrono::seconds(1));
		cout << "3...." << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "2...." << endl;
		this_thread::sleep_for(chrono::seconds(1));
		cout << "1...." << endl;
		this_thread::sleep_for(chrono::seconds(1));
		clrscr();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (oprt)
		{
		case 1:
			easy(hRndEngine);
			break;
		case 2:
			upgrade(hRndEngine);
			break;
		case 3:
			normal(hRndEngine);
			break;
		case 4:
			advanced(hRndEngine);
			break;
		case 5:
			hardcore(hRndEngine);
			break;
		case 6:
			clrscr();
			cout << "[ B ] 退出帮助系统" << endl;
			cout << "[ X ] 玩法" << endl;
			while (true) {
				if (SDL_GameControllerGetButton(hWatermelonGamepad, SDL_CONTROLLER_BUTTON_B)) {
					clrscr();
					continue;
				}
				else if (SDL_GameControllerGetButton(hWatermelonGamepad, SDL_CONTROLLER_BUTTON_X)) {
					clrscr();
					cout << "你可以通过主界面选择难度，倒计时后，本软件将会生成一个随机字符串（ASCII 65至122）。" << endl;
					cout << "你需要一字不误（且区分大小写，以后可能会是选项式）打出这个字符串，当然，也不是说打错了就没有机会了，在你打错后，程序会弹出一段提示，可以让你检查，检查过后，你可以按下键盘上的一个字符，可以再试一次。" << endl;
					cout << "按下“A”继续...." << endl;
					if (SDL_GameControllerGetButton(hWatermelonGamepad, SDL_CONTROLLER_BUTTON_A)) {
						clrscr();
						continue;
					}
				}
			}
			break;
		case 7:
			SDL_GameControllerClose(hWatermelonGamepad);
			SDL_Quit();
			return 0;
		default:
			cout << "你的选択无效，倒计时后，将执行默认选项（2，还行）" << endl;
			this_thread::sleep_for(chrono::milliseconds(2500));
			clrscr();
			cout << "3...." << endl;
			this_thread::sleep_for(chrono::seconds(1));
			cout << "2...." << endl;
			this_thread::sleep_for(chrono::seconds(1));
			cout << "1...." << endl;
			this_thread::sleep_for(chrono::seconds(1));
			clrscr();
			upgrade(hRndEngine);
		}
		cout << "如果要开始下一局，按下A。" << endl;
		while (1) {
			if (SDL_GameControllerGetButton(hWatermelonGamepad, SDL_CONTROLLER_BUTTON_A)) {
				clrscr();
				break;
			}
		}
	}
}


int main(int argc, char** argv) {
	if (GetACP() != 936) {
		cout << "Due to coding differences, \"TT(China only)\" cannot provide services for you. You can switch to the international version. Of course, if you don't mind the trouble and can understand Chinese, you can install a Chinese version of Windows to experience \"TT(China only)\" (of course, this is a bad idea for many people)" << endl;
		cout << "We deeply apologize for any inconvenience caused to you." << endl;
		cout << "          --\"TT(China only)\" Development Team" << endl;
		system("pause");
		return 1;
	}
	if (!IsWindows10Build17763OrGreater())
	{
		cout << "你的Windows版本过旧。" << endl;
		return ERROR_OLD_WIN_VERSION;
	}
	int oprt = 1;
	cout << "【1】 用键盘进行操作" << endl;
	cout << "请选择操作：[ ]" << endl;
	gotoxy(13, 2);
	cin >> oprt;
	while (true) {
		switch (oprt) {
		case 1:
			clrscr();
			return keyboard();
		default:
			continue;
		}
	}
}
