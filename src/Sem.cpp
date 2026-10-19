//
// Created by os on 8/19/25.
//

#include "../h/Sem.hpp"
#include "../lib/mem.h"

Sem::Sem(uint64 init)
{
    this->value = init;
    this->open = true;
}


uint32 Sem::signal()
{
<<<<<<< HEAD
    if (!open) return -1;

    value++;

    while (blocked && value >= blocked->requested)
    {
        Elem* first = blocked;

        value -= first->requested;

        TCB* t = getBlocked();
        t->setBlocked(false);
        Scheduler::put(t);
    }

=======
    if (!this->isOpen()) return -1;

    if(++value <= 0){
        TCB* unblockedThread = getBlocked();
        unblockedThread->setBlocked(false);
        Scheduler::put(unblockedThread);
    }
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
    return 0;
}


uint32 Sem::wait()
{
<<<<<<< HEAD
    if (!open) return -1;

    if (value > 0) {
        value--;
        return 0;
    }

    putBlocked(TCB::running, 1);
    TCB::running->setBlocked(true);
    TCB::dispatch();

    return open ? 0 : -1;
=======
    if (!this->isOpen()) return -1;

    if(--value < 0){
        TCB* blockedThread= TCB::running;
        putBlocked(blockedThread);
        blockedThread->setBlocked(true);
        TCB::dispatch();
    	if (!this->isOpen()) return -1;
    }
    return 0;
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
}


uint32 Sem::tryWait()
{
    if (!this->isOpen()) return -1;

    if(value > 0){
        value--;
        return 0;
    }
    else return 1;
}


uint32 Sem::close()
{
    if (!this->isOpen()) return -1;
    this->setOpen(false);

<<<<<<< HEAD
    while (blocked) {
        Elem* toDelete = blocked;
        blocked = blocked->next;
        toDelete->thread->setBlocked(false);
        Scheduler::put(toDelete->thread);
        delete toDelete;
    }

=======
    for (Elem* iter = blocked; iter; iter = iter->next){
        //TCB::TCB* thread = this->getBlocked();
        iter->thread->setBlocked(false);
        Scheduler::put(iter->thread);
    }
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
    return 0;
}


TCB* Sem::getBlocked()
{
    Elem* firstBlocked = blocked;
    TCB* unblockedThread = firstBlocked->thread;
    blocked = blocked->next;
    delete firstBlocked;
    return unblockedThread;
}

<<<<<<< HEAD
bool Sem::seekBlocked()
{
    if (blocked)
        return true;
    else
        return false;
}


void Sem::putBlocked(TCB* blockedThread, int requested)
{
    Elem* newBlocked = new Elem;
    newBlocked->thread = blockedThread;
    newBlocked->requested = requested;
=======

void Sem::putBlocked(TCB* blockedThread)
{
    Elem* newBlocked = new Elem;
    newBlocked->thread = blockedThread;
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
    //newBlocked->thread->setBlocked(true);
    newBlocked->next = nullptr;

    if(blocked){
        Elem* previous = nullptr;
        for (Elem* iter = blocked; iter; iter = iter->next) previous = iter;
        previous->next = newBlocked;
    }
    else blocked = newBlocked;
}


Sem* Sem::createSemaphore(uint64 init)
{
    return new Sem(init);
}
<<<<<<< HEAD

uint32 Sem::signalN(uint64 n)
{
    if (!open) return -1;

    value += n;

    while (blocked && value >= blocked->requested)
    {
        Elem* first = blocked;

        value -= first->requested;

        TCB* t = getBlocked();
        t->setBlocked(false);
        Scheduler::put(t);
    }

    return 0;
}

uint32 Sem::waitN(uint64 n)
{
    if (!open) return -1;

    if (value >= int(n))
    {
        value -= n;
        return 0;
    }

    putBlocked(TCB::running, n);
    TCB::running->setBlocked(true);
    TCB::dispatch();

    return open ? 0 : -1;
}

=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
