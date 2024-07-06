#include "Scheduler.h"

#include <ctime>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "CPU.h"
#include "Process.h"

Scheduler::Scheduler() {

}

Scheduler* Scheduler::_ptr = nullptr;

Scheduler* Scheduler::get() {
	return _ptr;
}

void Scheduler::initialize(int cpuCount) {
    _ptr = new Scheduler();
    for (int i = 0; i < cpuCount; i++) {
        _ptr->_cpuList.push_back(std::make_shared<CPU>());
    }
}

void Scheduler::startFCFS() {
	if (this->running == false) {
		this->running = true;
		std::thread t(&Scheduler::runFCFS, this);
		t.detach();
	}
}
void Scheduler::startSJF() {
    if (this->running == false) {
        this->running = true;
        std::thread t(&Scheduler::runSJF, this);
        t.detach();
    }
}

void Scheduler::startRR() {
    if (this->running == false) {
        this->running = true;
        std::thread t(&Scheduler::runRR, this);
        t.detach();
    }
}

void Scheduler::stop() {
	this->running = false;
}

void Scheduler::destroy() {
	delete _ptr;
}

void Scheduler::addProcess(Process process) {
	this->_readyQueue.push(std::make_shared<Process>(process));
}

void Scheduler::printStatus() {

}

void Scheduler::schedulerTest(float batchProcessFreq, int minIns, int maxIns) {

}

void Scheduler::runFCFS(float delay) { // FCFS
    while (this->running) {
        this->running = false;
        for (int i = 0; i < this->_cpuList.size(); i++) {
            std::shared_ptr<CPU> cpu = this->_cpuList.at(i);
            if (cpu->isReady()) {
                if (this->_readyQueue.size() > 0) {
                    cpu->setProcess(this->_readyQueue.front());
                    this->_readyQueue.pop();
                    this->running = true;
                }
            }
            else {
                if (this->running == false) {
                    std::chrono::duration<float> duration(delay);
                    std::this_thread::sleep_for(duration);
                    this->running = true;
                }
            }
        }
    }
}

void Scheduler::runSJF(float delay, bool preemptive) {

}

void Scheduler::runRR(float delay, int quantumCycles) {

}



