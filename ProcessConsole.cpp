#include "ProcessConsole.h"
#include <iostream>

ProcessConsole::ProcessConsole(std::shared_ptr<Process> process) : 
    AConsole(std::make_shared<std::string>(process->getName())), 
    _process(process) {
}

void ProcessConsole::run() {
    this->_active = true;
	std::string input;
    while (this->_active) {
		std::cout << "root:\\> ";
		std::getline(std::cin, input);
		if (input == "exit") {
			this->stop();
			return;
		}
		if (input == "process-smi") {
			this->draw();
		}
		else {
			std::cout << input << " not recognized." << std::endl;
		}
    }
}

void ProcessConsole::stop() {
    this->_active = false;
}

void ProcessConsole::draw() {
	std::cout << "Process: " << this->_process->getName() << std::endl
		<< "ID: " << this->_process->getID() << std::endl
		<< std::endl
		<< "Current instruction line: " << this->_process->getCommandCounter() << std::endl
		<< "Lines of code: " << this->_process->getCommandListSize() << std::endl
		<< std::endl;
}