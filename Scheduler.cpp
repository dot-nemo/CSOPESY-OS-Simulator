#include "Scheduler.h"

using namespace std;

Scheduler* Scheduler::_ptr = nullptr;

Scheduler* Scheduler::get() {
	return _ptr;
}



