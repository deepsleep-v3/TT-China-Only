// TT.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <type_traits>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <Windows.h>
#include <thread>
#include <string>
#include <conio.h>
#include "bgm.h"
#undef max
using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename _Ty>
class Range {
private:
    _Ty m_begin;
    _Ty m_end;
public:
    Range(int begin, int end) {
		static_assert(is_arithmetic<_Ty>::value, "���͵����͡�_Ty���������������͡�");
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
    // �ַ�������Сд��ĸ����52����
    vector<char> all_letters = Range<char>(65, 122).toVector();
    // ����ֲ�����0��charset.size()-1
    uniform_int_distribution<size_t> dist(0, all_letters.size() - 1);

    string result;
    result.reserve(length); // Ԥ����ռ�
    for (size_t i = 0; i < length; ++i) {
        result += all_letters[dist(engine)]; // ���ѡ���ַ��������ظ���
    }
    return result;
}

void easy(mt19937 &mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 21);
        cout << "������" << sz << "��." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "��������ˣ����һ�°ɣ���������ˣ���������ĸ�����ּ���" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "������ȷ����ʱ: " << duration << " �롣" << endl;
            cout << "ƽ��ÿ���ַ���ʱ��" << duration / sz.length() << "��" << endl;
            break;
        }
    }
}
void upgrade(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 36);
        cout << "������" << sz << "��." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "��������ˣ����һ�°ɣ���������ˣ���������ĸ�����ּ���" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "������ȷ����ʱ: " << duration << " �롣" << endl;
            cout << "ƽ��ÿ���ַ���ʱ��" << duration / sz.length() << "��" << endl;
            break;
        }
    }
}
void normal(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 50);
        cout << "������" << sz << "��." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "��������ˣ����һ�°ɣ���������ˣ���������ĸ�����ּ���" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "������ȷ����ʱ: " << duration << " �롣" << endl;
            cout << "ƽ��ÿ���ַ���ʱ��" << duration / sz.length() << "��" << endl;
            break;
        }
    }
}

void advanced(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 67);
        cout << "������" << sz << "��." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "��������ˣ����һ�°ɣ���������ˣ���������ĸ�����ּ���" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "������ȷ����ʱ: " << duration << " �롣" << endl;
            cout << "ƽ��ÿ���ַ���ʱ��" << duration / sz.length() << "��" << endl;
            break;
        }
    }
}

void hardcore(mt19937& mt19937RndEngine) {
    while (true) {
        string input = "";
        string sz = generateRandomString(mt19937RndEngine, 99);
        cout << "������" << sz << "��." << endl;
        auto startTime = chrono::high_resolution_clock::now();
        cin >> input;
        auto endTime = chrono::high_resolution_clock::now();
        double duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime).count();
        if (input != sz) {
            cout << "��������ˣ����һ�°ɣ���������ˣ���������ĸ�����ּ���" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getchar();
            clrscr();
            continue;
        }
        else {
            cout << "������ȷ����ʱ: " << duration << " �롣" << endl;
            cout << "ƽ��ÿ���ַ���ʱ��" << duration / sz.length() << "��" << endl;
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
    char kbdInput = 'A';
	string _ = "";
    while (true) {
        cout << "���ֲ���V1.0 BY DEEPSLEEP-V3������21�֣�36��....��" << endl;
        cout << "1����\n2�����У�Ĭ�ϣ�\n3����ͨ\n4������\n5��Ӳ��\n6������\n7������С�������\n7���˳�\n���������ѡ�k��[ ]\n";
        gotoxy(17, 9);
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
            clrscr();
            cout << "[esc] �˳�����ϵͳ" << endl;
            cout << "[ 1 ] �淨" << endl;
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
				cout << "�����ͨ��������ѡ���Ѷȣ�����ʱ�󣬱������������һ������ַ�����ASCII 65��122����" << endl;
				cout << "����Ҫһ�ֲ��������ִ�Сд���Ժ���ܻ���ѡ��ʽ���������ַ�������Ȼ��Ҳ����˵����˾�û�л����ˣ�������󣬳���ᵯ��һ����ʾ�����������飬����������԰��¼����ϵ�һ���ַ�����������һ�Ρ�" << endl;
				cout << "���¡��س�������...." << endl;
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
            cout << "���ѡ�k��Ч������ʱ�󣬽�ִ��Ĭ��ѡ�2�����У�" << endl;
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
        cout << "���Ҫ��ʼ��һ�֣������������" << endl;
        system("pause");
        clrscr();
    }
}


