#pragma once
#ifndef PAGINGALLOCATOR_H
#define PAGINGALLOCATOR_H

#include "IAllocator.h"
#include <queue>
#include <unordered_map>

// PROCESS {CTR, MEMORY NEEDED, FRAME NUMBER}
typedef std::pair<std::shared_ptr<Process>, std::tuple<int, int, int>> Page;

class PagingAllocator : public IAllocator {
public:
    PagingAllocator(int maxMemory);
    ~PagingAllocator() = default;

    bool allocate(std::shared_ptr<Process> process) override;
    void deallocate(std::shared_ptr<Process> process) override;

    void printMem() override;

private:
    void readBackingStore(std::shared_ptr<Process> process);
    void writeBackingStore(std::shared_ptr<Process> process);
    std::queue<int> _freeFrameList;
    std::unordered_map <std::shared_ptr<Process>, std::vector<int>> _pageTable;
    int _maxMemory;
    std::vector<Page> _memory;
};

#endif //!PAGINGALLOCATOR_H