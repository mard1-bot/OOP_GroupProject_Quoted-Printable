#ifndef ENCODER_H
#define ENCODER_H

#include <string>

//Прототип
char intToHexChar(int n);
std::string quotedPrintableEncode(const std::string& input);

#endif