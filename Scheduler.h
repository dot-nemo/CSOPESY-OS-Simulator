// Scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <memory>
#include <queue>
#include <vector>

#include "CPU.h"
#include "Process.h"

using namespace std;
class Scheduler {
public:
    static Scheduler* get();

    void start();
    void stop();
    void destroy();
    void initialize(int cpuCount);
    void addProcess(Process process);
    

    void printStatus();
private:
    Scheduler();
    ~Scheduler() = default;

    virtual void run();

    static Scheduler* _ptr;

    queue<shared_ptr<Process>> _readyQueue;
    vector<shared_ptr<CPU>> _cpuList;
    vector<shared_ptr<Process>> _processList;

};

#endif // SCHEDULER_H
