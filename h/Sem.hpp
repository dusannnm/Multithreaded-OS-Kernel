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
<<<<<<< HEAD
    uint32 signalN(uint64 n);
    uint32 waitN(uint64 n);
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

    bool isOpen() const { return open; }
    void setOpen(bool value) { open = value; }

<<<<<<< HEAD
    void setValue(int newValue) {value = newValue; }

=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
private:
    Sem(uint64 init);
    int value;
    bool open = false;

    struct Elem {
        TCB* thread;
        struct Elem* next;
<<<<<<< HEAD
        int requested;
    };

    Elem* blocked = nullptr; //lista niti blokiranih na datom semaforu
    void putBlocked(TCB* thread, int requested);
    TCB* getBlocked();
    bool seekBlocked();
=======
    };

    Elem* blocked = nullptr; //lista niti blokiranih na datom semaforu
    void putBlocked(TCB* blockedThread);
    TCB* getBlocked();
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
};


#endif //PROJECT_BASE_SEM_HPP