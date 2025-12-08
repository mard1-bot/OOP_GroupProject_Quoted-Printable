#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// функция проверки, является ли символ шестнадцатеричной цифрой
bool isHexDigit(char c) {
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

// функция преобразования шестнадцатеричного символа в число
int hexCharToInt(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

// основная функция декодирования Quoted-Printable
string quotedPrintableDecode(const string& encoded) {
    string result;
    
    for (size_t i = 0; i < encoded.length(); i++) {
        char current = encoded[i];
        
        if (current != '=') {
            // обычный символ - добавляем как есть
            result.push_back(current);
        } else {
            // обработка последовательностей с '='
            
            // проверка на мягкий перевод строки
            if (i + 1 < encoded.length()) {
                char next = encoded[i + 1];
                
                // проверка на "=\r\n" (CRLF)
                if (next == '\r' && i + 2 < encoded.length() && encoded[i + 2] == '\n') {
                    i += 2; // пропускаем =\r\n
                    continue;
                }
                
                // проверка на "=\n" (LF)
                if (next == '\n') {
                    i += 1; // Пропускаем =\n
                    continue;
                }
                
                // проверка на шестнадцатеричную последовательность =XX
                if (i + 2 < encoded.length()) {
                    char hex1 = encoded[i + 1];
                    char hex2 = encoded[i + 2];
                    
                    if (isHexDigit(hex1) && isHexDigit(hex2)) {
                        // преобразуем шестнадцатеричную пару в символ
                        int byteValue = hexCharToInt(hex1) * 16 + hexCharToInt(hex2);
                        result.push_back(static_cast<char>(byteValue));
                        i += 2; // пропускаем два шестнадцатеричных символа
                    } else {
                        // некорректная последовательность - оставляем '='
                        result.push_back('=');
                    }
                } else {
                    // недостаточно символов для завершения последовательности
                    result.push_back('=');
                }
            } else {
                // '=' в конце строки
                result.push_back('=');
            }
        }
    }
    
    return result;
}