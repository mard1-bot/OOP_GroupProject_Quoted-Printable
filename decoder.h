#ifndef DECODER_H
#define DECODER_H

#include <string>

// Прототипы функций
bool isHexDigit(char c);
int hexCharToInt(char c);
std::string quotedPrintableDecode(const std::string& encoded);

#endif