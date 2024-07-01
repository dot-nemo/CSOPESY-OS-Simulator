#pragma once
#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "ICommand.h"
#include <ostream>
#include <string>


class PrintCommand : public ICommand {
public:
    PrintCommand(std::string string, int pid, std::string outputFileName = "");
    ~PrintCommand() = default;

    void execute(int core) override;

//private:
    int _pid;
    CommandType _type = PRINT;

    std::string _string;
    std::string _outputFileName;
};

#endif // !PRINTCOMMAND_H