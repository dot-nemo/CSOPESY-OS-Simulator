#include "Memory.h"
#include "MemoryManager.h"
#include <string>
#include <iostream>

MemoryManager::MemoryManager(int maxMemory) : _maxMemory(maxMemory) {
	this->_head = new MemoryBlock();
	MemoryBlock* currentBlock = this->_head;
	for (int i = 1; i < maxMemory; i++) {
		currentBlock->next = new MemoryBlock();
		currentBlock = currentBlock->next;
	}
}

bool MemoryManager::allocate(std::string process, int requiredMem) {
	MemoryBlock* currentBlock = this->_head;
	int ctr = 0;
	for (int i = 0; i < this->_maxMemory; i++) {
		if (currentBlock != nullptr && currentBlock->is_free) {
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
				currentBlock->is_free = false;
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
	for (int i = 0; i < this->_maxMemory; i++) {
		if (currentBlock->process == process) {
			currentBlock->is_free = true;
			currentBlock->process = "";
		}
		currentBlock = currentBlock->next;
		if (currentBlock->is_free) break;
	}
}

void MemoryManager::printMem() {
	MemoryBlock* currentBlock = this->_head;
	for (int i = 0; i < this->_maxMemory; i++) {
		std::cout << i
			<< "\t" << currentBlock->is_free
			<< " " << currentBlock->process
			<< std::endl;
		currentBlock = currentBlock->next;
	}
}
