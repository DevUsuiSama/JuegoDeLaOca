#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#ifndef _WINDOWS_H
#include <windows.h>
#endif // !_WINDOWS_H
#ifndef _TCHAR_H_
#include <tchar.h>
#endif // !_TCHAR_H_

void limpiar_terminal()
{
    COORD cordenada;
    DWORD escritura;
    CONSOLE_SCREEN_BUFFER_INFO info;

    cordenada.X = 0;
    cordenada.Y = 0;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), _T(' '), info.dwSize.X * info.dwSize.Y, cordenada, &escritura);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cordenada);
}

#endif // !__TERMINAL_H__