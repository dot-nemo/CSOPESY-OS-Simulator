#include "MemoryManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <memory>
#include "Process.h"
#include "FlatAllocator.h"

MemoryManager::MemoryManager(int maxMemory, int minPage, int maxPage) {
	if (minPage == maxPage == 1) {
		this->_allocator = new FlatAllocator(maxMemory);
	}
	else {
		
	}
}

bool MemoryManager::allocate(std::shared_ptr<Process> process) {
	return this->_allocator->allocate(process);
}

void MemoryManager::deallocate(std::shared_ptr<Process> process) {
	this->_allocator->deallocate(process);
}
void MemoryManager::printMem(int qq) {
	this->_allocator->printMem();
}
