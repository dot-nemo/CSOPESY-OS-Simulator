// Scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <memory>
#include <queue>
#include <vector>

#include "Cpu.h"
#include "Process.h"

using namespace std;
class Scheduler {
public:
    static Scheduler* get();

    void initialize();
    void start();
    void stop();
private:
    Scheduler();
    ~Scheduler() = default;

    void run();

    static Scheduler* _ptr;

    int _numCpu;
    string _scheduler;
    int _quantumCycle;
    bool _preemptive;
    int _batchProcessFreq;
    int _minIns;
    int _maxIns;
    int _delaysPerExec;
    bool running = false;

    queue<shared_ptr<Process>> _readyQueue;
    vector<shared_ptr<Cpu>> _cpuList;
    vector<shared_ptr<Process>> _processList;

};

#endif // SCHEDULER_H
