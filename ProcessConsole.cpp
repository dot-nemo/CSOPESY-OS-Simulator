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
		this->_history += "root:\\> " + input + "\n";
		if (input == "exit") {
			this->stop();
			return;
		}
		if (input == "process-smi") {
			this->draw();
			continue;
		}
		if (input == "") {
			continue;
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
	std::string info = "Process: " + this->_process->getName() + "\n"
		+ "ID: " + std::to_string(this->_process->getID()) + "\n"
		+ "\n"
		+ "Current instruction line: " + std::to_string(this->_process->getCommandCounter()) + "\n"
		+ "Lines of code: " + std::to_string(this->_process->getCommandListSize()) + "\n"
		+ "\n";
	std::cout << info;
	this->_history += info;
}