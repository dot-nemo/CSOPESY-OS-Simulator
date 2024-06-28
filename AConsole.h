#pragma once
#ifndef ACONSOLE_H

#include <memory>
#include <string>
#include <tuple>


class AConsole {
public:
    AConsole(std::shared_ptr<std::string> process);
    ~AConsole() = default;

    bool isActive() { return this->_active; }

    virtual void run();
    virtual void stop();

protected:
    virtual void draw();
    void SetCursorPosition(short row, short col);
    void DrawHorizontalLine(short row, short col, short length, bool two = false);
    void DrawVerticalLine(short row, short col, short length);
    void PrintAtCoords(short row, short col, std::string string, short length = -1, bool right = false);
    void FillCorners(short topRow, short leftCol, short width, short height);
    void DrawBox(short topRow, short leftCol, short width, short height, bool two = false);
    std::tuple<short, short> getWindowSize();

    std::shared_ptr<std::string> _process;

    bool _active = false;
};

#endif // !ACONSOLE_H

