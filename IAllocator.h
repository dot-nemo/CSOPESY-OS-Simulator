#pragma once
#ifndef IALLOCATOR_H
#define IALLOCATOR_H

#include "Process.h"

#include <memory>


class IAllocator {
    virtual bool allocate(std::shared_ptr<Process> process) = 0;
    virtual void deallocate(std::shared_ptr<Process> process) = 0;
    virtual void printMem() = 0;
};

#endif //!IALLOCATOR_H