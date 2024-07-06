#include "AConsole.h"

#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <windows.h>
#include <tuple>

AConsole::AConsole(std::string name) {
    this->_name = name;
}

void AConsole::run() {
    std::cout << "Starting " + this->_name << std::endl;
    this->_active = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(25));
    this->stop();
}

void AConsole::stop() {
    if (this->_active) {
        this->_active = false;
        std::cout << "Stopping " + this->_name << std::endl;
    }
}

void AConsole::draw() {
    std::cout << this->_name << std::endl;
    std::tuple<short, short> temp = this->getWindowSize();
    std::cout << std::get<0>(temp) << " " << std::get<1>(temp) << std::endl;
}

void AConsole::SetCursorPosition(short row, short col) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { col, row };
    SetConsoleCursorPosition(handle, coord);
}

void AConsole::DrawHorizontalLine(short row, short col, short length, bool two) {
    SetCursorPosition(row, col);
    char c = two ? '=' : '-';
    for (short i = 0; i < length; i++) {
        std::cout << c;
    }
}

void AConsole::DrawVerticalLine(short row, short col, short length) {
    for (short i = 0; i < length; i++) {
        SetCursorPosition(row + i, col);
        std::cout << '|';
    }
}

void AConsole::PrintAtCoords(short row, short col, std::string string, short length, bool right) {
    SetCursorPosition(row, col);
    if (length != -1)
        if (right)
            printf("%-*s", length, string.c_str());
        else
            printf("%*s", length, string.c_str());
    else
        std::cout << string;
}

void AConsole::FillCorners(short topRow, short leftCol, short width, short height) {
    width -= 1;
    height -= 1;
    PrintAtCoords(topRow, leftCol, "+");
    PrintAtCoords(topRow, leftCol + width, "+");
    PrintAtCoords(topRow + height, leftCol, "+");
    PrintAtCoords(topRow + height, leftCol + width, "+");
}

void AConsole::DrawBox(short topRow, short leftCol, short width, short height, bool two) {
    width -= 1;
    height -= 1;
    if (width != 0) {
        DrawHorizontalLine(topRow, leftCol, width, two);
        DrawHorizontalLine(topRow + height, leftCol, width, two);
    }
    if (height != 0) {
        DrawVerticalLine(topRow, leftCol, height);
        DrawVerticalLine(topRow, leftCol + width, height);
    }
    FillCorners(topRow, leftCol, width + 1, height + 1);
}

std::tuple<short, short> AConsole::getWindowSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    short width, height;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return std::make_tuple(width, height);
}