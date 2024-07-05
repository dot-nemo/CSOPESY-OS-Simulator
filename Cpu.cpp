#include "CPU.h"

#include "Process.h"

#include <memory>
#include <thread>


int CPU::nextID = 0;

CPU::CPU() {
    this->_id = CPU::nextID;
    CPU::nextID++;
    std::thread tickThread(&CPU::run, this);
    tickThread.detach();
}

void CPU::setProcess(std::shared_ptr<Process> process) {
    this->_process = process;
    this->_ready = false;
}

void CPU::run() {
    while (true) {
        if (this->_process != nullptr) {
            this->_process->setCPUCoreID(this->_id);
            this->_process->execute();
            if (this->_process->hasFinished()) {
                this->setProcess(nullptr);
                this->_ready = true;
            }
        }
    }
}