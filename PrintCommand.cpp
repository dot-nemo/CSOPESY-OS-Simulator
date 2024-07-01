#include "PrintCommand.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>


PrintCommand::PrintCommand(std::string string, int pid, std::string outputFileName) {
    this->_string = string;
    this->_pid = pid;
    this->_outputFileName = outputFileName;
}

void PrintCommand::execute(int core) {
    if (this->_outputFileName == "") {
        std::cout << this->_string;
    }
    else {
        std::ofstream outputFile;
        outputFile.open(this->_outputFileName, std::ios::out | std::ios::app);

        // Output folder must exist
        if (outputFile.is_open()) {
            auto timestamp = time(nullptr);
            struct tm timeInfo;
            localtime_s(&timeInfo, &timestamp);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "(%D %r)", &timeInfo);

            outputFile << buffer << " "
                << "Core:" << core << " "
                << "\"" << this->_string << "\""
                << std::endl;
            outputFile.close();
        }
    }
}
