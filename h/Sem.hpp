//
// Created by os on 8/19/25.
//

#ifndef PROJECT_BASE_SEM_HPP
#define PROJECT_BASE_SEM_HPP

#include "../lib/hw.h"
#include "../h/TCB.hpp"
#include "../h/MemoryAllocator.hpp"
#include "../h/Scheduler.hpp"

class TCB;

class Sem
{
public:
    uint32 signal();
    uint32 wait();
    uint32 tryWait();
    uint32 close();
    static Sem* createSemaphore(uint64 init);
    uint32 signalN(uint64 n);
    uint32 waitN(uint64 n);

    bool isOpen() const { return open; }
    void setOpen(bool value) { open = value; }

    void setValue(int newValue) {value = newValue; }

private:
    Sem(uint64 init);
    int value;
    bool open = false;

    struct Elem {
        TCB* thread;
        struct Elem* next;
        int requested;
    };

    Elem* blocked = nullptr; //lista niti blokiranih na datom semaforu
    void putBlocked(TCB* thread, int requested);
    TCB* getBlocked();
    bool seekBlocked();
};


#endif //PROJECT_BASE_SEM_HPP