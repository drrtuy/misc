#include <wchar.h>
#include <stdio.h>
#include <locale.h>

#include "module.h"

int main ()
{

    wchar_t buf[BUF_LEN + 1], crypted[BUF_LEN + 1];
#ifdef _WIN32
    SetConsoleOutputCP(65001); //set default Windows cmd output to UTF-8
    SetConsoleCP(65001);
#endif
#ifdef linux
    setlocale(LC_ALL, "");
#endif

#ifdef _WIN32
    printf("%s\n", "Введите строку:");
#endif
#ifdef linux
    printf("%ls\n", L"Введите строку:");
#endif

    fgetws(buf, BUF_LEN + 1, stdin);
    crypt(crypted, (const wchar_t *) buf);

#ifdef _WIN32
    printf("%s: %s\n", "Шифр: ", crypted);
#endif
#ifdef linux
    printf("%ls: %ls\n", L"Шифр: ", crypted);
#endif

    return 0;
}
