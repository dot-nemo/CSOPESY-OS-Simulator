#pragma once
#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <string>
#include <unordered_map>


struct MemoryBlock {
    std::string process = "";
    bool isFree = true;
    MemoryBlock* next;
};

class MemoryManager {
public:
    MemoryManager(int maxMemory);
    ~MemoryManager() = default;

    bool allocate(std::string process, int requiredMem);
    void deallocate(std::string process);
    
    void printMem();

private:
    int _maxMemory;
    MemoryBlock* _head;
};

#endif // !MEMORYMANAGER_H