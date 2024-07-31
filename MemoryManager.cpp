#include "MemoryManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

int MemoryManager::maxMemory = 0;

MemoryManager::MemoryManager() {
	this->_head = new MemoryBlock();
	MemoryBlock* currentBlock = this->_head;
	for (int i = 1; i < MemoryManager::maxMemory; i++) {
		currentBlock->next = new MemoryBlock();
		currentBlock = currentBlock->next;
	}
}

bool MemoryManager::allocate(std::string process, int requiredMem) {
	MemoryBlock* currentBlock = this->_head;
	int ctr = 0;
	for (int i = 0; i < MemoryManager::maxMemory; i++) {
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
				currentBlock->process = process;
				currentBlock->isFree = false;
				currentBlock = currentBlock->next;
			}
			return true;
		}
		currentBlock = currentBlock->next;
	}
    return false;
}

void MemoryManager::deallocate(std::string process) {
	MemoryBlock* currentBlock = this->_head;
	for (int i = 0; i < MemoryManager::maxMemory; i++) {
		if (currentBlock->process == process) {
			currentBlock->isFree = true;
			currentBlock->process = "";
			if (currentBlock->next->process != process) break;
		}
		currentBlock = currentBlock->next;
	}
}

void MemoryManager::setMaxMemory(int maxMemory) {
	MemoryManager::maxMemory = maxMemory;
}

void MemoryManager::printMem(int qq) {
	// TODO: MAKE THIS PRINT TO A FILE

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
	for (int i = 0; i < MemoryManager::maxMemory; i++) {
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
		+ "-----end----- = " + std::to_string(MemoryManager::maxMemory) + "\n"
		+ "\n"
		+ output;
	std::cout << output << std::endl;
}
