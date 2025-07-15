#include <type_traits>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <Windows.h>
#include <thread>
#include <string>
#undef max
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename _Ty>
requires is_arithmetic_v<_Ty>
class Range {
private:
    _Ty m_begin;
    _Ty m_end;
public:
    Range(int32_t begin, int32_t end) {
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
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒." << endl;
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
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒." << endl;
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
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒." << endl;
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
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒." << endl;
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
            cout << "你好像打错了，检查一下吧，如果检查好了，按任意字母或数字键." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "输入正确！用时: " << duration << " 秒." << endl;
            cout << "平均每个字符用时：" << duration / sz.length() << "秒" << endl;
            break;
        }
    }
}

int main()
{
    std::random_device rd;
    unsigned int seed = rd();
    mt19937 hRndEngine(seed);
    size_t oprt = 0;
    while (true) {
        cout << "打字测试V1.0 BY DEEPSLEEP-V3（包含21字，36字....）" << endl;
        cout << "1，简单\n2，还行（默认）\n3，普通\n4，进阶\n5，硬核\n6，退出\n请输入你的选択：[ ]\n";
        gotoxy(17, 7);
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
        cout << "如果要开始下一局，按下任意键." << endl;
        system("pause");
        clrscr();
    }
}
