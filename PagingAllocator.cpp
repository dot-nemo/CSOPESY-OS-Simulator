#include "PagingAllocator.h"
#include "Process.h"

#include <cstdlib> 
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <queue>


#define PAGE_SIZE 4;

PagingAllocator::PagingAllocator(int maxMemory) : _maxMemory(maxMemory) {
	std::ofstream backingStoreFile(".pagefile", std::ios::trunc);
	backingStoreFile.close();
	for (size_t i = 0; i < maxMemory / Process::getRequiredPages(); i++) {
		_freeFrameList.push(i);
	}
}

bool PagingAllocator::allocate(std::shared_ptr<Process> process) {
	//int requiredMem = Process::setRequiredMemory(0, 0);
	//int requiredPages = Process::getRequiredPages();
	//int pageSize = requiredMem / requiredPages;
	//for (size_t i = 0; i < requiredPages; i++) {
	//	if (_freeFrameList.size() >= requiredPages)

	//}
 //   return true;
}

void PagingAllocator::deallocate(std::shared_ptr<Process> process) {
}

void PagingAllocator::printMem() {
	auto timestamp = time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &timestamp);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "Timestamp: (%D %r)", &timeInfo);

	int uniqueCtr = this->_memory.size();
	int externalFragmentation = 0;
	std::string lastProcess = "";
	std::string output = "----start---- = 0";
	int total = 0;
	for (size_t i = 0; i < this->_memory.size(); i++) {
		output = std::to_string(std::get<0>(this->_memory.at(i).second)) + "\n\n" + output;
		output = std::to_string(std::get<1>(this->_memory.at(i).second)) + "\n" + this->_memory.at(i).first->getName() + " " + std::to_string(std::get<2>(this->_memory.at(i).second)) + "\n" + output;
		total += std::get<1>(this->_memory.at(i).second) - std::get<0>(this->_memory.at(i).second);
	}

	output = std::string(buffer) + "\n"
		+ "Number of processes in memory: " + std::to_string(uniqueCtr) + "\n"
		+ "Total external fragmentation in KB: " + std::to_string(this->_maxMemory - total) + "\n"
		+ "\n"
		+ "-----end----- = " + std::to_string(this->_maxMemory) + "\n"
		+ "\n"
		+ output;
	std::cout << output << std::endl;
}