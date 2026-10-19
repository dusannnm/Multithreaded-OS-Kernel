//
// Created by os on 10/8/25.
//

#include "Modification_Resource.hpp"

#include "printing.hpp"
#include "../h/syscall_cpp.hpp"
#include "../h/Resource.hpp"


class ThreadA: public Thread
{
    void bodyA(void* arg);

public:
    ThreadA(Resource *resource):Thread() {this->resource = resource;}
    Resource *resource;

    void run() override
    {
        bodyA(resource);
    }

};

void ThreadA::bodyA(void* arg)
{
    this->resource = (Resource*) arg;

    this->resource->take(10);
    printString("A: Uzeo sam 10. \n");
    this->resource->take(10);
    printString("A: Uzeo sam 10. \n");
    //thread_dispatch();
    this->dispatch();
    this->resource->give_back(20);
    printString("A: Vratio sam 20. \n");
    printString("A: Gotov! \n");
}

class ThreadB: public Thread
{
    void bodyB(void* arg);

public:
    ThreadB(Resource *resource):Thread() {this->resource = resource;}
    Resource *resource;

    void run() override
    {
        bodyB(resource);
    }

};

void ThreadB::bodyB(void* arg)
{
    this->resource = (Resource*) arg;

    this->resource->take(20);
    printString("B: Uzeo sam 20. \n");
    this->resource->take(20);
    printString("B: Uzeo sam 20. \n");
    //thread_dispatch();
    this->dispatch();
    this->resource->give_back(40);
    printString("B: Vratio sam 40. \n");
    printString("B: Gotov! \n");
}

class ThreadC: public Thread
{
    void bodyC(void* arg);

public:
    ThreadC(Resource *resource):Thread() {this->resource = resource;}
    Resource *resource;

    void run() override
    {
        bodyC(resource);
    }

};

void ThreadC::bodyC(void* arg)
{
    this->resource = (Resource*) arg;

    this->resource->take(30);
    printString("C: Uzeo sam 30. \n");
    //thread_dispatch();
    this->dispatch();
    this->resource->give_back(30);
    printString("C: Vratio sam 30. \n");
    printString("C: Gotov! \n");
}

void Modification_Resource_test()
{
    Thread* threads[3];
    Resource* resource = new Resource(50);

    threads[0] = new ThreadA(resource);
    threads[1] = new ThreadB(resource);
    threads[2] = new ThreadC(resource);

    for(auto & thread : threads) {
        thread->start();
    }

    for(auto & thread : threads) {
        thread->join();
    }

}