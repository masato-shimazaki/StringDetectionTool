#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <locale.h>

int func(FILE *fp, std::map<wchar_t, wchar_t> &map);

int main(int argc, char *args[])
{
    if (argc <= 1)
    {
        return -1;
    }

    std::string out_filename;
    std::vector<std::string> ipts;

    for (int i = 1; i < argc; i++)
    {
        std::string str = args[i];
        for (size_t space = str.find_first_of(" "); space != std::string::npos; space = str.find_first_of(" "))
        {
            str.erase(space, 1);
        }

        std::cout << str << std::endl;

        std::string name = str.substr(2, str.length());

        std::string prefix = str.substr(0, 2);

        if (prefix.find("-o") != std::string::npos)
        {
            out_filename = name;
        }

        if (prefix.find("-i") != std::string::npos)
        {
            ipts.push_back(name);
        }
    }

    setlocale(LC_CTYPE, "ja_JP.UTF-8");

    FILE *out_fp = fopen(out_filename.c_str(), "w+");
    if (out_fp == NULL)
    {
        return -1;
    }

    std::map<wchar_t, wchar_t> map;

    for (int i = 0; i < ipts.size(); i++)
    {
        FILE *fp = fopen(ipts.at(i).c_str(), "r");
        if (fp == NULL)
        {
            continue;
        }

        func(fp, map);
        fclose(fp);
    }

    std::string str;

    for (std::map<wchar_t, wchar_t>::iterator it = map.begin(); it != map.end(); it++)
    {
        char chr[8];
        memset(chr, 0, sizeof(chr));

        wcstombs(chr, &it->second, sizeof(chr));
        std::cout << &it->second << std::endl;

        for (int i = 0; i < sizeof(chr); i++)
        {
            if (chr[i] == 0)
            {
                break;
            }
            putc(chr[i], out_fp);
        }
    }

    fclose(out_fp);

    return 0;
}

int func(FILE *fp, std::map<wchar_t, wchar_t> &map)
{
    const char cr = '\r';
    wchar_t CR;
    mbstowcs(&CR, &cr, sizeof(CR));

    const char lf = '\n';
    wchar_t LF;
    mbstowcs(&LF, &lf, sizeof(LF));

    char buff[1024];
    while (fgets(buff, sizeof(buff), fp) != NULL)
    {
        wchar_t wbuff[1024];
        memset(wbuff, 0, sizeof(wbuff));
        int result = mbstowcs(wbuff, buff, sizeof(buff));

        for (int i = 0; i < result; i++)
        {
            wchar_t wc = wbuff[i];

            if (map.find(wc) != map.end())
            {
                continue;
            }

            if (wc == CR || wc == LF)
            {
                continue;
            }
            map.insert(std::make_pair(wc, wc));
        }
    }
    return 0;
}