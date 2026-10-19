//
// Created by os on 8/12/25.
//

#include "../h/TCB.hpp"
#include "../h/Riscv.hpp"
#include "../h/Sem.hpp"
#include "../h/syscall_c.hpp"


TCB *TCB::running = nullptr;
uint64 TCB::timeSliceCounter = 0;
int TCB:: ID = 0;
Sem* TCB::barrier = 0;

TCB::TCB(Body body, void* arguments, uint64* stack)
{
    this->body = body;
    this->stack = (body != nullptr ? stack : nullptr);
    this->context = {body!= nullptr ? (uint64) &threadWrapper : 0,
                 stack != nullptr ? (((uint64) stack) + DEFAULT_STACK_SIZE) : 0
                };
    this->arguments = arguments;
    this->finished = false;
    this->blocked = false;
    this->semaphore = Sem::createSemaphore(0);
    //timeSlice = DEFAULT_TIME_SLICE;
    this->myID = ID++;
    this->synchronize = false;
    this->syncSemaphore = Sem::createSemaphore(0);
    this->isPaired = false;
    this->resourcesTaken = 0;


    {
        if (body == nullptr) barrier = Sem::createSemaphore(5);
    }

    {
        if (body != nullptr) { Scheduler::put(this); }
    }
}


void TCB::dispatch()
{
    TCB *old = running;
    if (!old->isFinished() && !old->isBlocked()) { Scheduler::put(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}


void TCB::exit()
{
    TCB *old = running;
    old->setFinished(true);
    old->semaphore->close();
    TCB::barrier->signal();
    TCB::dispatch();
}


TCB *TCB::createThread(Body body, void* arguments, uint64 *stack)
{
    return new TCB(body, arguments, stack);
}


void TCB::threadWrapper()
{
    Riscv::popSppSpie();
    running->body(running->arguments);
	thread_exit();
}


void TCB::join()
{
    this->semaphore->wait();
}


void TCB::setMaxThreads(int number)
{
    barrier->setValue(number);
}


void TCB::waitOnBarrier()
{
    barrier->wait();
}


void TCB::pairThreads(TCB* thread1, TCB* thread2)
{
    if (thread1->isPaired == false && thread2->isPaired == false)
    {
        thread1->pair = thread2;
        thread2->pair = thread1;
        thread1->isPaired = thread2->isPaired = true;
    }
}


void TCB::joinSync()
{
    this->syncSemaphore->wait();
}


void TCB::continueSync()
{
    this->syncSemaphore->signal();
}


void TCB::sync()
{
    if (this->pair->synchronize == false)
    {
        this->synchronize = true;
        this->joinSync();
    }
    else if (this->pair->synchronize == true)
    {
        this->pair->synchronize = false;
        this->pair->continueSync();
    }
}










