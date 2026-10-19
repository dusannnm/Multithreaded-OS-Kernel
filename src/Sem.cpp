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

    return 0;
}


uint32 Sem::wait()
{
    if (!open) return -1;

    if (value > 0) {
        value--;
        return 0;
    }

    putBlocked(TCB::running, 1);
    TCB::running->setBlocked(true);
    TCB::dispatch();

    return open ? 0 : -1;
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

    while (blocked) {
        Elem* toDelete = blocked;
        blocked = blocked->next;
        toDelete->thread->setBlocked(false);
        Scheduler::put(toDelete->thread);
        delete toDelete;
    }

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

