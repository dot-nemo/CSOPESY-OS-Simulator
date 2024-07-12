// Scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <memory>
#include <queue>
#include <vector>

#include "CPU.h"
#include "MemoryManager.h"
#include "Process.h"

using namespace std;
class Scheduler {
public:
    static Scheduler* get();

    void startFCFS(int delay);
    void startSJF(int delay, bool preemptive);
    void startRR(int delay, int quantumCycles);
    void stop();
    void destroy();
    static void initialize(int cpuCount, float batchProcessFreq, int minIns, int maxIns, int minMemProc, int maxMemProc);
    void addProcess(std::shared_ptr<Process> process);
    void schedulerTest();
    void schedulerTestStop();
    
    void printStatus();
    void printMem();

private:
    Scheduler();
    ~Scheduler() = default;

    void runFCFS(float delay); // FCFS
    void runSJF(float delay, bool preemptive); // SJF
    void runRR(float delay, int quantumCycles); // RR

    void schedulerRun();

    static Scheduler* _ptr;

    queue<shared_ptr<Process>> _readyQueue;
    vector<shared_ptr<CPU>> _cpuList;
    vector<shared_ptr<Process>> _processList;
    priority_queue<shared_ptr<Process>> _readyQueueSJF;
    MemoryManager _memMan;

    float batchProcessFreq;
    int minIns;
    int maxIns;
    int _minMemProc;
    int _maxMemProc;

    bool _testRunning = false;
    bool running = false;
    friend class ConsoleManager;
};

#endif // SCHEDULER_H
