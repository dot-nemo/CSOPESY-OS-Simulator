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
    void schedulerTest(float batchProcessFreq);
    
    void printStatus();
private:
    Scheduler();
    ~Scheduler() = default;

    void run(float delay); // FCFS
    void run(float delay); // SJF
    void run(float delay); // RR

    static Scheduler* _ptr;

    queue<shared_ptr<Process>> _readyQueue;
    vector<shared_ptr<CPU>> _cpuList;
    vector<shared_ptr<Process>> _processList;

    bool running = false;

};

#endif // SCHEDULER_H
