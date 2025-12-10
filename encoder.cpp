#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cctype>

using namespace std;

// функция преобразования числа в шестнадцатеричный символ
char intToHexChar(int n) {
    if (n >= 0 && n <= 9) return '0' + n;
    if (n >= 10 && n <= 15) return 'A' + (n - 10);
    return '0'; // fallback
}

// функция кодирования строки в Quoted-Printable
string quotedPrintableEncode(const string& input) {
    string result;
    for (char c : input) {
        unsigned char uc = static_cast<unsigned char>(c);

        // проверка на безопасный символ (ASCII 33-60, 62-126, кроме '=')
        if ((uc >= 33 && uc <= 60) || (uc >= 62 && uc <= 126)) {
            result.push_back(c);
        }
        else if (c == ' ' || c == '\t') {
            // пробел или табуляция на конце строки нужно кодировать
            result.push_back(c);
        }
        else if (c == '\r' || c == '\n') {
            // оставляем переводы строк как есть
            result.push_back(c);
        }
        else {
            // кодируем все остальные символы
            result.push_back('=');
            result.push_back(intToHexChar((uc >> 4) & 0xF)); // старшая 4 бита
            result.push_back(intToHexChar(uc & 0xF));        // младшая 4 бита
        }
    }
    return result;
}
