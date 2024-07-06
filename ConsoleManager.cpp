#include "AConsole.h"
#include "ConsoleManager.h"
#include <iostream>
#include <memory>
#include <string>
#include "MainConsole.h"


ConsoleManager* ConsoleManager::ptr = nullptr;

ConsoleManager* ConsoleManager::get() {
    return ConsoleManager::ptr;
}

void ConsoleManager::initialize() {
    ConsoleManager::ptr = new ConsoleManager();
}

void ConsoleManager::destroy() {
    ConsoleManager::ptr = nullptr;
}

void ConsoleManager::start() {
    this->_current->run();
}

bool ConsoleManager::newConsole(std::string name, AConsole_ console) {
    if (this->_consoleMap.find(name) != this->_consoleMap.end()) {
        std::cout << "Process '" + name + "' is already running!" << std::endl;
        return false;
    }

    if (console == nullptr)
        this->_consoleMap[name] = std::make_shared<AConsole>(name);
    else
        this->_consoleMap[name] = console;

    return true;
}

void ConsoleManager::switchConsole(std::string processName) {
    if (this->_consoleMap.find(processName) == this->_consoleMap.end()) {
        std::cout << "Process " + processName + " not found." << std::endl;
        return;
    }

    this->_current->stop();

    this->_current = this->_consoleMap[processName];
    this->_current->run();
        
    // Wait for console to set active to false
    while (this->_current->isActive()) {}

    this->_current = this->_mainConsole;
    this->_current->run();
}

ConsoleManager::ConsoleManager() {
    this->_mainConsole = std::make_shared<MainConsole>(MainConsole(this));
    this->_current = this->_mainConsole;
}

ConsoleManager::~ConsoleManager() {}
