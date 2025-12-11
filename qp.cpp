#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "encoder.h"
#include "decoder.h"

using namespace std;

void printHelp(const char* name) {
    cout << "Usage: " << name << " [options] [text]\n\n";
    cout << "Quoted-Printable encoder/decoder\n\n";
    cout << "Options:\n";
    cout << "  -e, --encrypt          Encode text\n";
    cout << "  -d, --decrypt          Decode text\n";
    cout << "  -f, --file <file>      Read from file\n";
    cout << "  -o, --output <file>    Write to file\n";
    cout << "  -h, --help             Show this help\n\n";
    cout << "Positional commands:\n";
    cout << "  " << name << " encrypt \"Hello\"\n";
    cout << "  " << name << " decrypt \"=48=65=6C=6C=6F\"\n";
    cout << "  " << name << " encode file.txt\n";
    cout << "  " << name << " decode file.qp\n\n";
    cout << "Examples:\n";
    cout << "  " << name << " --encrypt \"Привет мир\"\n";
    cout << "  " << name << " -d \"Hello=20World\"\n";
    cout << "  " << name << " -e -f input.txt -o encoded.qp\n";
}

string readFile(const string& path) {
    ifstream f(path, ios::binary);
    if (!f) {
        cerr << "Error: cannot open file " << path << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(f)), {});
}

void writeFile(const string& path, const string& data) {
    ofstream f(path, ios::binary);
    if (!f) {
        cerr << "Error: cannot write to file " << path << endl;
        exit(1);
    }
    f << data;
}

int main(int argc, char* argv[]) {
    //Поддержка кириллицы, если Windows
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    if (argc == 1) {
        printHelp(argv[0]);
        return 0;
    }

    vector<string> args;
    for (int i = 1; i < argc; ++i) args.push_back(argv[i]);

    bool doEncode = false, doDecode = false;
    string inFile, outFile, text;

    // --help в любом месте
    for (const auto& a : args)
        if (a == "-h" || a == "--help") {
            printHelp(argv[0]);
            return 0;
        }

    // 1. Позиционный режим: qp encrypt "text"   или   qp decode file.qp
    if (!args.empty() && args[0].find('-') != 0) {
        string cmd = args[0];
        if (cmd == "encrypt" || cmd == "encode" || cmd == "e") doEncode = true;
        else if (cmd == "decrypt" || cmd == "decode" || cmd == "d") doDecode = true;
        else {
            cerr << "Unknown command: " << cmd << endl;
            return 1;
        }
        args.erase(args.begin());

        // После команды может быть -f file или просто текст
        if (!args.empty() && (args[0] == "-f" || args[0] == "--file")) {
            if (args.size() < 2) { cerr << "Missing filename after -f\n"; return 1; }
            inFile = args[1];
            args.erase(args.begin(), args.begin() + 2);
        }
        else if (!args.empty()) {
            text = args[0];
            for (size_t i = 1; i < args.size(); ++i) text += " " + args[i];
        }
    }
    else {
        // 2. Классический режим с флагами
        for (size_t i = 0; i < args.size(); ++i) {
            string a = args[i];
            if (a == "-e" || a == "--encrypt") doEncode = true;
            else if (a == "-d" || a == "--decrypt") doDecode = true;
            else if ((a == "-f" || a == "--file") && i + 1 < args.size()) inFile = args[++i];
            else if ((a == "-o" || a == "--output") && i + 1 < args.size()) outFile = args[++i];
            else if (a.find('-') != 0) {
                text = a;
                for (++i; i < args.size(); ++i) text += " " + args[i];
                break;
            }
        }
    }

    if (doEncode + doDecode != 1) {
        cerr << "Error: specify exactly one of -e/--encrypt or -d/--decrypt\n";
        return 1;
    }

    string input;
    if (!inFile.empty())
        input = readFile(inFile);
    else if (!text.empty())
        input = text;
    else {
        // Чтение из stdin
        cin >> noskipws;
        istream_iterator<char> it(cin), end;
        input = string(it, end);
    }

    string result = doEncode ? quotedPrintableEncode(input)
        : quotedPrintableDecode(input);

    if (!outFile.empty())
        writeFile(outFile, result);
    else
        cout << result << (result.empty() || result.back() != '\n' ? "\n" : "");

    return 0;
}