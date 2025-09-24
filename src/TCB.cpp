//
// Created by os on 8/12/25.
//

#include "../h/TCB.hpp"
#include "../h/Riscv.hpp"
#include "../h/Sem.hpp"
#include "../h/syscall_c.hpp"


TCB *TCB::running = nullptr;
uint64 TCB::timeSliceCounter = 0;

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



