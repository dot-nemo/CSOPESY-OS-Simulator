#ifndef INITSCHEDULER_H
#define INITSCHEDULER_H

#include <string>

using namespace std;

class InitScheduler
{
public:
	InitScheduler();
	~InitScheduler();
	void initialize();
private:
    int _numCpu;
    string _scheduler;
    int _quantumCycle;
    bool _preemptive;
    int _batchProcessFreq;
    int _minIns;
    int _maxIns;
    int _delaysPerExec;
    bool running = false;
};

#endif