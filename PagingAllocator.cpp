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
	int requiredMem = Process::setRequiredMemory(-1, -1);
	for (size_t i = 0; i < maxMemory / (requiredMem / Process::getRequiredPages()); i++) {
		_freeFrameList.push(i);
	}
}

bool PagingAllocator::allocate(std::shared_ptr<Process> process) {
	int requiredMem = Process::setRequiredMemory(0, 0);
	int requiredPages = Process::getRequiredPages();
	int pageSize = requiredMem / requiredPages;
	if (_pageTable.find(process->getName()) != _pageTable.end()) {
		for (size_t i = 0; i < _pageTable[process->getName()].size(); i++) {
			if (_pageTable[process->getName()].at(i) < 0) {
				int nextFrame = _freeFrameList.front();
				_freeFrameList.pop();
				_pageTable[process->getName()].at(i) = nextFrame;
			}
		}
		return true;
	}
	if (_freeFrameList.size() >= requiredPages) {
		for (size_t i = 0; i < requiredPages; i++) {
			int nextFrame = _freeFrameList.front();
			_freeFrameList.pop();
			_pageTable[process->getName()].push_back(nextFrame);
		}
		return true;
	}
	return false;
}

void PagingAllocator::deallocate(std::shared_ptr<Process> process) {
	if (_pageTable.find(process->getName()) != _pageTable.end()) {
		for (size_t i = 0; i < _pageTable[process->getName()].size(); i++) {
			_freeFrameList.push(_pageTable[process->getName()].at(i));
		}
		_pageTable.erase(_pageTable.find(process->getName()));
	}
}

void PagingAllocator::printMem() {
	auto timestamp = time(nullptr);
	struct tm timeInfo;
	localtime_s(&timeInfo, &timestamp);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "Timestamp: (%D %r)", &timeInfo);

	int requiredMem = Process::setRequiredMemory(0, 0);
	int requiredPages = Process::getRequiredPages();
	int pageSize = requiredMem / requiredPages;

	std::vector<std::string> memProcNames;
	std::vector<int> memFrameIdx;

	for (auto it = _pageTable.begin(); it != _pageTable.end(); ++it) {
		std::string process = it->first;
		for (size_t i = 0; i < it->second.size(); i++) {
			if (it->second.at(i) != -1) {
				int insertIdx = 0;
				for (size_t j = 0; j < memFrameIdx.size(); j++) {
					if (memFrameIdx.at(j) > it->second.at(i)) {
						insertIdx = j;
						break;
					}
				}
				memFrameIdx.insert(memFrameIdx.begin() + insertIdx, it->second.at(i));
				memProcNames.insert(memProcNames.begin() + insertIdx, process);
			}
		}
	}
	std::cout << std::string(buffer) + "\n"
		+ "Number of processes in memory: " + std::to_string(_pageTable.size()) + "\n"
		+ "Total external fragmentation in KB: " + std::to_string(this->_maxMemory - memFrameIdx.size() * pageSize) + "\n"
		+ "\n"
		+ "-----end----- = " + std::to_string(this->_maxMemory) + "\n"
		+ "\n";
	for (size_t i = 0; i < memFrameIdx.size(); i++) {
		std::cout << std::to_string((memFrameIdx.at(i) + 1) * pageSize) << std::endl
			<< memProcNames.at(i) << std::endl
			<< std::to_string(memFrameIdx.at(i) * pageSize)
			<< std::endl << std::endl;
	}
	std::cout << "----start---- = 0" << std::endl; 
}

void PagingAllocator::printProcesses() {
	int requiredMem = Process::setRequiredMemory(0, 0);
	int requiredPages = Process::getRequiredPages();
	int pageSize = requiredMem / requiredPages;

	std::vector<std::string> memProcNames;
	std::vector<int> memFrameIdx;

	for (auto it = _pageTable.begin(); it != _pageTable.end(); ++it) {
		std::string process = it->first;
		memProcNames.push_back(process);
	}

	std::cout << "Memory Usage: " << this->_pageTable.size() * requiredMem << " / " << this->_maxMemory << std::endl;

	std::cout << "Memory Util: " << (1.0 * (this->_pageTable.size() * requiredMem) / this->_maxMemory) * 100 << "%" << std::endl;

	std::cout << std::endl;

	for (int i = 0; i < 48; i++) {
		std::cout << "=";
	}
	std::cout << std::endl;

	std::cout << "Running processes and memory usage: " << std::endl;

	for (int i = 0; i < 48; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < memProcNames.size(); i++)
	{
		std::cout << memProcNames[i] << " " << requiredPages * pageSize << std::endl;
	}
}

void PagingAllocator::vmstat() {
}
