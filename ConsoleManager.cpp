#include "AConsole.h"
#include "ConsoleManager.h"
#include <iostream>
#include <memory>
#include <string>


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

// TODO: Change process from string to actual process
bool ConsoleManager::newConsole(Process_ process, AConsole_ console) {
    if (this->_consoleMap.find(*process) != this->_consoleMap.end()) {
        std::cout << "Process '" + *process + "' is already running!" << std::endl;
        return false;
    }

    if (console == nullptr)
        this->_consoleMap[*process] = std::make_shared<AConsole>(process);
    else
        this->_consoleMap[*process] = console;

    return true;
}

void ConsoleManager::switchConsole(std::string processName) {
    if (this->_consoleMap.find(processName) == this->_consoleMap.end()) {
        std::cout << "No process found with the name " + processName << std::endl;
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
    this->_mainConsole = std::make_shared<AConsole>(std::make_shared<std::string>("Main"));
    this->_current = this->_mainConsole;
    this->_current->run();
}

ConsoleManager::~ConsoleManager() {}
