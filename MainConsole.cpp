#include "AConsole.h"
#include "ConsoleManager.h"
#include "MainConsole.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#define SPACE " "


MainConsole::MainConsole(ConsoleManager* conman) : AConsole("MAIN_CONSOLE") {
	// SCREEN
	this->_commandMap["screen"] = [conman](argType arguments) { 
		if (arguments.size() > 2) {
			std::cout << "Too many strings!" << std::endl;
			return;
		}
		if (arguments.size() == 1) {
			std::cout << "No process specified." << std::endl;
			return;
		}
		if (arguments.size() == 0) {
			std::cout << "TODO: help for screen" << std::endl;
			return;
		}
		if (arguments.at(0) == "-s") {
			conman->switchConsole(arguments.at(1));
		}
	};
	this->_commandMap["marquee"] = [conman](argType arguments) {
		conman->switchConsole("MARQUEE_CONSOLE");
	};
}

void MainConsole::run() {
	system("cls");
    this->_active = true;
	std::string input;
	this->printHeader();
    while (this->_active) {
		std::cout << "root:\\> ";
		std::getline(std::cin, input);
		std::string command = input.substr(0, input.find(SPACE));
		input.erase(0, input.find(SPACE) + 1);
		if (command == "exit") {
			this->stop();
			return;
		}
		if (this->_commandMap.find(command) == this->_commandMap.end())
			std::cout << "'" << command << "' is not recognized." << std::endl;
		else {
			std::stringstream tokens(input);
			std::vector<std::string> arguments;
			std::string token;
			while (std::getline(tokens, token, ' ')) {
				arguments.push_back(token);
			}
			this->_commandMap[command](arguments);
		}
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