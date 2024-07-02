#include "MainConsole.h"
#include <iostream>
#include <string>

#define SPACE " "


void MainConsole::run() {
    this->_active = true;
	std::string input;
    while (this->_active) {
		this->printHeader();
		std::cout << "Enter a command: ";
		std::getline(std::cin, input);
		std::string token = input.substr(0, input.find(SPACE));
		this->stop();
    }
}

void MainConsole::stop() {
    this->_active = false;
}

void MainConsole::draw() {
}

void MainConsole::printHeader() {
	std::cout << R"(   _____  _____  ____  _____  ______  _______     __)" << std::endl
		<< R"(  / ____|/ ____|/ __ \|  __ \|  ____|/ ____\ \   / /)" << std::endl
		<< R"( | |    | (___ | |  | | |__) | |__  | (___  \ \_/ / )" << std::endl
		<< R"( | |     \___ \| |  | |  ___/|  __|  \___ \  \   /  )" << std::endl
		<< R"( | |____ ____) | |__| | |    | |____ ____) |  | |   )" << std::endl
		<< R"(  \_____|_____/ \____/|_|    |______|_____/   |_|   )" << std::endl
		<< "Hello, Welcome to CSOPSY commandline!" << std::endl
		<< "Type 'exit' to quit, 'clear' to clear the screen" << std::endl;
}