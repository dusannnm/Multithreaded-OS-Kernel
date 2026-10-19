//
// Created by os on 8/12/25.
//

#ifndef PROJECT_BASE_TCB_HPP
#define PROJECT_BASE_TCB_HPP

#include "../lib/hw.h"
#include "../lib/mem.h"
#include "../h/Sem.hpp"
#include "../h/Scheduler.hpp"
#include "../h/Riscv.hpp"


class Sem;

class TCB
{
public:
    using Body = void (*)(void*);

    bool isFinished() const { return finished; }

    void setFinished(bool value) { finished = value; }

    bool isBlocked() const { return blocked; }

    void setBlocked(bool value) { blocked = value; }

    static TCB* createThread(Body body, void* arguments, uint64* stack);

    static void dispatch();

    static void exit();

    void join();

    static TCB *running;

    ~TCB() { if (stack) delete[] stack; }

    //uint getTimeSlice() const {return timeSLice; }

<<<<<<< HEAD
    static int ID;

    static int getRunningID() { return running->myID; }

    static Sem* barrier;

    static void setMaxThreads(int number);

    static void waitOnBarrier();

    static void pairThreads(TCB* thread1, TCB* thread2);

    void sync();

    static TCB* getRunning(){return running;}

    void send(char* message);

    static char* receive();
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c


private:

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    Context context;
    uint64* stack;
    Body body;
    //uint64 timeSlice;
    bool finished;
    bool blocked;
    void* arguments;
    Sem* semaphore;
<<<<<<< HEAD
    int myID;
    TCB* pair;
    bool synchronize;
    Sem* syncSemaphore;
    bool isPaired;
    int resourcesTaken;


     void joinSync();
     void continueSync();

    friend class Riscv;
=======

    //friend class Riscv;
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

    static uint64 timeSliceCounter;
    static void contextSwitch(Context *oldContext, Context *newContext);
    static void threadWrapper();

<<<<<<< HEAD

    TCB(Body body, void* arguments, uint64* stack);

=======
    TCB(Body body, void* arguments, uint64* stack);


>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
};

#endif //PROJECT_BASE_TCB_HPP