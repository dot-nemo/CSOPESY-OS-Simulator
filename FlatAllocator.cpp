
#include "FlatAllocator.h"
#include "Process.h"

#include <ctime>
#include <iostream>
#include <memory>
#include <string>


FlatAllocator::FlatAllocator(int maxMemory) : _maxMemory(maxMemory) {
	this->_head = new MemoryBlock();
	MemoryBlock* currentBlock = this->_head;
	for (int i = 1; i < this->_maxMemory; i++) {
		currentBlock->next = new MemoryBlock();
		currentBlock = currentBlock->next;
	}
}

bool FlatAllocator::allocate(std::shared_ptr<Process> process) {
	std::string processName = process->getName();
	int requiredMem = process->getRequiredMemory();
	MemoryBlock* currentBlock = this->_head;
	int ctr = 0;
	for (int i = 0; i < this->_maxMemory; i++) {
		if (currentBlock != nullptr && currentBlock->isFree) {
			ctr++;
		}
		else {
			ctr = 0;
		}
		if (ctr == requiredMem) {
			currentBlock = this->_head;
			for (int j = 0; j < i - requiredMem + 1; j++) {
				currentBlock = currentBlock->next;
			}
			for (int j = 0; j < requiredMem; j++) {
				currentBlock->process = processName;
				currentBlock->isFree = false;
				currentBlock = currentBlock->next;
			}
			return true;
		}
		currentBlock = currentBlock->next;
	}
	return false;
}

void FlatAllocator::deallocate(std::shared_ptr<Process> process) {
	std::string processName = process->getName();
	MemoryBlock* currentBlock = this->_head;
	for (int i = 0; i < this->_maxMemory; i++) {
		if (currentBlock->process == processName) {
			currentBlock->isFree = true;
			currentBlock->process = "";
			if (currentBlock->next->process != processName) break;
		}
		currentBlock = currentBlock->next;
	}
}

void FlatAllocator::printMem() {
	auto timestamp = time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &timestamp);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "Timestamp: (%D %r)", &timeInfo);

	int uniqueCtr = 0;
	int externalFragmentation = 0;
	std::string lastProcess = "";
	std::string output = "----start---- = 0";

	MemoryBlock* currentBlock = this->_head;
	for (int i = 0; i < this->_maxMemory; i++) {
		if (currentBlock->process != "") {
			if (!currentBlock->isFree && currentBlock->process != lastProcess) {
				lastProcess = currentBlock->process;
				uniqueCtr++;
				output = std::to_string(i) + "\n\n" + output;
			}
			if (currentBlock->next == nullptr || currentBlock->next->process != lastProcess) {
				output = std::to_string(i + 1) + "\n" + lastProcess + "\n" + output;
			}
		}
		else {
			externalFragmentation++;
		}
		currentBlock = currentBlock->next;
	}

	output = std::string(buffer) + "\n"
		+ "Number of processes in memory: " + std::to_string(uniqueCtr) + "\n"
		+ "Total external fragmentation in KB: " + std::to_string(externalFragmentation) + "\n"
		+ "\n"
		+ "-----end----- = " + std::to_string(this->_maxMemory) + "\n"
		+ "\n"
		+ output;
	std::cout << output << std::endl;
}
