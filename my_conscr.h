#ifndef MY_CONSCR_H_
#define MY_CONSCR_H_
/** Demo console screen functions **/
/** conscr.h dosyasi **/
#include <windows.h>
#include <stdio.h>

void cursorvisible(int c)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 10;
   info.bVisible = (c)?TRUE:FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
void clrscr()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); 
    COORD coord = {0, 0}; 
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi); 
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);  
}

void getxy(SHORT *x, SHORT *y)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); 
	*x=csbi.dwCursorPosition.X;
	*y=csbi.dwCursorPosition.Y;
}
void gotoxy (int x, int y)
{
    COORD coord; 
    coord.X = x; coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void settextattr(WORD attr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
}
#endif // MY_CONSCR_H_


