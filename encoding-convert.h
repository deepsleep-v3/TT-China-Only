#include <string>
#include <Windows.h>
using namespace std;

string WideToGBK(const wchar_t* wstr) {
	int len = WideCharToMultiByte(936, 0, wstr, -1, NULL, 0, NULL, NULL);
	string utf8Str(len, 0);
	WideCharToMultiByte(936, 0, wstr, -1, &utf8Str[0], len, NULL, NULL);
	return utf8Str;
}

std::wstring GBKToWide(const std::string& gbkStr) {
	int len = MultiByteToWideChar(936, 0, gbkStr.c_str(), -1, NULL, 0);
	if (len == 0) return L"";

	std::wstring wstr(len, 0);
	MultiByteToWideChar(936, 0, gbkStr.c_str(), -1, &wstr[0], len);

	return wstr;
}