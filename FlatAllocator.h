#pragma once
#ifndef FLATALLOCATOR_H
#define FLATALLOCATOR_H

#include "IAllocator.h"
#include "Process.h"

#include <memory>


struct MemoryBlock {
    std::string process = "";
    bool isFree = true;
    MemoryBlock* next;
};

class FlatAllocator : public IAllocator {
public:
    FlatAllocator(int maxMemory);
    ~FlatAllocator() = default;

    bool allocate(std::shared_ptr<Process> process) override;
    void deallocate(std::shared_ptr<Process> process) override;

    void printMem() override;

private:
    int _maxMemory;
    MemoryBlock* _head;
};

#endif //!FLATALLOCATOR_H