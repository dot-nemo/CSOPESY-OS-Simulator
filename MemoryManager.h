#pragma once
#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <string>
#include <unordered_map>
#include "Process.h"
#include <memory>


struct MemoryBlock {
    std::string process = "";
    bool isFree = true;
    MemoryBlock* next;
};

class MemoryManager {
public:
    MemoryManager();
    ~MemoryManager() = default;

    bool allocate(std::shared_ptr<Process> process);
    void deallocate(std::shared_ptr<Process> process);

    static void setMaxMemory(int maxMemory);
    
    void printMem(int qq);

private:
    static int maxMemory;
    MemoryBlock* _head;
};

#endif // !MEMORYMANAGER_H