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
    MemoryManager();
    ~MemoryManager() = default;

    bool allocate(std::string process, int requiredMem);
    void deallocate(std::string process);

    static void setMaxMemory(int maxMemory);
    
    void printMem();

private:
    static int maxMemory;
    MemoryBlock* _head;
};

#endif // !MEMORYMANAGER_H