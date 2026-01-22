#include "ioHandler.h"
#include <iostream>
using namespace std;

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdio.h>
#endif

#ifdef _WIN32
    const int KEY_UP = 72, KEY_DOWN = 80, KEY_ENTER = 13, KEY_ESC = 27;
#else
    const int KEY_UP = 65, KEY_DOWN = 66, KEY_ENTER = 10, KEY_ESC = 27;
#endif

void initTerminal() {
#ifdef _WIN32
    // 윈도우: 커서 숨기기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#else
    // 맥/리눅스: 대체 버퍼 진입 (\033[?1049h), 커서 숨기기 (\033[?25l)
    cout << "\033[?1049h\033[?25l" << flush;
#endif
}

void restoreTerminal() {
#ifdef _WIN32
    // 윈도우: 커서 다시 보이기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
#else
    // 맥/리눅스: 기본 버퍼 복귀 (\033[?1049l), 커서 보이기 (\033[?25h)
    cout << "\033[?1049l\033[?25h" << flush;
#endif
}

int getKeyPress() {
#ifdef _WIN32
    int ch = _getch();
    // 윈도우 방향키는 0 또는 224가 선행됨
    if (ch == 0 || ch == 224) return _getch();
    return ch;
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    if (ch == 27) { // ESC 또는 시퀀스 시작
        int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        int n2 = getchar();
        if (n2 != -1) { // 뒤에 데이터가 더 있다면 (방향키 등)
            int n3 = getchar();
            if (n3 != -1) ch = n3; 
        }
        // 데이터가 없다면 ch는 그대로 27 유지 (ESC)
        fcntl(STDIN_FILENO, F_SETFL, oldf);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // 화면 지우고 커서를 1,1 위치로 이동
    cout << "\033[2J\033[1;1H" << flush;
#endif
}