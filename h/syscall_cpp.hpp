//
// Created by os on 8/19/25.
//

#ifndef PROJECT_BASE_SYSCALL_CPP_HPP
#define PROJECT_BASE_SYSCALL_CPP_HPP

#include "syscall_c.hpp"

//void* ::operator new (size_t n);
//void  ::operator delete (void* ptr);
//void* ::operator new[](size_t n);
//void ::operator delete[](void* ptr);

class Thread
{
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    static int sleep (time_t);

    void join();
<<<<<<< HEAD
    int getThreadId();
    static void setMaximumThreads (int number = 5);
    static void pair(Thread* t1, Thread* t2);
    void sync();
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

protected:
    Thread ();
    virtual void run () {}

private:
    thread_t myHandle;
    void (*body)(void*);
    void* arg;

    static void runWrapper(void* thread);
};

class Semaphore
{
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
    int timedWait (time_t);
    int tryWait();
<<<<<<< HEAD
    int waitN(unsigned n);
    int signalN(unsigned n);
=======
>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c

private:
    sem_t myHandle;
};

class Console
{
public:
    static char getc ();
    static void putc (char);
};

<<<<<<< HEAD
=======

>>>>>>> dea1cbf46fba0fc2bd14f61e779d3c392e2d2c0c
#endif //PROJECT_BASE_SYSCALL_CPP_HPP