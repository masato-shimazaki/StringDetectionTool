#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <locale.h>
#include <cstring>

int processFile(FILE *fp, std::map<wchar_t, wchar_t> &charMap);

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Usage: " << argv[0] << " -o output_filename -i input_filename(s)" << std::endl;
        return -1;
    }

    std::string outputFilename;
    std::vector<std::string> inputFiles;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        arg.erase(std::remove(arg.begin(), arg.end(), ' '), arg.end());

        std::cout << arg << std::endl;

        std::string name = arg.substr(2);
        std::string prefix = arg.substr(0, 2);

        if (prefix == "-o")
        {
            outputFilename = name;
        }
        else if (prefix == "-i")
        {
            inputFiles.push_back(name);
        }
    }

    if (setlocale(LC_CTYPE, "ja_JP.UTF-8") == NULL)
    {
        std::cerr << "Failed to set locale to ja_JP.UTF-8" << std::endl;
        return -1;
    }

    FILE *outFp = fopen(outputFilename.c_str(), "w+");
    if (outFp == NULL)
    {
        std::cerr << "Failed to open output file: " << outputFilename << std::endl;
        return -1;
    }

    std::map<wchar_t, wchar_t> charMap;

    for (const auto &inputFile : inputFiles)
    {
        FILE *fp = fopen(inputFile.c_str(), "r");
        if (fp == NULL)
        {
            std::cerr << "Failed to open input file: " << inputFile << std::endl;
            continue;
        }

        processFile(fp, charMap);
        fclose(fp);
    }

    for (const auto &pair : charMap)
    {
        char mbStr[9] = {0};
        wcstombs(mbStr, &pair.second, sizeof(mbStr));
        fputs(mbStr, outFp);
    }

    fclose(outFp);
    return 0;
}

int processFile(FILE *fp, std::map<wchar_t, wchar_t> &charMap)
{
    const wchar_t CR = L'\r';
    const wchar_t LF = L'\n';

    char buffer[1024] = {0};
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        wchar_t wbuffer[1024] = {0};
        int length = mbstowcs(wbuffer, buffer, sizeof(buffer) / sizeof(char));

        for (int i = 0; i < length; ++i)
        {
            wchar_t wc = wbuffer[i];

            if (wc == CR || wc == LF || charMap.count(wc))
            {
                continue;
            }

            charMap[wc] = wc;
        }
    }
    return 0;
}
