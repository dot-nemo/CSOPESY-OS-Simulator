#pragma once
#ifndef CONSOLEMANAGER_H
#define CONSOLEMANAGER_H

#include "AConsole.h"
#include <chrono>
#include <memory>
#include <string>
#include <unordered_map>



typedef std::shared_ptr<std::string> Process_;
typedef std::shared_ptr<AConsole> AConsole_;

class ConsoleManager {
public:
    static ConsoleManager* get();
    static void initialize();
    static void destroy();

    bool newConsole(Process_ process, AConsole_ console = nullptr);
    void switchConsole(std::string processName);

private:
    ConsoleManager();
    ~ConsoleManager();

    static ConsoleManager* ptr;
    std::unordered_map<std::string, AConsole_> _consoleMap;
    AConsole_ _current = nullptr;
    AConsole_ _mainConsole = nullptr;
};

#endif // !CONSOLEMANAGER_H

