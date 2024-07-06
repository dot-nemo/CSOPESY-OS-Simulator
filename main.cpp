#include <iostream>
#include "InitScheduler.h"


int main() {
    InitScheduler init = InitScheduler();
    init.initialize();
    std::cout << init.getScheduler() << endl;
    return 0;
}