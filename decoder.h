#ifndef DECODER_H
#define DECODER_H

#include <string>
using namespace std;

// прототипы
bool isHexDigit(char c);
int hexCharToInt(char c);
string quotedPrintableDecode(const string& encoded);

#endif 