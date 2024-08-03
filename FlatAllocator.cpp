
#include "FlatAllocator.h"
#include "Process.h"

#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <cstdlib> 
#include <fstream>
#include <unordered_map>
#include <sstream>


FlatAllocator::FlatAllocator(int maxMemory) : _maxMemory(maxMemory) {
	std::ofstream backingStoreFile(".pagefile", std::ios::trunc);
	backingStoreFile.close();
}

bool FlatAllocator::allocate(std::shared_ptr<Process> process) {
	int requiredMem = process->getRequiredMemory();
	this->readBackingStore(process);
	if (this->_memory.size() == 0) {
		this->_memory.push_back(std::make_pair(process, std::make_pair(0, requiredMem)));
		return true;
	}
	else {
		for (size_t i = 0; i < this->_memory.size(); i++) {
			if (this->_memory.at(i).first->getName() == process->getName()) {
				return true;
			}
		}
		if (this->_memory.at(0).second.first >= requiredMem) {
			this->_memory.insert(this->_memory.begin(),
				std::make_pair(process,
					std::make_pair(0, requiredMem)));
			return true;
		}
		for (int retryLimit = 0; retryLimit < 5; retryLimit++) {
			int ctr = 0;
			int index = -1;
			for (size_t i = 0; i < this->_memory.size(); i++) {
				// check if blocks are not connected aka 0 space between
				if (i == this->_memory.size() - 1) {
					ctr = this->_maxMemory - this->_memory.at(i).second.second;
				}
				else {
					ctr = this->_memory.at(i + 1).second.first - this->_memory.at(i).second.second;
				}
				if (ctr >= requiredMem) {
					this->_memory.insert(this->_memory.begin() + i + 1,
						std::make_pair(process,
							std::make_pair(this->_memory.at(i).second.second,
								this->_memory.at(i).second.second + requiredMem)
						)
					);
					return true;
				}
			}
			if (this->_memory.size() > 0) {
				int randRemoveIdx = rand() % this->_memory.size();
				if (this->_memory.at(randRemoveIdx).first->getCPUCoreID() == -1) {
					this->writeBackingStore(this->_memory.at(randRemoveIdx).first);
					this->_memory.erase(this->_memory.begin() + randRemoveIdx);
				}
			}
		}
	}
	return false;
}

void FlatAllocator::deallocate(std::shared_ptr<Process> process) {
	this->readBackingStore(process);
	for (size_t i = 0; i < this->_memory.size(); i++) {
		if (this->_memory.at(i).first->getName() == process->getName()) {
			this->_memory.erase(this->_memory.begin() + i);
		}
	}
}

void FlatAllocator::printMem() {
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
		output = std::to_string(this->_memory.at(i).second.first) + "\n\n" + output;
		output = std::to_string(this->_memory.at(i).second.second) + "\n" + this->_memory.at(i).first->getName() + "\n" + output;
		total += this->_memory.at(i).second.second - this->_memory.at(i).second.first;
	}

	/*MemoryBlock* currentBlock = this->_head;
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
	}*/

	output = std::string(buffer) + "\n"
		+ "Number of processes in memory: " + std::to_string(uniqueCtr) + "\n"
		+ "Total external fragmentation in KB: " + std::to_string(this->_maxMemory - total) + "\n"
		+ "\n"
		+ "-----end----- = " + std::to_string(this->_maxMemory) + "\n"
		+ "\n"
		+ output;
	std::cout << output << std::endl;
}

void FlatAllocator::readBackingStore(std::shared_ptr<Process> process) {
	std::ifstream backingStoreFile(".pagefile");
	if (!backingStoreFile.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	std::unordered_map<std::string, std::pair<int, int>> backingStore;
	std::string line, key, ctr, mem;

	while (std::getline(backingStoreFile, line)) {
        std::istringstream iss(line);
        iss >> key >> ctr >> mem;
		backingStore[key] = std::make_pair(std::stoi(ctr), std::stoi(mem));
	}

	backingStoreFile.close();

	if (backingStore.find(process->getName()) != backingStore.end()) {
		backingStore.erase(backingStore.find(process->getName()));
	}

	std::ofstream saveFile(".pagefile", std::ios::trunc);

	if (saveFile.is_open()) {
		for (const auto& pair : backingStore) {
			saveFile << pair.first << ' ' << pair.second.first << ' ' << pair.second.second << '\n';
		}
		saveFile.close();
	}
}

void FlatAllocator::writeBackingStore(std::shared_ptr<Process> process) {
	std::ifstream backingStoreFile(".pagefile");
	if (!backingStoreFile.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return;
	}
	std::unordered_map<std::string, std::pair<int, int>> backingStore;
	std::string line, key, ctr, mem;

	while (std::getline(backingStoreFile, line)) {
		std::istringstream iss(line);
		iss >> key >> ctr >> mem;
		backingStore[key] = std::make_pair(std::stoi(ctr), std::stoi(mem));
	}

	backingStoreFile.close();

	if (backingStore.find(process->getName()) == backingStore.end()) {
		backingStore[process->getName()] = std::make_pair(process->getCommandCounter(),
			process->getRequiredMemory());
		std::ofstream saveFile(".pagefile", std::ios::trunc);

		if (saveFile.is_open()) {
			for (const auto& pair : backingStore) {
				saveFile << pair.first << ' ' << pair.second.first << ' ' << pair.second.second << '\n';
			}
			saveFile.close();
		}
	}
}
