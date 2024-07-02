#pragma once
#ifndef MAINCONSOLE_H
#define MAINCONSOLE_H

#include "AConsole.h"
#include <memory>
#include <string>


class MainConsole : public AConsole {
public:
    MainConsole() : AConsole(std::make_shared<std::string>("MAIN_CONSOLE")) {};
    ~MainConsole() = default;
    void run() override;
    void stop() override;

private:
    void draw() override;
    void printHeader();
};

#endif // !MAINCONSOLE_H