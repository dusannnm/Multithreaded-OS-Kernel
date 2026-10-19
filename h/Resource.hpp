//
// Created by os on 10/8/25.
//

#ifndef PROJECT_BASE_RESOURCE_HPP
#define PROJECT_BASE_RESOURCE_HPP

#include "../h/syscall_cpp.hpp"

class Resource
{
public:
    Resource(int N);
    void take(int num_of_instances);
    int give_back(int num_of_instances);

private:
    int instancesNum;
    int freeInstances;
    int busyInstances;
    Semaphore* resourceSem;
    int waitingThreads;
};


#endif //PROJECT_BASE_RESOURCE_HPP